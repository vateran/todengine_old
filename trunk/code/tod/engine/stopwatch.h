#ifndef TOD_ENGINE_TIME_STOPWATCH_H
#define TOD_ENGINE_TIME_STOPWATCH_H
/**
    @ingroup TodEngineTime
    @class tod::engine::TimeServer
    @brief 
*/

#include "tod/core/time.h"

namespace tod
{
namespace engine
{
    class StopWatch
    {
    public:
        StopWatch(bool start=false);

        void start();
        void reset();
        void restart();
        void pause();
        void resume();
        void step(Time d);
        Time elapse() const;
        Time delta() const;

        bool isStarted() const;
        bool isPaused() const;

    protected:
        bool start_;
        bool pause_;
        Time startTime_;
        Time pauseTime_;
    };
}
}

#endif // TOD_ENGINE_TIME_STOPWATCH_H
