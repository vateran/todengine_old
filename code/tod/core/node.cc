#include "tod/core/node.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/core/nodeeventpublisher.h"

using namespace tod;

IMPLEMENT_CLASS(Node, Object);

//-----------------------------------------------------------------------------
Node::Node():
refCount_(1), parent_(0)
{
    NodeEventPublisher::instance()->addRefSingleton();
}


//-----------------------------------------------------------------------------
Node::~Node()
{   
    if (parent_)
    {
        parent_->onRemoveNode(this);
        onDetachFrom(parent_);
        NodeEventPublisher::instance()->onDetachFrom(parent_, this);
    }

    NodeEventPublisher::instance()->releaseSingleton();
}


//-----------------------------------------------------------------------------
int Node::release()
{
    if (--refCount_ == 0)
    {
        // clear children
        for (Nodes::iterator iter = firstChildNode();
             iter != lastChildNode(); ++iter)
        {
            Node* node = iter->second;
            node->parent_ = 0;
        }
        children_.clear();

        // detach
        if (parent_)
        {
            parent_->onRemoveNode(this);
            onDetachFrom(parent_);
            NodeEventPublisher::instance()->onDetachFrom(parent_, this);
        }
        delete this;
        return 0;
    }
    return refCount_;
}


//-----------------------------------------------------------------------------
void Node::setName(const String& name)
{
    if (parent_)
    {
        // check node name where parent children nodes
        Node* node = parent_->findChild(name);
        if (node)
            return;
        Node* parent = parent_;
        detach();
        name_ = name;
        parent->attach(this);
    }
    else
        name_ = name;

    onSetName(name);
}


//-----------------------------------------------------------------------------
Path Node::getAbsolutePath()
{
    std::stack<Node*> s;
    Node* cur = this;
    while (cur)
    {
        if (cur->parent_)
            s.push(cur);
        cur = cur->parent_;
    }

    String path;
    while (!s.empty())
    {
        path += "/";
        path += s.top()->getName();
        s.pop();
    }

    return path;
}


//-----------------------------------------------------------------------------
void Node::attach(Node* child)
{
    children_.insert(Nodes::value_type(child->getName(), child));
    child->parent_ = this;
    onAddNode(child);
    child->onAttachTo(this);
    NodeEventPublisher::instance()->onAttachTo(this, child);
}


//-----------------------------------------------------------------------------
Node::NodeIterator Node::detach()
{
    Node* parent = parent_;
    parent_ = 0;
    if (parent)
    {
        Nodes::iterator fi = parent->children_.find(getName());
        if (parent->children_.end() != fi)
        {
            Nodes::iterator next_i = parent->children_.erase(fi);
            NodeEventPublisher::instance()->onDetachFrom(parent, this);
            this->onDetachFrom(parent);
            parent->onRemoveNode(this);
            return next_i;
        }
    }
    return lastChildNode();
}


//-----------------------------------------------------------------------------
Node* Node::findChild(const String& name)
{
    Nodes::iterator iter = children_.find(name);
    if (children_.end() == iter)
        return 0;
    return iter->second;
}


//-----------------------------------------------------------------------------
Node* Node::relativeNode(const Path& path)
{
    if (path == ".")
        return this;
    else if (path == "..")
        return getParent();
    else
    {
        Node* cur = this;
        for (Path::iterator token = path.begin(); token != path.end(); ++token)
        {
            Node* child = cur->findChild(*token);
            if (0 == child)
                return 0;
            cur = child;
        }
        return cur;
    }
}


//-----------------------------------------------------------------------------
void Node::onSetName(const String& name)
{
    // empty
}


//-----------------------------------------------------------------------------
void Node::onAttachTo(Node* parent)
{
    // empty
}


//-----------------------------------------------------------------------------
void Node::onDetachFrom(Node* parent)
{
    // empty
}

//-----------------------------------------------------------------------------
void Node::onAddNode(Node* node)
{
    // empty
}


//-----------------------------------------------------------------------------
void Node::onRemoveNode(Node* node)
{
    // empty
}


//-----------------------------------------------------------------------------
bool Node::trigger()
{
    // empty
    return true;
}


//-----------------------------------------------------------------------------
void Node::bindProperty()
{
    BIND_PROPERTY(size_t, num_children, 0, &getNumChildren);
    BIND_PROPERTY(const String&, name, &setName, &getName);
}
