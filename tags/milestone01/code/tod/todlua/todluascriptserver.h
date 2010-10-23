#ifndef TOD_TODLUA_TODLUASCRIPTSERVER_H
#define TOD_TODLUA_TODLUASCRIPTSERVER_H
/**
    @ingroup TodLuaScriptServer
    @class tod::TodLuaScriptServer
    @brief
*/

extern "C"
{
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

#include "tod/core/singleton3.h"
#include "tod/core/scriptserver.h"
#include "tod/todlua/todluathread.h"

#define TODLUA_METATABLES "_TodLuaMetaTables"
#define TODLUA_OBJECTMETATABLES "_TodLuaObjectMetaTable"

namespace tod
{
    class TodLuaScriptServer :
        public ScriptServer,
        public Singleton3<TodLuaScriptServer>
    {
    public:
        TodLuaScriptServer();
        virtual~TodLuaScriptServer();
        DECLARE_CLASS(TodLuaScriptServer, ScriptServer);

        void newThread(const Uri& uri);
        void newThreadCall(const String& str, Parameter* parameter);

        override bool run(const String& str, String* result);
        override bool call(const String& str, Parameter* parameter);
        override bool runFile(const Uri& uri, String* result);

        override bool trigger();

        static void initialize();
        static void bindMethod();

    public:
        bool run(lua_State* s, const char* buf, size_t size, String* result);
        bool call(lua_State* s, const String& str, Parameter* parameter);
        bool runFile(lua_State* s, const Uri& uri, String* result);
        bool executeLuaChunk(lua_State* s, String* result, int errfunc);
        String generateStackTrace(lua_State* s);
        void stackToString(lua_State* s, int bottom, String* result);
        bool thunkObject(lua_State* s, Object* obj, bool creation_by_lua);
        Object* unpackFromStack(lua_State* s, int table_index);
        bool stackToVariable(lua_State* s, Variable* v, int index);
        bool stackToNewVariable(lua_State* s, Variables* vs, int index);
        bool stackToInparam(lua_State* s, Method* method);
        bool outparamToStack(lua_State* s, Method* method);
        bool variablesToStack(lua_State* s, Variables* vs);
        bool variableToStack(lua_State* s, Variable* v);
        bool propertyToStack(lua_State* s, Object* obj, Property* prop);

    private:
        void reg_globalfunc(lua_CFunction func, const char* name);

    private:
        typedef std::list<TodLuaThread*> TodLuaThreads;

    private:
        lua_State* luaStateRoot_;
        TodLuaThreads threads_;
    };
}

#endif // TOD_TODLUA_TODLUASCRIPTSERVER_H
