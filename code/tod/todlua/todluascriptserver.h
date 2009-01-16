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

#include "tod/core/singleton.h"
#include "tod/core/scriptserver.h"

#define TODLUA_METATABLES "_TodLuaMetaTables"

namespace tod
{
    class TodLuaScriptServer :
        public ScriptServer,
        public Singleton<TodLuaScriptServer>
    {
    public:
        TodLuaScriptServer();
        virtual~TodLuaScriptServer();
        DECLARE_CLASS(TodLuaScriptServer, ScriptServer);

        static void initialize();

        override bool run(const String& str, String* result);
        override bool call(
            const String& str,
            Parameter* parameter);
        override bool runFile(const Uri& uri, String* result);

    public:
        bool executeLuaChunk(String* result, int errfunc);
        String generateStackTrace();
        void stackToString(lua_State* s, int bottom, String* result);
        bool thunkObject(lua_State* s, Object* obj);
        Object* unpackFromStack(lua_State* s, int table_index);
        bool stackToVariable(lua_State* s, Variable* v, int index);
        bool stackToInparam(lua_State* s, Method* method);
        bool outparamToStack(lua_State* s, Method* method);

    private:
        void reg_globalfunc(lua_CFunction func, const char* name);

    private:
        lua_State* luaStateRoot_;
    };
}

#endif // TOD_CORE_SCRIPT_SCRIPTSERVER_H
