#include "tod/core/linknode.h"

#include "tod/core/kernel.h"
#include "tod/core/updatepropertyserver.h"
#include "tod/core/triggerserver.h"
#include "tod/core/simplepropertybinder.h"

using namespace tod;

IMPLEMENT_CLASS(LinkNode, Node);

//-----------------------------------------------------------------------------
LinkNode::LinkNode():
fromProperty_(0), toProperty_(0), updateProperty_(0)
{
    TriggerServer::instance()->add(this, 0);
}


//-----------------------------------------------------------------------------
LinkNode::~LinkNode()
{
    TriggerServer::instance()->remove(this);
}


//-----------------------------------------------------------------------------
void LinkNode::connect
(Node* from, Property* from_prop, Node* to, Property* to_prop)
{
    from_ = from;
    to_ = to;
    fromProperty_ = from_prop;
    toProperty_ = to_prop;
    updateProperty_ = UpdatePropertyServer::instance()->
        find(from_prop->getType(), to_prop->getType());
}


//-----------------------------------------------------------------------------
void LinkNode::connect(const String& from, const String& to)
{   
    setFromByStr(from);
    setToByStr(to);

    connect(from_, fromProperty_, to_, toProperty_);
}


//------------------------------------------------------------------------------
bool LinkNode::trigger()
{
    if (from_.invalid() || to_.invalid() ||
        fromProperty_ == 0 || toProperty_ == 0 ||
        updateProperty_ == 0)
        return true;
    
    updateProperty_->update(from_, fromProperty_, to_, toProperty_);

    return true;
}


//-----------------------------------------------------------------------------
bool LinkNode::parse_ups(const String& ups, Node** node, Property** prop)
{
    size_t o = ups.find(":", 0);
    if (o == -1) return false;

    String path(ups.substr(0, o));
    String prop_name(ups.substr(o + 1, -1));
    *node = Kernel::instance()->lookup(path);
    if (*node == 0) return false;
    *prop = (*node)->getType()->findProperty(prop_name);
    if (*prop == 0) return false;

    return true;
}


//-----------------------------------------------------------------------------
void LinkNode::setFromByStr(const String& from)
{
    Node* node = 0;
    Property* prop = 0;

    if (!parse_ups(from, &node, &prop))
    {
        fromStr_.clear();
        return;
    }

    from_ = node;
    fromProperty_ = prop;
    fromStr_ = from;
}


//-----------------------------------------------------------------------------
void LinkNode::setToByStr(const String& to)
{
    Node* node = 0;
    Property* prop = 0;

    if (!parse_ups(to, &node, &prop))
    {
        toStr_.clear();
        return;
    }

    to_ = node;
    toProperty_ = prop;
    toStr_ = to;
}


//-----------------------------------------------------------------------------
const String& LinkNode::getFromStr() const
{
    return fromStr_;
}


//-----------------------------------------------------------------------------
const String& LinkNode::getToStr() const
{
    return toStr_;
}


//-----------------------------------------------------------------------------
void LinkNode::bindProperty()
{
    BIND_PROPERTY(const String&, from, &setFromByStr, &getFromStr);
    BIND_PROPERTY(const String&, to, &setToByStr, &getToStr);
}
