#include "tod/core/node.h"

#include "tod/core/methodbinder.h"

using namespace tod;

//-----------------------------------------------------------------------------
static void Node_i_addRef_v(Node* self, Parameter* param)
{
    param->out()->get<int>(0) = self->addRef();
}


//-----------------------------------------------------------------------------
static void Node_i_release_v(Node* self, Parameter* param)
{
    param->out()->get<int>(0) = self->release();
}


//-----------------------------------------------------------------------------
static void Node_i_getRef_v(Node* self, Parameter* param)
{
    param->out()->get<int>(0) = self->getRef();
}


//-----------------------------------------------------------------------------
static void Node_v_setName_s(Node* self, Parameter* param)
{
    self->setName(param->in()->get<Name>(0));
}


//-----------------------------------------------------------------------------
static void Node_s_getName_v(Node* self, Parameter* param)
{
    param->out()->get<String>(0) = self->getName();
}


//-----------------------------------------------------------------------------
static void Node_s_getAbsolutePath_v(Node* self, Parameter* param)
{
    param->out()->get<String>(0) = self->getAbsolutePath();
}


//-----------------------------------------------------------------------------
static void Node_o_getParent_v(Node* self, Parameter* param)
{
    param->out()->get<Node*>(0) = self->getParent();
}


//-----------------------------------------------------------------------------
static void Node_v_attach_o(Node* self, Parameter* param)
{
    self->attach(param->in()->get<Node*>(0));
}


//-----------------------------------------------------------------------------
static void Node_v_detach_v(Node* self, Parameter* param)
{
    self->detach();
}


//-----------------------------------------------------------------------------
static void Node_v_clearChildren_v(Node* self, Parameter* param)
{
    self->clearChildren<Node>();    
}


//-----------------------------------------------------------------------------
static void Node_i_getNumChildren_v(Node* self, Parameter* param)
{
    param->out()->get<int>(0) = self->getNumChildren();
}


//-----------------------------------------------------------------------------
static void Node_o_findChild_s(Node* self, Parameter* param)
{
    param->out()->get<Node*>(0) = self->findChild(param->in()->get<String>(0));
}


//-----------------------------------------------------------------------------
static void Node_o_relativeNode_s(Node* self, Parameter* param)
{
    param->out()->get<Node*>(0) =
        self->relativeNode(param->in()->get<Path>(0));
}


//-----------------------------------------------------------------------------
static void Node_l_getChildren_v(Node* self, Parameter* param)
{
    param->out()->clear();
    for (Node::NodeIterator i = self->firstChildNode();
         i != self->lastChildNode(); ++i)
        param->out()->add<Node*>(i->second);
}

//-----------------------------------------------------------------------------
static void Node_b_trigger_v(Node* self, Parameter* param)
{
    param->out()->get<bool>(0) = self->trigger();
}

//-----------------------------------------------------------------------------
void Node::bindMethod()
{
    BIND_METHOD(i_addRef_v, Node_i_addRef_v);
    BIND_METHOD(i_release_v, Node_i_release_v);
    BIND_METHOD(i_getRef_v, Node_i_getRef_v);
    BIND_METHOD(v_setName_s, Node_v_setName_s);
    BIND_METHOD(s_getName_v, Node_s_getName_v);
    BIND_METHOD(s_getAbsolutePath_v, Node_s_getAbsolutePath_v);
    BIND_METHOD(o_getParent_v, Node_o_getParent_v);
    BIND_METHOD(v_attach_o, Node_v_attach_o);
    BIND_METHOD(v_detach_v, Node_v_detach_v);
    BIND_METHOD(v_clearChildren_v, Node_v_clearChildren_v);
    BIND_METHOD(i_getNumChildren_v, Node_i_getNumChildren_v);
    BIND_METHOD(o_findChild_s, Node_o_findChild_s);
    BIND_METHOD(o_relativeNode_s, Node_o_relativeNode_s);
    BIND_METHOD(l_getChildren_v, Node_l_getChildren_v);
    BIND_METHOD(b_trigger_v, Node_b_trigger_v);
}
