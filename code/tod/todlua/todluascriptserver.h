#ifndef TOD_TODPYTHON_TODLUASCRIPTSERVER_H
#define TOD_TODPYTHON_TODLUASCRIPTSERVER_H
/**
    @ingroup TodLuaScriptServer
    @class tod::ScriptServer
    @brief
*/

extern "C"
{
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

#include "tod/core/scriptserver.h"

namespace tod
{
    class TodLuaScriptServer : public ScriptServer
    {
    public:
        TodLuaScriptServer();
        virtual~TodLuaScriptServer();
        DECLARE_CLASS(TodLuaScriptServer, ScriptServer);

        static void initialize();

        override bool run(const String& str);
        override bool call(
            const String& str,
            Parameter* parameter);
        override bool runFile(const Uri& uri);

    private:
        void reg_globalfunc(lua_CFunction func, const char* name);

    private:
        lua_State* luaStateRoot_;
    };
}

#endif // TOD_CORE_SCRIPT_SCRIPTSERVER_H
