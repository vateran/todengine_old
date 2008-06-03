#include "tod/engine/timeserver.h"

#include "tod/core/simplepropertybinder.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(TimeServer, Node);

//-----------------------------------------------------------------------------
TimeServer::TimeServer()
{
    QueryPerformanceFrequency(&s_Frequency_);
    s_Frequency_.QuadPart = static_cast<DWORD>(s_Frequency_.QuadPart / 1000);
    s_prevSystemTime_.QuadPart = getSystemTime();    
}


//-----------------------------------------------------------------------------
TimeServer::~TimeServer()
{
    // empty
}


//-----------------------------------------------------------------------------
void TimeServer::pause(bool pause)
{
    s_pause_= pause;
}


//-----------------------------------------------------------------------------
void TimeServer::resume()
{
    s_pause_ = false;
}


//-----------------------------------------------------------------------------
void TimeServer::step(Time d)
{
    s_time_ += d;
}


//-----------------------------------------------------------------------------
void TimeServer::scale(float scale)
{
    s_scale_ = scale;
}


//-----------------------------------------------------------------------------
bool TimeServer::isPause() const
{
    return s_pause_;
}


//-----------------------------------------------------------------------------
float TimeServer::getScale() const
{
    return s_scale_;
}


//-----------------------------------------------------------------------------
Time TimeServer::getTime() const
{
    return s_time_;
}


//-----------------------------------------------------------------------------
uint64_t TimeServer::getSystemTime() const
{
    QueryPerformanceCounter(&s_currentSystemTime_);
    return s_currentSystemTime_.QuadPart /= s_Frequency_.QuadPart;
}


//-----------------------------------------------------------------------------
Time TimeServer::getDelta() const
{
    return s_delta_;
}


//-----------------------------------------------------------------------------
void TimeServer::sleep(Time t)
{
    Sleep(static_cast<DWORD>(t * 1000));
}


//-----------------------------------------------------------------------------
bool TimeServer::trigger()
{
    if (isPause())
    {
        s_prevSystemTime_.QuadPart = getSystemTime();
        return true;
    }
    else
    {
        s_delta_ = static_cast<Time>
            (getSystemTime() - s_prevSystemTime_.QuadPart) / 1000.0f;
        s_time_ += s_delta_ * s_scale_;
        s_prevSystemTime_ = s_currentSystemTime_;

    }

    return true;
}


//-----------------------------------------------------------------------------
void TimeServer::bindProperty()
{
    BIND_PROPERTY(bool, pause, &pause, &isPause);
    BIND_PROPERTY(float, scale, &scale, &getScale);
    BIND_PROPERTY(Time, time, 0, &getTime);
    BIND_PROPERTY(uint64_t, system_time, 0, &getSystemTime);
    BIND_PROPERTY(Time, delta, 0, &getDelta);
}


//-----------------------------------------------------------------------------
bool TimeServer::s_pause_ = false;
float TimeServer::s_scale_ = 1;
Time TimeServer::s_delta_ = 0;
Time TimeServer::s_time_ = 0;
LARGE_INTEGER TimeServer::s_prevSystemTime_;
LARGE_INTEGER TimeServer::s_currentSystemTime_;
LARGE_INTEGER TimeServer::s_Frequency_;