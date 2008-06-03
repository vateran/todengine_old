#include "tod/engine/triggerserver.h"

#include "tod/engine/timeserver.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(TriggerServer, Node);

//-----------------------------------------------------------------------------
TriggerServer::TriggerServer():
period_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
TriggerServer::~TriggerServer()
{
    // empty
}


//-----------------------------------------------------------------------------
void TriggerServer::add(Node* node, Time period)
{
    tnodes_.push_back(Target(node, period));
}


//-----------------------------------------------------------------------------
void TriggerServer::remove(Node* node)
{
    tnodes_.remove(Target(node, 0));
}


//-----------------------------------------------------------------------------
bool TriggerServer::trigger()
{
    for (TargetNodes::iterator i = tnodes_.begin();
        i != tnodes_.end(); ++i)
    {
        Target& t = *i;
        if (t.sw_.elapse() < t.period_)
            continue;
        t.node_->trigger();
        t.sw_.reset();
    }
    TimeServer::instance()->sleep(period_);
    return true;
}


//-----------------------------------------------------------------------------
void TriggerServer::setPeriod(const Time& period)
{
    period_ = period;
}


//-----------------------------------------------------------------------------
const Time& TriggerServer::getPeriod() const
{
    return period_;
}


//-----------------------------------------------------------------------------
void TriggerServer::bindProperty()
{

}
