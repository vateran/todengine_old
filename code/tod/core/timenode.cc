#include "tod/core/timenode.h"

#include "tod/core/timeserver.h"
#include "tod/core/simplepropertybinder.h"

using namespace tod;

IMPLEMENT_CLASS(TimeNode, Node);

//-----------------------------------------------------------------------------
TimeNode::TimeNode()
{
    // empty
}


//-----------------------------------------------------------------------------
TimeNode::~TimeNode()
{
    // empty
}


//-----------------------------------------------------------------------------
Time TimeNode::getTime() const
{
    return TimeServer::instance()->getTime();
}


//-----------------------------------------------------------------------------
void TimeNode::bindProperty()
{
    BIND_PROPERTY(Time, time, 0, &getTime);
}

