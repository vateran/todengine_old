#include "tod/core/object.h"

#include "tod/core/methodbinder.h"

using namespace tod;

//-----------------------------------------------------------------------------
static void Object_b_isKindOf_v(Object* self, Parameter* param)
{
    param->out()->get<bool>(0) =
        self->isKindOf(param->in()->get<String>(0).get().c_str());
}


//-----------------------------------------------------------------------------
static void Object_s_getTypeName_v(Object* self, Parameter* param)
{
    param->out()->get<String>(0) = self->getType()->getName();
}


//-----------------------------------------------------------------------------
/**
    @out return tuple that generation names of Object
*/
static void Object_l_getGenerations_v(Object* self, Parameter* param)
{
    param->out()->clear();
    Type* type = self->getType();
    while (type)
    {
        param->out()->add<String>(type->getName());
        type = type->getBase();
    }
}


//-----------------------------------------------------------------------------
static void Object_l_getPropertyNames_s(Object* self, Parameter* param)
{
    param->out()->clear();
    Type* type = self->getType()->
        findTypeInGenerations(param->in()->get<String>(0));
    if (0 == type)
        return;
    for (Properties::iterator i = type->firstProperty();
         i != type->lastProperty(); ++i)
        param->out()->add<String>(i->first);
}


//-----------------------------------------------------------------------------
/**
    @in  type name, value
*/
static void Object_v_setProperty_ss(Object* self, Parameter* param)
{
    Property* property = self->getType()->
        findProperty(param->in()->get<String>(0));
    if (0 == property)
        return;
    property->fromString(self, param->in()->get<String>(1).get().c_str());
}


//-----------------------------------------------------------------------------
/**
    @in  property name
    @out name, value, type, read only
*/
static void Object_sssb_getProperty_s(Object* self, Parameter* param)
{
    Property* property = self->getType()->
        findProperty(param->in()->get<String>(0));
    if (0 == property)
        return;
    param->out()->get<String>(0) = property->getName();
    param->out()->get<String>(1) = property->toString(self);
    param->out()->get<String>(2) = property->getTypeKeyword();
    param->out()->get<bool>(3) = property->isReadOnly();
}


//-----------------------------------------------------------------------------
void Object::bindMethod()
{
    BIND_METHOD(b_isKindOf_v, Object_b_isKindOf_v);
    BIND_METHOD(s_getTypeName_v, Object_s_getTypeName_v);
    BIND_METHOD(l_getGenerations_v, Object_l_getGenerations_v);
    BIND_METHOD(l_getPropertyNames_s, Object_l_getPropertyNames_s);
    BIND_METHOD(sssb_getProperty_s, Object_sssb_getProperty_s);
    BIND_METHOD(v_setProperty_ss, Object_v_setProperty_ss);
}
