#include "tod/todlua/todlua_extension.h"

#include "tod/core/exception.h"
#include "tod/core/define.h"
#include "tod/core/kernel.h"
#include "tod/core/module.h"
#include "tod/core/color.h"
#include "tod/core/simpleproperty.h"
#include "tod/core/resourcemanager.h"
#include "tod/core/xmlserializer.h"
#include "tod/engine/triggerserver.h"
#include "tod/todlua/todluascriptserver.h"

using namespace tod;

//-----------------------------------------------------------------------------
int luacmd_StackDump(lua_State* s)
{
    String result;
    result = TodLuaScriptServer::instance()->generateStackTrace(s);
    TOD_THROW_EXCEPTION(0, result);
    lua_settop(s, 0);
    return 0;
}


//-----------------------------------------------------------------------------
int luacmd_Res(lua_State* s)
{
    TodLuaScriptServer::instance()->
        thunkObject(s, ResourceManager::instance(), false);
    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_NewObj(lua_State* s)
{
    const char* type_name = 0;
    if ((1 != lua_gettop(s)) || !lua_isstring(s, -1))
    {
        TOD_THROW_EXCEPTION(0, "Usage is newobj(<typename>)\n");
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
        TodLuaScriptServer::instance()->thunkObject(s, new_obj, true);
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
        TOD_THROW_EXCEPTION(0, "Usage is new(<typename>, <path>)\n");
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
        TodLuaScriptServer::instance()->thunkObject(s, new_node, true);
    }

    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_Get(lua_State* s)
{
    const char* path = 0;
    if ((1 != lua_gettop(s)) || !lua_isstring(s, -1))
    {
        TOD_THROW_EXCEPTION(0, "Usage is get(<path>)\n");
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    path = lua_tostring(s, -1);
    lua_settop(s, 0);

    Node* exist_node = Kernel::instance()->lookup(String(path).c_str());
    if (0 == exist_node)
    {
        lua_pushnil(s);
    }
    else
    {
        // create thunk and leave it on stack
        TodLuaScriptServer::instance()->thunkObject(s, exist_node, false);
    }

    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_Delete(lua_State* s)
{   
    if ((1 != lua_gettop(s)))
    {
        TOD_THROW_EXCEPTION(0, "Usage is delete(<path>) or delete(<obj>)\n");
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
        TOD_THROW_EXCEPTION(0, "Usage is delete(<path>) or delete(<obj>)\n");
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
        lua_pushstring(s, i->second->getName());
        TodLuaScriptServer::instance()->thunkObject(s, node, false);
        lua_settable(s, -3);
    }

    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_PushCwn(lua_State* s)
{
    if ((1 != lua_gettop(s)) || !lua_istable(s, -1))
    {
        TOD_THROW_EXCEPTION(0, "Usage is pushcwn(<node>)\n");
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
            "Usage is pushcwn(<node>), given object is not 'node' type\n");
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
        TOD_THROW_EXCEPTION(0, "Usage is todprint(<string>)\n");
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    String result;
    TodLuaScriptServer::instance()->stackToString(s, 0, &result);
    printf(result.c_str());
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
    const char* uri = 0;
    if ((2 != lua_gettop(s)) || !lua_isstring(s, 1) || !lua_istable(s, 2))
    {
        TOD_THROW_EXCEPTION(0, "Usage is serialize(<uri>, <obj>)\n");
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }
    
    uri = lua_tostring(s, 1);
    Node* node = dynamic_cast<Node*>
        (TodLuaScriptServer::instance()->unpackFromStack(s, 2));
    if (node)
    {
        Kernel::instance()->pushCwn(node);
        XmlSerializer serializer;
        serializer.serialize(String(uri), node);
    }

    lua_settop(s, 0);
    lua_pushnil(s);
    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_Deserialize(lua_State* s)
{
    const char* uri = 0;
    const char* new_name = 0;
    XmlSerializer serializer;

    if (lua_gettop(s) == 2)
    {
        if (!lua_istable(s, 1) || !lua_isstring(s, 2))
            goto ON_ARG_ERROR;
    }
    else if (lua_gettop(s) == 3)
    {
        if (!lua_istable(s, 1) || !lua_isstring(s, 2) || !lua_isstring(s, 3))
            goto ON_ARG_ERROR;
    }
    else
        goto ON_ARG_ERROR;
    
    Node* parent_node = dynamic_cast<Node*>
        (TodLuaScriptServer::instance()->unpackFromStack(s, 1));
    uri = lua_tostring(s, 2);
    if (lua_gettop(s) == 3)
        new_name = lua_tostring(s, 3);
    
    Object* result_o = 0;
    if (new_name)
        result_o = serializer.deserialize(
            parent_node, String(uri), String(new_name).c_str());
    else
        result_o = serializer.deserialize(parent_node, String(uri), 0);
    if (0 == result_o)
    {
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    // create thunk and leave it on stack
    TodLuaScriptServer::instance()->thunkObject(s, result_o, false);
    return 1;

ON_ARG_ERROR:
    TOD_THROW_EXCEPTION(0, "Usage is deserialize(<parent>, <uri>, <new name>)\n");
    lua_settop(s, 0);
    lua_pushnil(s);
    return 1;
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
        lua_pushstring(s, module->getName());
        lua_settable(s, -3);
    }

    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_GetTypeList(lua_State* s)
{
    if ((1 != lua_gettop(s)) || !lua_isstring(s, -1))
    {
        TOD_THROW_EXCEPTION(0, "Usage is get(<module name>)\n");
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
        lua_pushstring(s, type->getName());
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
        TOD_THROW_EXCEPTION(0, "invalid object");
        return 0;
    }
    
    // find corresponding method
    Method* method = static_cast<Method*>(lua_touserdata(s, lua_upvalueindex(1)));
    if (0 == method)
    {
        TOD_THROW_EXCEPTION(0, "invalid method name");
        return 0;
    }

    // check input argument number 
    size_t num_inarg = method->getParameter()->in()->size();
    if ((lua_gettop(s) - 1) != num_inarg)
    {
        TOD_THROW_EXCEPTION(0,
            String("InputArgumentError: %s() takes exactly %d argument (%d given)\n",
                method->getName().c_str(), num_inarg, lua_gettop(s) - 1));
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
bool set_property__(lua_State* s, Object* obj, Property* prop)
{
    if (TypeId<bool>::check(prop->getType()))
    {   
        if (lua_isboolean(s, 3))
        {
            typedef bool type;
            typedef SimpleProperty<type> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->set(obj, (lua_toboolean(s, 3)>0)?true:false);
        }
    }
    else if (TypeId<int>::check(prop->getType()))
    {   
        if (lua_isnumber(s, 3))
        {
            typedef int type;
            typedef SimpleProperty<type> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->set(obj, static_cast<type>(lua_tonumber(s, 3)));
        }
    }
    else if (TypeId<__int64>::check(prop->getType()))
    {   
        if (lua_isnumber(s, 3))
        {
            typedef __int64 type;
            typedef SimpleProperty<type> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->set(obj, static_cast<type>(lua_tonumber(s, 3)));
        }
    }
    else if (TypeId<float>::check(prop->getType()))
    {   
        if (lua_isnumber(s, 3))
        {
            typedef float type;
            typedef SimpleProperty<type> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->set(obj, static_cast<type>(lua_tonumber(s, 3)));
        }
    }
    else if (TypeId<double>::check(prop->getType()))
    {   
        if (lua_isnumber(s, 3))
        {
            typedef double type;
            typedef SimpleProperty<type> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->set(obj, static_cast<type>(lua_tonumber(s, 3)));
        }
    }
    else if (TypeId<const Vector3&>::check(prop->getType()))
    {   
        if (lua_istable(s, 3))
        {
            typedef const Vector3& type;
            typedef SimpleProperty<type> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            
            Vector3 v;
            for (int i = 0; i < 3; ++i)
            {
                lua_rawgeti(s, 3, 1 + i);
                if (!lua_isnumber(s, 4))
                    return false;
                double value = lua_tonumber(s, 4);
                lua_pop(s, 1);
                v.a_[i] = static_cast<float>(value);
            }
            ap->set(obj, v);
        }
    }
    else if (TypeId<const Color&>::check(prop->getType()))
    {   
        if (lua_istable(s, 3))
        {
            typedef const Color& type;
            typedef SimpleProperty<type> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            
            Color c;
            for (int i = 0; i < 4; ++i)
            {
                lua_rawgeti(s, 3, 1 + i);
                if (!lua_isnumber(s, 4))
                    return false;
                double value = lua_tonumber(s, 4);
                lua_pop(s, 1);
                c.array_[i] = static_cast<uint8_t>(value);
            }
            ap->set(obj, c);
        }
    }
    else if (TypeId<const String&>::check(prop->getType()))
    {   
        if (lua_isstring(s, 3))
        {
            typedef const String& type;
            typedef SimpleProperty<type> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->set(obj, String(lua_tostring(s, 3)));
        }
    }
    else if (TypeId<const Uri&>::check(prop->getType()))
    {   
        if (lua_isstring(s, 3))
        {
            typedef const Uri& type;
            typedef SimpleProperty<type> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->set(obj, Uri(lua_tostring(s, 3)));
        }
    }
    else
        return false;
    return true;
}


//-----------------------------------------------------------------------------
int luacmd_SetProperty(lua_State* s)
{
    // get node instance form the table in stack
    Object* obj = TodLuaScriptServer::instance()->unpackFromStack(s, 1);
    if (0 == obj)
    {
        TOD_THROW_EXCEPTION(0, "invalid object");
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    // find corresponding property
    const char* name = lua_tostring(s, 2);
    Type* type = obj->getType();
    Property* prop = type->findProperty(String(name));
    if (0 == prop)
    {
        TOD_THROW_EXCEPTION(0, String("could not found property(%s)", name));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    if (!set_property__(s, obj, prop))
    {
        TOD_THROW_EXCEPTION(0, String("mismatch property type(%s)", name));
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    lua_settop(s, 0);
    lua_pushnil(s);
    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_GetProperty(lua_State* s)
{
    // get node instance form the table in stack
    Object* obj = TodLuaScriptServer::instance()->unpackFromStack(s, 1);
    if (0 == obj)
    {
        TOD_THROW_EXCEPTION(0, "invalid object");
        return 0;
    }
    
    // find corresponding property
    Property* prop = static_cast<Property*>(lua_touserdata(s, lua_upvalueindex(1)));
    if (0 == prop)
    {
        TOD_THROW_EXCEPTION(0, "invalid prop name");
        return 0;
    }

    lua_settop(s, 0);
    TodLuaScriptServer::instance()->propertyToStack(s, obj, prop);
    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_Del(lua_State* s)
{
    // get node instance form the table in stack
    TodLuaObject* result =
        static_cast<TodLuaObject*>
            (lua_touserdata(s, 1));

    Node* node = dynamic_cast<Node*>(result->object_);
    if (node)
    {
        node->release();
    }
    else
    {
        if (result->createdByLua_)
            delete result->object_;
    }

    lua_settop(s, 0);
    lua_pushnil(s);
    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_Panic(lua_State* s)
{
    return 1;
}


//-----------------------------------------------------------------------------
int luacmd_WaitSec(lua_State* s)
{
    lua_pushlightuserdata(s, s);
    lua_gettable(s, LUA_REGISTRYINDEX);
    TodLuaThread* thread = thread = static_cast<TodLuaThread*>(lua_touserdata(s, -1));
    if (0 == thread)
    {
        TOD_THROW_EXCEPTION(0, "unable to get TodLuaThread object");
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    thread->waitSecond(lua_tonumber(s, 1));
    
    lua_settop(s, 0);    

    return (lua_yield(s, 0));
}


//-----------------------------------------------------------------------------
int luacmd_WaitFrame(lua_State* s)
{
    lua_pushlightuserdata(s, s);
    lua_gettable(s, LUA_REGISTRYINDEX);
    TodLuaThread* thread = thread = static_cast<TodLuaThread*>(lua_touserdata(s, -1));
    if (0 == thread)
    {
        TOD_THROW_EXCEPTION(0, "unable to get TodLuaThread object");
        lua_settop(s, 0);
        lua_pushnil(s);
        return 1;
    }

    thread->waitFrame(static_cast<int>(lua_tonumber(s, 1)));
    
    lua_settop(s, 0);    

    return (lua_yield(s, 0));
}
