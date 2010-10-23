#include "tod/engine/triggerserver.h"

#include "tod/engine/timeserver.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(TriggerServer, Node);

//-----------------------------------------------------------------------------
TriggerServer::TriggerServer():
period_(0), requestQuit_(false)
{
    // empty
}


//-----------------------------------------------------------------------------
TriggerServer::~TriggerServer()
{
    tnodes_.clear();
}


//-----------------------------------------------------------------------------
void TriggerServer::quit()
{
    requestQuit_ = true;
}


//-----------------------------------------------------------------------------
void TriggerServer::add(Node* node, Time period)
{
    tnodes_.push_back(Target(node, period));
    addRefSingleton();
}


//-----------------------------------------------------------------------------
void TriggerServer::remove(Node* node)
{
    for (TargetNodes::iterator i = tnodes_.begin();
         i != tnodes_.end(); ++i)
    {
        if ((*i).node_ == node)
        {
            tnodes_.erase(i);
            releaseSingleton();
            return;
        }
    }
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
        t.sw_.restart();
    }
    TimeServer::instance()->sleep(period_);
    return !requestQuit_;
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
