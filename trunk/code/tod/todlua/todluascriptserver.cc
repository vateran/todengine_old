#include "tod/todlua/todluascriptserver.h"

#include "tod/core/exception.h"
#include "tod/core/color.h"
#include "tod/core/kernel.h"
#include "tod/core/module.h"
#include "tod/core/resource.h"
#include "tod/core/simpleproperty.h"
#include "tod/engine/timeserver.h"
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
    reg_globalfunc(luacmd_StackDump, "_TODLUASCRIPTSERVER_STACKDUMP");
    reg_globalfunc(luacmd_Res, "res");
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
    reg_globalfunc(luacmd_WaitSec, "todwaitsec");
    reg_globalfunc(luacmd_WaitFrame, "todwaitframe");

    // Setup environment
    lua_pushstring(luaStateRoot_, TODLUA_METATABLES);
    lua_newtable(luaStateRoot_);
    lua_settable(luaStateRoot_, LUA_GLOBALSINDEX);

    lua_pushstring(luaStateRoot_, TODLUA_OBJECTMETATABLES);
    lua_newtable(luaStateRoot_);
    lua_pushstring(luaStateRoot_, "__gc");
    lua_pushcfunction(luaStateRoot_, luacmd_Del);
    lua_settable(luaStateRoot_, -3);
    lua_settable(luaStateRoot_, LUA_GLOBALSINDEX);

    // clear stack
    lua_settop(luaStateRoot_, 0);
}


//-----------------------------------------------------------------------------
TodLuaScriptServer::~TodLuaScriptServer()
{
    threads_.reverse();
    for (TodLuaThreads::iterator i = threads_.begin();
         i != threads_.end(); ++i)
        delete *i;
    threads_.clear();

    if (luaStateRoot_)
        lua_close(luaStateRoot_);
    luaStateRoot_ = 0;
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::run(const String& str, String* result)
{
    return run(luaStateRoot_, str.toAnsiString().c_str(), str.size(), result);
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::call(const String& str, Parameter* parameter)
{
    return call(luaStateRoot_, str, parameter);
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::runFile(const Uri& uri, String* result)
{
    return runFile(luaStateRoot_, uri, result);
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::run(lua_State* s, const char* buf, size_t size, String* result)
{
    // push the error handler on stack
    lua_pushstring(s, "_TODLUASCRIPTSERVER_STACKDUMP");
    lua_gettable(s, LUA_GLOBALSINDEX);
    int errfunc = lua_gettop(s);

    int status = luaL_loadbuffer(
        s, buf, size, "TodLua");
    if (0 == status)
    {   
        //return executeLuaChunk(s, result, errfunc);
        executeLuaChunk(s, result, errfunc);

        lua_gc(s, LUA_GCCOLLECT, 0);
        return true;
    }
    else
    {   
        String desc;
        stackToString(s, 0, &desc);
        if (result)
            *result = desc;
        TOD_THROW_EXCEPTION(0, desc);
        lua_settop(s, 0);
        return false;
    }
    return true;
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::runFile(lua_State* s, const Uri& uri, String* result)
{
    tod::Resource resource(uri);
    if (!resource.open(
        tod::Resource::OPEN_READ |
        tod::Resource::OPEN_BINARY))
        return false;

    dynamic_buffer_t buffer;
    resource.read(&buffer);

    return run(s, &buffer[0], buffer.size(), result);    
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::call(lua_State* s, const String& str, Parameter* parameter)
{
    lua_getglobal(s, str.toAnsiString().c_str());
    if (!lua_isfunction(s, -1))
    {
        TOD_THROW_EXCEPTION(0,
            String("Could not found function '%s'",
                str.toAnsiString().c_str()));
        lua_settop(s, 0);
        return false;
    }

    size_t pnum = 0;
    if (parameter)
    {
        pnum = parameter->in()->size();
        if (!variablesToStack(s, parameter->in()))
            return false;
    }

    if (lua_pcall(s, pnum, 1, 0) != 0)
    {
        parameter->out()->clear();
        parameter->out()->add<String>(
            TodLuaScriptServer::instance()->generateStackTrace(s));
        return false;
    }

    parameter->out()->clear();

    if (lua_istable(s, -1))
    {
        pnum = lua_objlen(s, -1);
        for (size_t pi = 1; pi <= pnum; ++pi)
        {   
            lua_rawgeti(s, -1, pi);
            if (!stackToNewVariable(s, parameter->out(), -1))
            {
                lua_settop(s, 0);
                return false;
            }
            lua_pop(s, 1);
        }
    }
    else
    {
        stackToNewVariable(s, parameter->out(), -1);
    }

    lua_settop(s, 0);
    return true;
}


//-----------------------------------------------------------------------------
void TodLuaScriptServer::newThread(const Uri& uri)
{
    TodLuaThread* new_thread = new TodLuaThread();

    TodLuaThread::ReturnCode r = new_thread->runFile(luaStateRoot_, uri, 0);

    switch (r)
    {
    case TodLuaThread::RETURNCODE_OK:
    case TodLuaThread::RETURNCODE_ERROR:
        delete new_thread;
        break;
    case TodLuaThread::RETURNCODE_YIELD:
        threads_.push_back(new_thread);
        break;
    }
}


//-----------------------------------------------------------------------------
void TodLuaScriptServer::newThreadCall(const String& str, Parameter* parameter)
{
    TodLuaThread* new_thread = new TodLuaThread();

    TodLuaThread::ReturnCode r =
        new_thread->call(luaStateRoot_, str, parameter);

    switch (r)
    {
    case TodLuaThread::RETURNCODE_OK:
    case TodLuaThread::RETURNCODE_ERROR:
        delete new_thread;
        break;
    case TodLuaThread::RETURNCODE_YIELD:
        threads_.push_back(new_thread);
        break;
    }
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::trigger()
{
    for (TodLuaThreads::iterator i = threads_.begin();
         i != threads_.end();)
    {
        TodLuaThread* t = *i;
        if (!t->update())
        {
            delete t;
            i = threads_.erase(i);
        }
        else
            ++i;
    }

    ++TodLuaThread::s_curFrame_;
    return true;
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::executeLuaChunk(lua_State* s, String* result, int errfunc)
{
    int status = lua_pcall(s, 0, 0, errfunc);

    // error occurred
    if (0 != status)
    {
        String desc = generateStackTrace(s);
        if (result)
            *result = desc;
        lua_settop(s, 0);
    }
    else
    {
        if (result)
        {
            result->clear();
            stackToString(s, 0, result);
        }
    }

    return (0 == status);
}


//-----------------------------------------------------------------------------
String TodLuaScriptServer::generateStackTrace(lua_State* s)
{
    String result;

    result = STRING("TodLuaScriptServer encounter a problem...\n");
    result += String("%s", lua_tostring(s, -1));
    result += STRING("\n\n-- Stack Trace --\n");

    lua_Debug debug_info;

    int level = 0;
    const char* namewhat = 0;
    const char* funcname = 0;
    char_t buffer[1024];
    while (lua_getstack(s, level, &debug_info))
    {
        if (lua_getinfo(s, "nSl", &debug_info))
        {
            if (0 == debug_info.namewhat[0])
                namewhat = "???";
            else
                namewhat = debug_info.namewhat;
            if (0 == debug_info.name)
                funcname = "???";
            else
                funcname = debug_info.name;

            tod_snprintf(buffer, 1024, STRING("%s(%d): %s (%s/%s)\n"),
                String(debug_info.short_src).c_str(),
                debug_info.currentline,
                String(funcname).c_str(),
                String(namewhat).c_str(),
                String(debug_info.what).c_str());
            buffer[sizeof(buffer) - 1] = 0;
            result += buffer;

        }
        else
            result += STRING("Failed to generate stack trace.\n");
        ++level;
    }

    return result;
}


//-----------------------------------------------------------------------------
void TodLuaScriptServer::stackToString(lua_State* s, int bottom, String* result)
{
    while (bottom < lua_gettop(s))
    {
        switch (lua_type(s, -1))
        {
            case LUA_TBOOLEAN:
            {
                if (lua_toboolean(s, -1)) 
                    *result += STRING("true");
                else 
                    *result += STRING("false");
                break;  
            }
            case LUA_TNUMBER:
            case LUA_TSTRING:
            {
                *result += String(lua_tostring(s, -1));
                break;
            }
            case LUA_TUSERDATA:
            case LUA_TLIGHTUSERDATA:
            {
                *result += STRING("<userdata>");
                break;
            }
            case LUA_TFUNCTION:
            {
                lua_getupvalue(s, -1, 1);
                TodLuaScriptServer::instance()->
                    stackToString(s, lua_gettop(s) - 1, result);
                break;
            }
            case LUA_TNIL:
            {
                *result += STRING("<nil>");
                break;
            }
            case LUA_TTABLE:
            {
                // check if it's a thunk
                lua_pushstring(s, "_");
                lua_rawget(s, -2);
                if (lua_isuserdata(s, -1))
                {
                    Object* obj =
                        TodLuaScriptServer::instance()->
                            unpackFromStack(s, 1);
                    Node* node = dynamic_cast<Node*>(obj);
                    if (node)
                    {
                        // assume it's a thunk
                        *result += String("<thunk path='%s'>",
                            node->getAbsolutePath().toAnsiString().c_str());
                    }
                    else
                    {
                        *result += String("<thunk address=%p>", obj);
                    }

                    lua_pop(s, 1);
                }
                else
                {
                    lua_pop(s, 1);
                    *result += STRING("{ ");
                    lua_pushnil(s);

                    bool firstItem = true;
                    while (lua_next(s, -2) != 0)
                    {
                        if (!firstItem)
                            *result += STRING(", ");
                        else
                            firstItem = false;
                        TodLuaScriptServer::instance()->
                            stackToString(s, lua_gettop(s) - 1, result);
                    }
                    *result += STRING(" }");
                }
                break;
            }
            default:
                *result += STRING("???");
                break;  
        }
        lua_pop(s, 1);
    }
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::thunkObject
(lua_State* s, Object* obj, bool creation_by_lua)
{
    lua_newtable(s);

    lua_pushstring(s, "_");
    TodLuaObject* result =
        static_cast<TodLuaObject*>
            (lua_newuserdata(s, sizeof(TodLuaObject)));
    memset(result, 0, sizeof(TodLuaObject));
    result->object_ = obj;
    result->createdByLua_ = creation_by_lua;
    Node* node = dynamic_cast<Node*>(obj);
    if (node)
        node->addRef();

    lua_pushstring(s, TODLUA_OBJECTMETATABLES);
    lua_gettable(s, LUA_GLOBALSINDEX);
    lua_setmetatable(s, -2);

    lua_settable(s, -3);

    // get todlua type table        
    lua_pushstring(s, TODLUA_METATABLES);
    lua_gettable(s, LUA_GLOBALSINDEX);

    if (!lua_istable(s, -1))
    {
        TOD_THROW_EXCEPTION(0, STRING("todlua type table not found!"));
        return 1;
    }

    // find the corresponding type metatable in TODLUA_METATABLES
    std::string tname(obj->getType()->getName().toAnsiString());
    const char* type_name = tname.c_str();
    lua_pushstring(s, type_name);
    lua_gettable(s, -2);

    if (!lua_istable(s, -1))
    {
        // pop the nil off the stack
        lua_pop(s, 1);
        
        // metatable
        lua_pushstring(s, type_name);
        lua_newtable(s);

        lua_pushstring(s, "__index");
        lua_newtable(s);

        Type* cur_type = obj->getType();
        while (cur_type)
        {
            for (Methods::iterator m = cur_type->firstMethod();
                 m != cur_type->lastMethod(); ++m)
            {
                Method* method = m->second;
                lua_pushstring(s, method->getName().toAnsiString().c_str());
                lua_pushlightuserdata(s, method);
                lua_pushcclosure(s, luacmd_Invoke, 1);
                lua_settable(s, -3);
            }
            for (Properties::iterator p = cur_type->firstProperty();
                 p != cur_type->lastProperty(); ++p)
            {
                Property* prop = p->second;
                String name("");
                name += prop->getName();
                lua_pushstring(s, name.toAnsiString().c_str());
                lua_pushlightuserdata(s, prop);
                lua_pushcclosure(s, luacmd_GetProperty, 1);
                lua_settable(s, -3);
            }
            cur_type = cur_type->getBase();
        }
        
        // insert ("__index", table) to metatable
        lua_settable(s, -3);

        // insert ("__newindex", luacmd_SetProperty) to metatable
        lua_pushstring(s, "__newindex");
        lua_pushcfunction(s, luacmd_SetProperty);
        lua_settable(s, -3);

        // insert (type_name, metatable) to TODLUA_METATABLES
        lua_settable(s, -3);

        lua_pushstring(s, type_name);
        lua_gettable(s, -2);
    }

    // remove _TodLuaObjectTable from the stack
    lua_remove(s, -2);

    lua_setmetatable(s, -2);

    return true;
}


//-----------------------------------------------------------------------------
Object* TodLuaScriptServer::unpackFromStack(lua_State* s, int table_index)
{
    Object* obj = 0;

    int t = lua_gettop(s);
    if (0 == t)
        return 0;

    lua_pushstring(s, "_");
    lua_rawget(s, table_index);
    
    if (lua_isuserdata(s, -1))
    {
        TodLuaObject* data =
            static_cast<TodLuaObject*>
                (lua_touserdata(s, -1));
        if (data->object_)
            obj = data->object_;
    }

    lua_pop(s, 1);

    return obj;
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::stackToVariable(lua_State* s, Variable* v, int index)
{
    if (TypeId<bool>::check(v->getType()))
    {
        if (!lua_isboolean(s, index) &&
            !lua_isnumber(s, index))
            return false;

        typedef bool type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        if (lua_isboolean(s, index))
            *av = (lua_toboolean(s, index) > 0)?true:false;
        else
            *av = (lua_tonumber(s, index) > 0)?true:false;
    }
    else if (TypeId<int>::check(v->getType()))
    {
        if (!lua_isnumber(s, index))
            return false;

        typedef int type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        *av = static_cast<type>(lua_tonumber(s, index));
    }
    else if (TypeId<__int64>::check(v->getType()))
    {
        if (!lua_isnumber(s, index))
            return false;

        typedef __int64 type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        *av = static_cast<type>(lua_tonumber(s, index));
    }
    else if (TypeId<float>::check(v->getType()))
    {
        if (!lua_isnumber(s, index))
            return false;

        typedef float type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        *av = static_cast<type>(lua_tonumber(s, index));
    }
    else if (TypeId<double>::check(v->getType()))
    {
        if (!lua_isnumber(s, index))
            return false;

        typedef float type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        *av = static_cast<type>(lua_tonumber(s, index));
    }
    else if (TypeId<String>::check(v->getType()))
    {
        if (!lua_isstring(s, index))
            return false;

        typedef String type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        *av = lua_tostring(s, index);
    }
    else if (TypeId<Uri>::check(v->getType()))
    {
        if (!lua_isstring(s, index))
            return false;

        typedef Uri type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        *av = String(lua_tostring(s, index));
    }
    else if (TypeId<Vector3>::check(v->getType()))
    {
        if (!lua_istable(s, index))
            return false;
        if (lua_objlen(s, index) != 3)
            return false;

        typedef Vector3 type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        Vector3& tv(av->get());

        for (size_t i = 0; i < 3; ++i)
        {
            lua_rawgeti(s, index, i + 1);
            tv.a_[i] = static_cast<float>(lua_tonumber(s, -1));
            lua_pop(s, 1);
        }
    }
    else if (TypeId<Color>::check(v->getType()))
    {
        if (!lua_istable(s, index))
            return false;
        if (lua_objlen(s, index) != 4)
            return false;

        typedef Color type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        Color& tc(av->get());

        for (size_t i = 0; i < 4; ++i)
        {
            lua_rawgeti(s, index, i + 1);
            tc.array_[i] = static_cast<uint8_t>(lua_tonumber(s, -1));
            lua_pop(s, 1);
        }
    }
    else if (TypeId<Object*>::check(v->getType()))
    {
        if (!lua_istable(s, index))
            return false;

        Object* obj =
            TodLuaScriptServer::instance()->
                unpackFromStack(s, index);

        typedef Object* type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        *av = obj;
    }
    else if (TypeId<Node*>::check(v->getType()))
    {
        if (!lua_istable(s, index))
            return false;

        Object* obj =
            TodLuaScriptServer::instance()->
                unpackFromStack(s, index);

        typedef Node* type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        *av = dynamic_cast<Node*>(obj);
    }
    else
        return false;
    return true;
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::stackToNewVariable
(lua_State* s, Variables* vs, int index)
{
    if (lua_isboolean(s, index))
    {
        typedef bool type;
        vs->add<type>((lua_tonumber(s, index) > 0)?true:false);
    }
    else if (lua_isnumber(s, index))
    {
        typedef double type;
        vs->add<type>(lua_tonumber(s, index));
    }
    else if (lua_isstring(s, index))
    {
        typedef String type;
        vs->add<type>(lua_tostring(s, index));
    }
    else if (lua_isuserdata(s, index))
    {
        typedef Node* type;
        vs->add<type>(static_cast<type>(lua_touserdata(s, index)));
    }
    else
        return false;
    return true;
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::stackToInparam(lua_State* s, Method* method)
{
    Variables* vars = method->getParameter()->in();
    if (vars->empty())
        return true;

    // pull a method's input arguments from the stack
    int top = lua_gettop(s);
    int index = top - vars->size() + 1;
    int i = 0;
    for (i = 0; index <= top; ++index, ++i)
    {
        // get the variable prepped
        if (!TodLuaScriptServer::instance()->
            stackToVariable(s, vars->get(i), index))
        {
            TOD_THROW_EXCEPTION(0,
                String("InputArgumentTypeMismatchError: "
                    "Cannot convert parameter method[%s](%d parameter)\n",
                        method->getName().toAnsiString().c_str(), i + 1));
            return false;
        }
    }

    return true;
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::outparamToStack(lua_State* s, Method* method)
{
    // empty output parameter
    Variables* vars = method->getParameter()->out();
    if (vars->empty())
    {
        lua_pushnil(s);
        return true;
    }

    // list mode
    if (vars->isForceList())
    {
        return true;
    }

    size_t num_vars = vars->size();
    for (size_t i = 0; i < num_vars; ++i)
    {
        Variable* v = vars->get(i);
        if (!variableToStack(s, v))
            return false;
    }

    return true;
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::variablesToStack(lua_State* s, Variables* vs)
{
    size_t pnum = vs->size();
    for (size_t pi = 0; pi < pnum; ++pi)
    {
        if (!variableToStack(s, vs->get(pi)))
            return false;
    }
    return true;
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::variableToStack(lua_State* s, Variable* v)
{
    if (TypeId<bool>::check(v->getType()))
    {   
        typedef bool type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        lua_pushboolean(s, av->get());
    }
    else if (TypeId<int>::check(v->getType()))
    {   
        typedef int type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        lua_pushinteger(s, av->get());
    }
    else if (TypeId<__int64>::check(v->getType()))
    {   
        typedef __int64 type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        lua_pushnumber(s, static_cast<double>(av->get()));
    }
    else if (TypeId<float>::check(v->getType()))
    {   
        typedef float type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        lua_pushnumber(s, av->get());
    }
    else if (TypeId<double>::check(v->getType()))
    {   
        typedef double type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        lua_pushnumber(s, av->get());
    }
    else if (TypeId<String>::check(v->getType()))
    {   
        typedef String type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        lua_pushstring(s, av->get().toAnsiString().c_str());
    }
    else if (TypeId<Vector3>::check(v->getType()))
    {   
        typedef Vector3 type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        const Vector3& v(av->get());

        lua_newtable(s);
        lua_pushnumber(s, 1);
        lua_pushnumber(s, v.x_);
        lua_settable(s, -3);
        lua_pushnumber(s, 2);
        lua_pushnumber(s, v.y_);
        lua_settable(s, -3);
        lua_pushnumber(s, 3);
        lua_pushnumber(s, v.z_);
        lua_settable(s, -3);
    }
    else if (TypeId<Color>::check(v->getType()))
    {
        typedef Color type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        const Color& c(av->get());

        lua_newtable(s);
        lua_pushnumber(s, 1);
        lua_pushnumber(s, c.r_);
        lua_settable(s, -3);
        lua_pushnumber(s, 2);
        lua_pushnumber(s, c.g_);
        lua_settable(s, -3);
        lua_pushnumber(s, 3);
        lua_pushnumber(s, c.b_);
        lua_settable(s, -3);
        lua_pushnumber(s, c.a_);
        lua_settable(s, -3);
    }
    else if (TypeId<Object*>::check(v->getType()))
    {   
        typedef Object* type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        thunkObject(s, av->get(), true);
    }
    else if (TypeId<Node*>::check(v->getType()))
    {   
        typedef Node* type;
        typedef SimpleVariable<type> AdaptiveVariable;
        AdaptiveVariable* av = static_cast<AdaptiveVariable*>(v);
        thunkObject(s, av->get(), false);
    }
    else
        return false;
    return true;
}


//-----------------------------------------------------------------------------
bool TodLuaScriptServer::propertyToStack
(lua_State* s, Object* obj, Property* prop)
{   
    if (TypeId<bool>::check(prop->getType()))
    {   
        typedef bool type;
        typedef SimpleProperty<type> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        lua_pushboolean(s, ap->get(obj));
    }
    else if (TypeId<int>::check(prop->getType()))
    {   
        typedef int type;
        typedef SimpleProperty<type> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        lua_pushinteger(s, ap->get(obj));
    }
    else if (TypeId<__int64>::check(prop->getType()))
    {   
        typedef __int64 type;
        typedef SimpleProperty<type> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        lua_pushnumber(s, static_cast<double>(ap->get(obj)));
    }
    else if (TypeId<float>::check(prop->getType()))
    {   
        typedef float type;
        typedef SimpleProperty<type> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        lua_pushnumber(s, ap->get(obj));
    }
    else if (TypeId<double>::check(prop->getType()))
    {   
        typedef double type;
        typedef SimpleProperty<type> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        lua_pushnumber(s, ap->get(obj));
    }
    else if (TypeId<String>::check(prop->getType()))
    {
        typedef String type;
        typedef SimpleProperty<type> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        lua_pushstring(s, ap->get(obj).toAnsiString().c_str());
    }
    else if (TypeId<Vector3>::check(prop->getType()))
    {
        typedef Vector3 type;
        typedef SimpleProperty<type> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        const Vector3& v(ap->get(obj));

        lua_newtable(s);
        lua_pushnumber(s, 1);
        lua_pushnumber(s, v.x_);
        lua_settable(s, -3);
        lua_pushnumber(s, 2);
        lua_pushnumber(s, v.y_);
        lua_settable(s, -3);
        lua_pushnumber(s, 3);
        lua_pushnumber(s, v.z_);
        lua_settable(s, -3);
    }
    else if (TypeId<Color>::check(prop->getType()))
    {
        typedef Color type;
        typedef SimpleProperty<type> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        const Color& c(ap->get(obj));

        lua_newtable(s);
        lua_pushnumber(s, 1);
        lua_pushnumber(s, c.r_);
        lua_settable(s, -3);
        lua_pushnumber(s, 2);
        lua_pushnumber(s, c.g_);
        lua_settable(s, -3);
        lua_pushnumber(s, 3);
        lua_pushnumber(s, c.b_);
        lua_settable(s, -3);
        lua_pushnumber(s, c.a_);
        lua_settable(s, -3);
    }
    else if (TypeId<Object*>::check(prop->getType()))
    {   
        typedef Object* type;
        typedef SimpleProperty<type> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        thunkObject(s, ap->get(obj), true);
    }
    else if (TypeId<Node*>::check(prop->getType()))
    {   
        typedef Node* type;
        typedef SimpleProperty<type> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        thunkObject(s, ap->get(obj), false);
    }
    else
        return false;
    return true;
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

    TodLuaScriptServer::setSingletonPath("/sys/server/script/lua");
}


//-----------------------------------------------------------------------------
void finalize_TodLua(Module* module)
{
}

//-----------------------------------------------------------------------------
DECLARE_MODULE(TodLua);
