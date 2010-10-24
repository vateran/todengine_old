#include "tod/core/updatepropertyserver.h"

#include "tod/core/vector2.h"
#include "tod/core/vector3.h"
#include "tod/core/vector4.h"
#include "tod/core/matrix44.h"
#include "tod/core/color.h"
#include "tod/core/simpleproperty.h"

using namespace tod;

IMPLEMENT_CLASS(UpdatePropertyServer, Node);

//------------------------------------------------------------------------------
#define INSERT_UPDATEPROPERTYEQUALTYPE(type) \
updateProperties_.insert(UpdateProperties::value_type(\
    PropertyTypeId(TypeId<type>::id(), TypeId<type>::id()),\
    new UpdatePropertyEqualType<type>()));
#define INSERT_UPDATEPROPERTY(from_type, to_type) \
updateProperties_.insert(UpdateProperties::value_type(\
    PropertyTypeId(TypeId<from_type>::id(), TypeId<to_type>::id()),\
    new UpdateProperty<from_type, to_type>()));
UpdatePropertyServer::UpdatePropertyServer()
{
    INSERT_UPDATEPROPERTYEQUALTYPE(bool);
    INSERT_UPDATEPROPERTYEQUALTYPE(int);
    INSERT_UPDATEPROPERTYEQUALTYPE(int64_t);
    INSERT_UPDATEPROPERTYEQUALTYPE(float);
    INSERT_UPDATEPROPERTYEQUALTYPE(double);
    INSERT_UPDATEPROPERTYEQUALTYPE(String);
    INSERT_UPDATEPROPERTYEQUALTYPE(Vector2);
    INSERT_UPDATEPROPERTYEQUALTYPE(Vector3);
    INSERT_UPDATEPROPERTYEQUALTYPE(Vector4);
    INSERT_UPDATEPROPERTYEQUALTYPE(Time);

    INSERT_UPDATEPROPERTY(int, bool);
    INSERT_UPDATEPROPERTY(int, int64_t);
    INSERT_UPDATEPROPERTY(int, float);
    INSERT_UPDATEPROPERTY(int, double);

    INSERT_UPDATEPROPERTY(int64_t, bool);
    INSERT_UPDATEPROPERTY(int64_t, int);
    INSERT_UPDATEPROPERTY(int64_t, float);
    INSERT_UPDATEPROPERTY(int64_t, double);

    INSERT_UPDATEPROPERTY(float, bool);
    INSERT_UPDATEPROPERTY(float, int);
    INSERT_UPDATEPROPERTY(float, int64_t);
    INSERT_UPDATEPROPERTY(float, double);

    INSERT_UPDATEPROPERTY(double, bool);
    INSERT_UPDATEPROPERTY(double, int);
    INSERT_UPDATEPROPERTY(double, int64_t);
    INSERT_UPDATEPROPERTY(double, float);
}


//-----------------------------------------------------------------------------
template <typename T>
void UpdatePropertyServer::UpdatePropertyEqualType<T>::update
(Object* from, Property* from_p, Object* to, Property* to_p)
{
    typedef SimpleProperty<T> TypedProperty;
    TypedProperty* from_property = static_cast<TypedProperty*>(from_p);
    TypedProperty* to_property = static_cast<TypedProperty*>(to_p);
    to_property->set(to, from_property->get(from));
}


//-----------------------------------------------------------------------------
template <>
void UpdatePropertyServer::UpdateProperty<int, bool>::update
(Object* from, Property* from_p, Object* to, Property* to_p)
{
    typedef SimpleProperty<int> FromProperty;
    typedef SimpleProperty<bool> ToProperty;
    FromProperty* from_property = static_cast<FromProperty*>(from_p);
    ToProperty* to_property = static_cast<ToProperty*>(to_p);
    to_property->set(to, from_property->get(from)?true:false);
}


//-----------------------------------------------------------------------------
template <>
void UpdatePropertyServer::UpdateProperty<int64_t, bool>::update
(Object* from, Property* from_p, Object* to, Property* to_p)
{
    typedef SimpleProperty<int64_t> FromProperty;
    typedef SimpleProperty<bool> ToProperty;
    FromProperty* from_property = static_cast<FromProperty*>(from_p);
    ToProperty* to_property = static_cast<ToProperty*>(to_p);
    to_property->set(to, from_property->get(from)?true:false);
}


//-----------------------------------------------------------------------------
template <>
void UpdatePropertyServer::UpdateProperty<float, bool>::update
(Object* from, Property* from_p, Object* to, Property* to_p)
{
    typedef SimpleProperty<float> FromProperty;
    typedef SimpleProperty<bool> ToProperty;
    FromProperty* from_property = static_cast<FromProperty*>(from_p);
    ToProperty* to_property = static_cast<ToProperty*>(to_p);
    to_property->set(to, from_property->get(from)?true:false);
}


//-----------------------------------------------------------------------------
template <>
void UpdatePropertyServer::UpdateProperty<double, bool>::update
(Object* from, Property* from_p, Object* to, Property* to_p)
{
    typedef SimpleProperty<double> FromProperty;
    typedef SimpleProperty<bool> ToProperty;
    FromProperty* from_property = static_cast<FromProperty*>(from_p);
    ToProperty* to_property = static_cast<ToProperty*>(to_p);
    to_property->set(to, from_property->get(from)?true:false);
}


//-----------------------------------------------------------------------------
template <>
void UpdatePropertyServer::UpdateProperty<bool, String>::update
(Object* from, Property* from_p, Object* to, Property* to_p)
{
    typedef SimpleProperty<bool> FromProperty;
    typedef SimpleProperty<String> ToProperty;
    FromProperty* from_property = static_cast<FromProperty*>(from_p);
    ToProperty* to_property = static_cast<ToProperty*>(to_p);
    to_property->set(to,
        from_property->get(from)?"true":"false");
}


//-----------------------------------------------------------------------------
#define UPDATE_PROPERTY(from_type, to_type) \
template <>\
void UpdatePropertyServer::UpdateProperty<from_type, to_type>::update\
(Object* from, Property* from_p, Object* to, Property* to_p)\
{\
    typedef SimpleProperty<from_type> FromProperty;\
    typedef SimpleProperty<to_type> ToProperty;\
    FromProperty* from_property = static_cast<FromProperty*>(from_p);\
    ToProperty* to_property = static_cast<ToProperty*>(to_p);\
    to_property->set(to, static_cast<to_type>(from_property->get(from)));\
}
UPDATE_PROPERTY(bool, int);
UPDATE_PROPERTY(bool, int64_t);
UPDATE_PROPERTY(bool, float);
UPDATE_PROPERTY(bool, double);

UPDATE_PROPERTY(int, int64_t);
UPDATE_PROPERTY(int, float);
UPDATE_PROPERTY(int, double);

UPDATE_PROPERTY(int64_t, int);
UPDATE_PROPERTY(int64_t, float);
UPDATE_PROPERTY(int64_t, double);

UPDATE_PROPERTY(float, int);
UPDATE_PROPERTY(float, int64_t);
UPDATE_PROPERTY(float, double);

UPDATE_PROPERTY(double, int);
UPDATE_PROPERTY(double, int64_t);
UPDATE_PROPERTY(double, float);



//-----------------------------------------------------------------------------
UpdatePropertyServer::PropertyTypeId::PropertyTypeId(type_id from, type_id to):
from_(from), to_(to)
{
    // empty
}


//-----------------------------------------------------------------------------
bool UpdatePropertyServer::PropertyTypeId::operator < (const PropertyTypeId& rhs) const
{
    if (from_ < rhs.from_)
        return true;
    else if (from_ == rhs.from_)
    {
        if (to_ < rhs.to_)
            return true;
    }
    return false;
}



//-----------------------------------------------------------------------------
UpdatePropertyServer::~UpdatePropertyServer()
{
    for (UpdateProperties::iterator i = updateProperties_.begin();
         i != updateProperties_.end(); ++i)
         delete i->second;
}


//------------------------------------------------------------------------------
bool UpdatePropertyServer::update()
{
    return true;
}


//------------------------------------------------------------------------------
UpdatePropertyBase* UpdatePropertyServer::find
(type_id from, type_id to)
{
    UpdateProperties::iterator find_iter = 
        updateProperties_.find(PropertyTypeId(from, to));
    if (updateProperties_.end() == find_iter)
        return 0;
    return find_iter->second;
}
