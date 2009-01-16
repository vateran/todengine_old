#include "tod/todlua/todlua_extension.h"

#include "tod/core/exception.h"
#include "tod/core/define.h"
#include "tod/core/kernel.h"
#include "tod/core/module.h"
#include "tod/core/resourcemanager.h"
#include "tod/core/xmlserializer.h"
#include "tod/engine/triggerserver.h"
#include "tod/todlua/todluascriptserver.h"

using namespace tod;


//-----------------------------------------------------------------------------
int luacmd_StackDump(lua_State* s)
{
    TodLuaScriptServer::instance()->generateStackTrace();
    lua_settop(s, 0);
    return 0;
}


//-----------------------------------------------------------------------------
int luacmd_ResRoot(lua_State* s)
{
    const char* resource_root = 0;
    if ((1 != lua_gettop(s)) || !lua_isstring(s, -1))
    {
        TOD_THROW_EXCEPTION(0, STRING("Usage is resroot(<path>)\n"));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    resource_root = lua_tostring(s, -1);
    lua_settop(s, 0);

    ResourceManager::instance()->initialize(String("%s", resource_root).c_str());
    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_NewObj(lua_State* s)
{
    const char* type_name = 0;
    if ((1 != lua_gettop(s)) || !lua_isstring(s, -1))
    {
        TOD_THROW_EXCEPTION(0, STRING("Usage is newobj(<typename>)\n"));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    type_name = lua_tostring(s, -1);
    lua_settop(s, 0);

    Object* new_obj = Kernel::instance()->create(String(type_name).c_str());
    if (0 == new_obj)
    {
        TOD_THROW_EXCEPTION(0,
            String("Could not create object '%s'\n", type_name));
        lua_pushnil(s);
    }
    else
    {
        // create thunk and leave it on stack
        TodLuaScriptServer::instance()->thunkObject(s, new_obj);
    }

    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_New(lua_State* s)
{
    const char* type_name = 0;
    const char* path = 0;
    if ((2 != lua_gettop(s)) || !lua_isstring(s, -1) || !lua_isstring(s, -2))
    {
        TOD_THROW_EXCEPTION(0, STRING("Usage is new(<typename>, <path>)\n"));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    type_name = lua_tostring(s, -2);
    path = lua_tostring(s, -1);
    lua_settop(s, 0);

    Node* new_node = Kernel::instance()->create(String(type_name).c_str(), path);
    if (0 == new_node)
    {
        TOD_THROW_EXCEPTION(0,
            String("Could not create object '%s' of node '%s'\n",
                path, type_name));
        lua_pushnil(s);
    }
    else
    {
        // create thunk and leave it on stack
        TodLuaScriptServer::instance()->thunkObject(s, new_node);
    }

    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_Get(lua_State* s)
{
    const char* path = 0;
    if ((1 != lua_gettop(s)) || !lua_isstring(s, -1))
    {
        TOD_THROW_EXCEPTION(0, STRING("Usage is get(<path>)\n"));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    path = lua_tostring(s, -1);
    lua_settop(s, 0);

    Node* exist_node = Kernel::instance()->lookup(String(path).c_str());
    if (0 == exist_node)
    {
        TOD_THROW_EXCEPTION(0,
            String("Could not find node at '%s'\n", path));
        lua_pushnil(s);
    }
    else
    {
        // create thunk and leave it on stack
        TodLuaScriptServer::instance()->thunkObject(s, exist_node);
    }

    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_Delete(lua_State* s)
{   
    if ((1 != lua_gettop(s)))
    {
        TOD_THROW_EXCEPTION(0, STRING("Usage is delete(<path>) or delete(<obj>)\n"));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    if (lua_isstring(s, -1))
    {
        const char* path = 0;        
    }
    else if (lua_istable(s, -1))
    {
        Object* obj = TodLuaScriptServer::instance()->unpackFromStack(s, 1);
        Node* node = dynamic_cast<Node*>(obj);
        if (node)
        {
            node->release();
        }
        else
        {
            delete obj;
        }
    }
    else
    {
        TOD_THROW_EXCEPTION(0, STRING("Usage is delete(<path>) or delete(<obj>)\n"));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_Ls(lua_State* s)
{
    lua_newtable(s);
    
    Node* node = Kernel::instance()->getCwn();
    int index = 0;
    for (Node::NodeIterator i = node->firstChildNode();
         i != node->lastChildNode(); ++i, ++index)
    {
        lua_pushstring(s, i->second->getName().toAnsiString().c_str());
        TodLuaScriptServer::instance()->thunkObject(s, node);
        lua_settable(s, -3);
    }

    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_PushCwn(lua_State* s)
{
    if ((1 != lua_gettop(s)) || !lua_istable(s, -1))
    {
        TOD_THROW_EXCEPTION(0, STRING("Usage is pushcwn(<node>)\n"));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    Node* node = dynamic_cast<Node*>
        (TodLuaScriptServer::instance()->unpackFromStack(s, 1));
    if (node)
    {
        Kernel::instance()->pushCwn(node);
    }
    else
    {
        TOD_THROW_EXCEPTION(0,
            STRING("Usage is pushcwn(<node>), given object is not 'node' type\n"));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }
    
    lua_pushnil(s);
    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_PopCwn(lua_State* s)
{
    Kernel::instance()->popCwn();
    lua_pushnil(s);
    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_TodPrint(lua_State* s)
{
    if ((1 != lua_gettop(s)))
    {
        TOD_THROW_EXCEPTION(0, STRING("Usage is todprint(<string>)\n"));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    String result;
    TodLuaScriptServer::instance()->stackToString(s, 0, &result);
    tod_printf(result.c_str());
    return 0;
}


//-----------------------------------------------------------------------------
int luacmd_Exit(lua_State* s)
{
    tod::engine::TriggerServer::instance()->quit();
    return 0;
}


//-----------------------------------------------------------------------------
int luacmd_Serialize(lua_State* s)
{
    return 0;
}


//-----------------------------------------------------------------------------
int luacmd_Deserialize(lua_State* s)
{
    return 0;
}


//-----------------------------------------------------------------------------
int luacmd_GetModuleList(lua_State* s)
{
    lua_newtable(s);

    int i = 1;
    for (Kernel::Modules::iterator m = Kernel::instance()->firstModule();
         m != Kernel::instance()->lastModule(); ++m, ++i)
    {
        Module* module = m->second;
        lua_pushinteger(s, i);
        lua_pushstring(s, module->getName().toAnsiString().c_str());
        lua_settable(s, -3);
    }

    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_GetTypeList(lua_State* s)
{
    if ((1 != lua_gettop(s)) || !lua_isstring(s, -1))
    {
        TOD_THROW_EXCEPTION(0, STRING("Usage is get(<module name>)\n"));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    const char* module_name = lua_tostring(s, -1);
    lua_settop(s, 0);    

    Module* module = Kernel::instance()->findModule(String(module_name).c_str());
    if (0 == module)
    {
        TOD_THROW_EXCEPTION(0,
            String("Could not find module '%s'\n", module_name));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    lua_newtable(s);
    
    int i = 1;
    for (Module::Types::iterator t = module->firstType();
         t != module->lastType(); ++t, ++i)
    {
        const Type* type = t->second;
        lua_pushinteger(s, i);
        lua_pushstring(s, type->getName().toAnsiString().c_str());
        lua_settable(s, -3);
    }

    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_Invoke(lua_State* s)
{
    // get node instance form the table in stack
    Object* obj = TodLuaScriptServer::instance()->unpackFromStack(s, 1);
    if (0 == obj)
    {
        TOD_THROW_EXCEPTION(0, STRING("invalid object"));
        return 0;
    }
    
    // find corresponding method
    Method* method = static_cast<Method*>(lua_touserdata(s, lua_upvalueindex(1)));
    if (0 == method)
    {
        TOD_THROW_EXCEPTION(0, STRING("invalid method name"));
        return 0;
    }

    // check input argument number 
    size_t num_inarg = method->getParameter()->in()->size();
    if ((lua_gettop(s) - 1) != num_inarg)
    {
        TOD_THROW_EXCEPTION(0,
            String("InputArgumentError: %s() takes exactly %d argument (%d given)\n",
                method->getName().toAnsiString().c_str(), num_inarg, lua_gettop(s) - 1));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }
    
    if (!TodLuaScriptServer::instance()->stackToInparam(s, method))
    {
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    lua_settop(s, 0);

    method->invoke(obj);

    if (!TodLuaScriptServer::instance()->outparamToStack(s, method))
    {
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    return method->getParameter()->out()->size();
}


//-----------------------------------------------------------------------------
int luacmd_Del(lua_State* s)
{
    // get node instance form the table in stack
    Object* obj = TodLuaScriptServer::instance()->unpackFromStack(s, 1);
    if (0 == obj)
    {
        TOD_THROW_EXCEPTION(0, STRING("invalid object"));
        return 0;
    }

    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_Panic(lua_State* s)
{
    return 1;
}

