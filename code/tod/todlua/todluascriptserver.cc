#include "tod/todlua/todluascriptserver.h"

#include "tod/core/exception.h"
#include "tod/core/kernel.h"
#include "tod/core/module.h"
#include "tod/core/resource.h"
#include "tod/todlua/todlua_extension.h"

using namespace tod;

IMPLEMENT_CLASS(TodLuaScriptServer, ScriptServer);
INCLUDE_MODULE(Engine);
INCLUDE_MODULE(D3D9Graphics);
INCLUDE_MODULE(TodLua);


//-----------------------------------------------------------------------------
void TodLuaScriptServer::initialize()
{
    USING_MODULE(Engine);
    USING_MODULE(D3D9Graphics);
    USING_MODULE(TodLua);
}


//-----------------------------------------------------------------------------
TodLuaScriptServer::TodLuaScriptServer():
luaStateRoot_(0)
{
    // Get a default Lua interpreter up and running then
    luaStateRoot_ = lua_open();
    if (0 == luaStateRoot_)
        TOD_THROW_EXCEPTION(0,
            STRING("Could not create the Lua5 interpreter"));

    // Setup a panic handler
    lua_atpanic(luaStateRoot_, luacmd_Panic);

    // Get a global table of TodEngine functions up
    reg_globalfunc(luacmd_ResRoot, "resroot");
    reg_globalfunc(luacmd_NewObj, "newobj");
    reg_globalfunc(luacmd_New, "new");
    reg_globalfunc(luacmd_Get, "get");
    reg_globalfunc(luacmd_Delete, "delete");
    reg_globalfunc(luacmd_Ls, "ls");
    reg_globalfunc(luacmd_PushCwn, "pushcwn");
    reg_globalfunc(luacmd_PopCwn, "popcwn");
    reg_globalfunc(luacmd_TodPrint, "todprint");
    reg_globalfunc(luacmd_Exit, "exit");
    reg_globalfunc(luacmd_Serialize, "serialize");
    reg_globalfunc(luacmd_Deserialize, "deserialize");
    reg_globalfunc(luacmd_GetModuleList, "getmodulelist");
    reg_globalfunc(luacmd_GetTypeList, "gettypelist");

    // Setup environment

    // clear stack
    lua_settop(luaStateRoot_, 0);
}


//-----------------------------------------------------------------------------
TodLuaScriptServer::~TodLuaScriptServer()
{
    if (luaStateRoot_)
        lua_close(luaStateRoot_);
    luaStateRoot_ = 0;
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::run(const String& str)
{
    luaL_dostring(luaStateRoot_, str.toAnsiString().c_str());
    return true;
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::call(const String& str, Parameter* parameter)
{
    return false;
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::runFile(const Uri& uri)
{
    tod::Resource resource(uri);
    if (!resource.open(
        tod::Resource::OPEN_READ |
        tod::Resource::OPEN_BINARY))
        return false;

    dynamic_buffer_t buffer;
    resource.read(buffer);
    buffer.resize(buffer.size() + 1);
    buffer[buffer.size() - 1] = 0;

    luaL_dostring(luaStateRoot_, &buffer[0]);

    return false;
}


//-----------------------------------------------------------------------------
void TodLuaScriptServer::reg_globalfunc(lua_CFunction func, const char* name)
{
    lua_pushstring(luaStateRoot_, name);
    lua_pushlightuserdata(luaStateRoot_, this);
    lua_pushcclosure(luaStateRoot_, func, 1);
    lua_settable(luaStateRoot_, LUA_GLOBALSINDEX);
    lua_settop(luaStateRoot_, 0);
}


//-----------------------------------------------------------------------------
void initialize_TodLua(Module* module)
{
    REGISTER_TYPE(module, TodLuaScriptServer);
}


//-----------------------------------------------------------------------------
void finalize_TodLua(Module* module)
{
}

//-----------------------------------------------------------------------------
DECLARE_MODULE(TodLua);
