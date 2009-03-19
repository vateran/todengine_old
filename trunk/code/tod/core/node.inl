//-----------------------------------------------------------------------------
inline int Node::addRef()
{
    return ++refCount_;
}


//-----------------------------------------------------------------------------
inline int Node::getRef() const
{
    return refCount_;
}


//-----------------------------------------------------------------------------
inline const String& Node::getName() const
{
    return name_;
}


//-----------------------------------------------------------------------------
inline Node* Node::getParent()
{
    return parent_;
}


//-----------------------------------------------------------------------------
template <typename DERIVED>
void Node::clearChildren()
{
    for (Nodes::iterator iter = firstChildNode();
        iter != lastChildNode();)
    {
        DERIVED* o = iter->second;
        if (o)
        {
			iter = o->detach();
            continue;
        }
		++iter;
    }
}


//-----------------------------------------------------------------------------
inline size_t Node::getNumChildren() const
{
    return children_.size();
}


//-----------------------------------------------------------------------------
inline Node::NodeIterator Node::firstChildNode()
{
    return children_.begin();
}


//-----------------------------------------------------------------------------
inline Node::NodeIterator Node::lastChildNode()
{
    return children_.end();
}


//-----------------------------------------------------------------------------
inline Node::ConstNodeIterator Node::firstChildNode() const
{
    return children_.begin();
}


//-----------------------------------------------------------------------------
inline Node::ConstNodeIterator Node::lastChildNode() const
{
    return children_.end();
}
