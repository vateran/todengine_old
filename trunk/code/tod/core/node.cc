#include "tod/core/node.h"

#include "tod/core/simplepropertybinder.h"

using namespace tod;

IMPLEMENT_CLASS(Node, Object);

//-----------------------------------------------------------------------------
Node::Node():
refCount_(1), parent_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
Node::~Node()
{
    if (parent_)
        parent_->onRemoveNode(this);
}


//-----------------------------------------------------------------------------
int Node::release()
{
    if (--refCount_ == 0)
    {
        if (parent_)
            parent_->onRemoveNode(this);
        delete this;
        return 0;
    }
    return refCount_;
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
        path += STRING("/");
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
}


//-----------------------------------------------------------------------------
Node::NodeIterator Node::detach()
{
    Node* parent = parent_;
    parent_ = 0;
    if (parent)
    {
        parent->onRemoveNode(this);
        parent->children_.erase(parent->children_.find(getName()));
    }
    return lastChildNode();
}


//-----------------------------------------------------------------------------
Node* Node::findChild(const name_t* name)
{
    Nodes::iterator iter = children_.find(name);
    if (children_.end() == iter)
        return 0;
    return iter->second;
}


//-----------------------------------------------------------------------------
Node* Node::findChild(const String& name)
{
    return findChild(name.c_str());
}


//-----------------------------------------------------------------------------
Node* Node::relativeNode(const Path& path)
{
    if (path == STRING("."))
        return this;
    else if (path == STRING(".."))
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
    BIND_PROPERTY(const Name&, name, &setName, &getName);
}
