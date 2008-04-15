#ifndef TOD_ENGINE_TIME_STOPWATCH_H
#define TOD_ENGINE_TIME_STOPWATCH_H
/**
    @ingroup TodEngineTime
    @class tod::engine::time::TimeServer
    @brief 
*/

#include "tod/core/time.h"

namespace tod
{
namespace engine
{
namespace time
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
        void step(core::Time d);
        core::Time elapse() const;
        core::Time delta() const;

        bool isStarted() const;
        bool isPaused() const;

    protected:
        bool start_;
        bool pause_;
        core::Time startTime_;
        core::Time pauseTime_;
    };
}
}
}

#endif // TOD_ENGINE_TIME_STOPWATCH_H
