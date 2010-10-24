#include "tod/core/linknode.h"

#include "tod/core/methodbinder.h"

using namespace tod;

//-----------------------------------------------------------------------------
static void LinkNode_v_connect_ss(LinkNode* self, Parameter* param)
{
    self->connect(param->in()->get<String>(0), param->in()->get<String>(1));
}

//-----------------------------------------------------------------------------
void LinkNode::bindMethod()
{   
    BIND_METHOD(v_connect_ss, LinkNode_v_connect_ss);
}
