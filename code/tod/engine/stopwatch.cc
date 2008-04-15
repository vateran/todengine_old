#include "tod/engine/stopwatch.h"

#include "tod/engine/timeserver.h"

using namespace tod::core;
using namespace tod::engine::time;

//------------------------------------------------------------------------------
StopWatch::StopWatch(bool start):
start_(start), pause_(false), startTime_(0), pauseTime_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
void StopWatch::start()
{
    if (start_)
        return;
    startTime_ = TimeServer::instance()->getTime();
    start_ = true;
}


//-----------------------------------------------------------------------------
void StopWatch::reset()
{
    if (!start_)
        return;
    start_ = false;
    startTime_ = 0;
    pause_ = false;
    pauseTime_ = 0;
}


//-----------------------------------------------------------------------------
void StopWatch::restart()
{
    reset();
    start();
}


//-----------------------------------------------------------------------------
void StopWatch::pause()
{
    if (!start_)
        return;
    if (pause_)
        return;
    pauseTime_ = TimeServer::instance()->getTime();
    pause_ = true;
}


//-----------------------------------------------------------------------------
void StopWatch::resume()
{
    if (!start_)
        return;
    if (!pause_)
        return;
    startTime_ += TimeServer::instance()->getTime() - pauseTime_;
    pauseTime_ = 0;
    pause_ = false;
}


//-----------------------------------------------------------------------------
void StopWatch::step(Time d)
{
    startTime_ -= d;
}


//-----------------------------------------------------------------------------
Time StopWatch::elapse() const
{
    if (isStarted())
    {
        if (isPaused())
            return pauseTime_ - startTime_;
        return TimeServer::instance()->getTime() - startTime_;
    }
    else
        return 0;
}


//-----------------------------------------------------------------------------
Time StopWatch::delta() const
{
    return TimeServer::instance()->getDelta();
}


//-----------------------------------------------------------------------------
bool StopWatch::isStarted() const
{
    return start_;
}


//-----------------------------------------------------------------------------
bool StopWatch::isPaused() const
{
    return pause_;
}
