#ifndef TOD_CORE_UTILITY_TIME_STOPWATCH_H
#define TOD_CORE_UTILITY_TIME_STOPWATCH_H
/**
    @ingroup TodUtility
    @class tod::core::StopWatch
    @brief 
*/

#include "tod/core/time.h"

namespace tod
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

#endif // TOD_CORE_UTILITY_TIME_STOPWATCH_H
