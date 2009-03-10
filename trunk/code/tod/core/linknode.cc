#include "tod/core/linknode.h"

#include "tod/core/vector2.h"
#include "tod/core/vector3.h"
#include "tod/core/vector4.h"
#include "tod/core/matrix44.h"
#include "tod/core/color.h"
#include "tod/core/simpleproperty.h"

using namespace tod;

IMPLEMENT_CLASS(LinkNode, Node);

//-----------------------------------------------------------------------------
LinkNode::LinkNode():
fromProperty_(0), toProperty_(0), updateProperty_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
LinkNode::~LinkNode()
{
    // empy
}


//-----------------------------------------------------------------------------
void LinkNode::connect
(Node* from, Property* from_prop, Node* to, Property* to_prop)
{
    from_ = from;
    to_ = to;
    fromProperty_ = from_prop;
    toProperty_ = to_prop;
    updateProperty_ = s_updatePropertyServer_.find(
        from_prop->getType(), to_prop->getType());
}


//-----------------------------------------------------------------------------
void LinkNode::connect(const String& from, const String& to)
{
    size_t o = from.find(".", 0);
    if (o == -1)
        return;
}


//------------------------------------------------------------------------------
void LinkNode::update()
{
    if (from_.invalid() || to_.invalid() ||
        fromProperty_ == 0 || toProperty_ == 0 ||
        updateProperty_ == 0)
        return;
    updateProperty_->update(from_, fromProperty_, to_, toProperty_);
}


//-----------------------------------------------------------------------------
template <typename T>
void LinkNode::UpdatePropertyEqualType<T>::update
(Object* from, Property* from_p, Object* to, Property* to_p)
{
    typedef SimpleProperty<T> TypedProperty;
    TypedProperty* from_property = static_cast<TypedProperty*>(from_p);
    TypedProperty* to_property = static_cast<TypedProperty*>(to_p);
    to_property->set(to, from_property->get(from));
}


//-----------------------------------------------------------------------------
template <>
void LinkNode::UpdateProperty<int, bool>::update
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
void LinkNode::UpdateProperty<__int64, bool>::update
(Object* from, Property* from_p, Object* to, Property* to_p)
{
    typedef SimpleProperty<__int64> FromProperty;
    typedef SimpleProperty<bool> ToProperty;
    FromProperty* from_property = static_cast<FromProperty*>(from_p);
    ToProperty* to_property = static_cast<ToProperty*>(to_p);
    to_property->set(to, from_property->get(from)?true:false);
}


//-----------------------------------------------------------------------------
template <>
void LinkNode::UpdateProperty<float, bool>::update
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
void LinkNode::UpdateProperty<double, bool>::update
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
void LinkNode::UpdateProperty<bool, String>::update
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
void LinkNode::UpdateProperty<from_type, to_type>::update\
(Object* from, Property* from_p, Object* to, Property* to_p)\
{\
    typedef SimpleProperty<from_type> FromProperty;\
    typedef SimpleProperty<to_type> ToProperty;\
    FromProperty* from_property = static_cast<FromProperty*>(from_p);\
    ToProperty* to_property = static_cast<ToProperty*>(to_p);\
    to_property->set(to, static_cast<to_type>(from_property->get(from)));\
}
UPDATE_PROPERTY(bool, int);
UPDATE_PROPERTY(bool, __int64);
UPDATE_PROPERTY(bool, float);
UPDATE_PROPERTY(bool, double);

UPDATE_PROPERTY(int, __int64);
UPDATE_PROPERTY(int, float);
UPDATE_PROPERTY(int, double);

UPDATE_PROPERTY(__int64, int);
UPDATE_PROPERTY(__int64, float);
UPDATE_PROPERTY(__int64, double);

UPDATE_PROPERTY(float, int);
UPDATE_PROPERTY(float, __int64);
UPDATE_PROPERTY(float, double);

UPDATE_PROPERTY(double, int);
UPDATE_PROPERTY(double, __int64);
UPDATE_PROPERTY(double, float);

//------------------------------------------------------------------------------
#define INSERT_UPDATEPROPERTYEQUALTYPE(type) \
updateProperties_.insert(UpdateProperties::value_type(\
    PropertyTypeId(TypeId<type>::id(), TypeId<type>::id()),\
    new UpdatePropertyEqualType<type>()));
#define INSERT_UPDATEPROPERTY(from_type, to_type) \
updateProperties_.insert(UpdateProperties::value_type(\
    PropertyTypeId(TypeId<from_type>::id(), TypeId<to_type>::id()),\
    new UpdateProperty<from_type, to_type>()));
LinkNode::UpdatePropertyServer::UpdatePropertyServer()
{
    INSERT_UPDATEPROPERTYEQUALTYPE(bool);
    INSERT_UPDATEPROPERTYEQUALTYPE(int);
    INSERT_UPDATEPROPERTYEQUALTYPE(__int64);
    INSERT_UPDATEPROPERTYEQUALTYPE(float);
    INSERT_UPDATEPROPERTYEQUALTYPE(double);
    INSERT_UPDATEPROPERTYEQUALTYPE(String);
    INSERT_UPDATEPROPERTYEQUALTYPE(Vector2);
    INSERT_UPDATEPROPERTYEQUALTYPE(Vector3);
    INSERT_UPDATEPROPERTYEQUALTYPE(Vector4);
    INSERT_UPDATEPROPERTYEQUALTYPE(Time);

    INSERT_UPDATEPROPERTY(int, bool);
    INSERT_UPDATEPROPERTY(int, __int64);
    INSERT_UPDATEPROPERTY(int, float);
    INSERT_UPDATEPROPERTY(int, double);

    INSERT_UPDATEPROPERTY(__int64, bool);
    INSERT_UPDATEPROPERTY(__int64, int);
    INSERT_UPDATEPROPERTY(__int64, float);
    INSERT_UPDATEPROPERTY(__int64, double);

    INSERT_UPDATEPROPERTY(float, bool);
    INSERT_UPDATEPROPERTY(float, int);
    INSERT_UPDATEPROPERTY(float, __int64);
    INSERT_UPDATEPROPERTY(float, double);

    INSERT_UPDATEPROPERTY(double, bool);
    INSERT_UPDATEPROPERTY(double, int);
    INSERT_UPDATEPROPERTY(double, __int64);
    INSERT_UPDATEPROPERTY(double, float);
}


//-----------------------------------------------------------------------------
LinkNode::UpdatePropertyServer::~UpdatePropertyServer()
{
    for (UpdateProperties::iterator i = updateProperties_.begin();
         i != updateProperties_.end(); ++i)
         delete i->second;
}


//------------------------------------------------------------------------------
LinkNode::UpdatePropertyBase* LinkNode::UpdatePropertyServer::find
(type_id from, type_id to)
{
    UpdateProperties::iterator find_iter = 
        updateProperties_.find(PropertyTypeId(from, to));
    if (updateProperties_.end() == find_iter)
        return 0;
    return find_iter->second;
}


//-----------------------------------------------------------------------------
LinkNode::UpdatePropertyServer LinkNode::s_updatePropertyServer_;


//-----------------------------------------------------------------------------
LinkNode::PropertyTypeId::PropertyTypeId
(type_id from, type_id to): from_(from), to_(to)
{
    // empty
}


//-----------------------------------------------------------------------------
bool LinkNode::PropertyTypeId::operator < (const PropertyTypeId& rhs) const
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
