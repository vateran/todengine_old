#include "tod/engine/timenode.h"

#include "tod/engine/timeserver.h"
#include "tod/core/simplepropertybinder.h"

using namespace tod::core;
using namespace tod::engine;
using namespace tod::engine::time;

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

