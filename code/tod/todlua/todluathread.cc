#include "tod/todlua/todluathread.h"

#include "tod/core/exception.h"
#include "tod/core/resource.h"
#include "tod/todlua/todluascriptserver.h"

using namespace tod;

//-----------------------------------------------------------------------------
TodLuaThread::TodLuaThread():
key_(0), luaStateRoot_(0), luaState_(0),
yieldMode_(YIELDMODE_NONE), waitFrame_(0)
{
}


//-----------------------------------------------------------------------------
TodLuaThread::~TodLuaThread()
{
    luaL_unref(luaStateRoot_, LUA_REGISTRYINDEX, key_);
    luaState_ = 0;
    luaStateRoot_ = 0;
    key_ = 0;
}


//-----------------------------------------------------------------------------
bool TodLuaThread::update()
{
    if (yieldMode_ == YIELDMODE_TIME &&
        stopWatch_.isStarted() &&
        stopWatch_.elapse() >= waitTime_)
    {
        int status = lua_resume(luaState_, 0);
        // dead coroutine
        if (status == 0)
            return false;
        // yield
        else if (status == LUA_YIELD)
            return true;
        // error
        else
            return false;
    }
    else if (yieldMode_ == YIELDMODE_FRAME)
    {
        if (s_curFrame_ >= waitFrame_)
        {
            int status = lua_resume(luaState_, 0);
            // dead coroutine
            if (status == 0)
                return false;
            // yield
            else if (status == LUA_YIELD)
                return true;
            // error
            else
                return false;
        }
    }
    
    return true;
}


//-----------------------------------------------------------------------------
TodLuaThread::ReturnCode TodLuaThread::call
(lua_State* s, const String& str, Parameter* parameter)
{
    luaStateRoot_ = s;
    luaState_ = lua_newthread(luaStateRoot_);

    lua_pushlightuserdata(luaStateRoot_, luaState_);
    lua_pushlightuserdata(luaStateRoot_, this);
    lua_settable(luaStateRoot_, LUA_REGISTRYINDEX);

    key_ = luaL_ref(luaStateRoot_, LUA_REGISTRYINDEX);

    lua_getglobal(luaState_, str.toAnsiString().c_str());
    if (!lua_isfunction(luaState_, -1))
    {
        TOD_THROW_EXCEPTION(0,
            String("Could not found function '%s'",
                str.toAnsiString().c_str()));
        lua_settop(luaState_, 0);
        return RETURNCODE_ERROR;
    }

    size_t pnum = 0;
    if (parameter)
    {
        pnum = parameter->in()->size();
        if (!TodLuaScriptServer::instance()->
            variablesToStack(luaState_, parameter->in()))
            return RETURNCODE_ERROR;
    }

    int status = lua_resume(luaState_, pnum);
    if (0 == status)
        return RETURNCODE_OK;
    // yield
    else if (status == LUA_YIELD)
        return RETURNCODE_YIELD;
    // error
    else
    {
        String result;
        TodLuaScriptServer::instance()->stackToString(luaState_, 0, &result);
        TOD_THROW_EXCEPTION(0, result);
        return RETURNCODE_ERROR;
    }

    return RETURNCODE_OK;
}


//-----------------------------------------------------------------------------
TodLuaThread::ReturnCode TodLuaThread::runFile
(lua_State* s, const Uri& uri, String* result)
{
    luaStateRoot_ = s;
    luaState_ = lua_newthread(luaStateRoot_);

    lua_pushlightuserdata(luaStateRoot_, luaState_);
    lua_pushlightuserdata(luaStateRoot_, this);
    lua_settable(luaStateRoot_, LUA_REGISTRYINDEX);

    key_ = luaL_ref(luaStateRoot_, LUA_REGISTRYINDEX);

    tod::Resource resource(uri);
    if (!resource.open(
        tod::Resource::OPEN_READ |
        tod::Resource::OPEN_BINARY))
        return RETURNCODE_ERROR;

    dynamic_buffer_t buffer;
    resource.read(&buffer);

    int status = luaL_loadbuffer(
        luaState_, &buffer[0], buffer.size(), "TodLua");
    if (0 == status)    // OK
    {   
        status = lua_resume(luaState_, 0);
        if (0 == status)
            return RETURNCODE_OK;
        // yield
        else if (status == LUA_YIELD)
            return RETURNCODE_YIELD;
        // error
        else
            goto ON_ERROR;
    }
    else    // error
        goto ON_ERROR;

    return RETURNCODE_OK;

ON_ERROR:
    {
        String result("file(%s):\n", uri.get().toAnsiString().c_str());
        result += TodLuaScriptServer::instance()->
            generateStackTrace(luaState_);
        TOD_THROW_EXCEPTION(0, result);
        lua_settop(luaState_, 0);
        return RETURNCODE_ERROR;
    }
}


//-----------------------------------------------------------------------------
void TodLuaThread::waitSecond(const Time& sec)
{
    yieldMode_ = YIELDMODE_TIME;
    waitTime_ = static_cast<float>(sec);
    stopWatch_.restart();
}


//-----------------------------------------------------------------------------
void TodLuaThread::waitFrame(int frame)
{
    yieldMode_ = YIELDMODE_FRAME;
    waitFrame_ = frame + s_curFrame_;
}


//-----------------------------------------------------------------------------
void TodLuaThread::setYieldMode(YieldMode m)
{
    yieldMode_ = m;
}


//-----------------------------------------------------------------------------
TodLuaThread::YieldMode TodLuaThread::getYieldMode() const
{
    return yieldMode_;
}

//-----------------------------------------------------------------------------
int TodLuaThread::s_curFrame_ = 0;
