#include "tod/todlua/todluathread.h"

#include "tod/core/exception.h"
#include "tod/core/resource.h"
#include "tod/todlua/todluascriptserver.h"

using namespace tod;

//-----------------------------------------------------------------------------
TodLuaThread::TodLuaThread():
luaStateRoot_(0), luaState_(0), yieldMode_(YIELDMODE_NONE), waitFrame_(0)
{
}


//-----------------------------------------------------------------------------
TodLuaThread::~TodLuaThread()
{
    luaState_ = 0;
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
        {
            return false;
        }
    }
    return true;
}


//-----------------------------------------------------------------------------
bool TodLuaThread::runFile(lua_State* s, const Uri& uri, String* result)
{
    luaStateRoot_ = s;
    luaState_ = lua_newthread(s);

    lua_pushlightuserdata(s, luaState_);
    lua_pushlightuserdata(s, this);
    lua_settable(s, LUA_GLOBALSINDEX);

    tod::Resource resource(uri);
    if (!resource.open(
        tod::Resource::OPEN_READ |
        tod::Resource::OPEN_BINARY))
        return false;

    dynamic_buffer_t buffer;
    resource.read(buffer);

    int status = luaL_loadbuffer(
        luaState_, &buffer[0], buffer.size(), "TodLua");
    if (0 == status)    // OK
    {   
        status = lua_resume(luaState_, 0);
        // yield
        if (status == LUA_YIELD)
            return true;
        // error
        else
            goto ON_ERROR;
    }
    else    // error
        goto ON_ERROR;

    return true;

ON_ERROR:
    {
        String result("file(%s):\n", uri.get().toAnsiString().c_str());
        result += TodLuaScriptServer::instance()->
            generateStackTrace(luaState_);
        TOD_THROW_EXCEPTION(0, result);
        lua_settop(luaState_, 0);
        return false;
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
void TodLuaThread::setYieldMode(YieldMode m)
{
    yieldMode_ = m;
}


//-----------------------------------------------------------------------------
TodLuaThread::YieldMode TodLuaThread::getYieldMode() const
{
    return yieldMode_;
}
