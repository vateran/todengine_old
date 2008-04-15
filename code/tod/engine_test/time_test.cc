#include "tod/engine_test/time_test.h"

#include "tod/core/ref.h"
#include "tod/core/kernel.h"
#include "tod/engine/timeserver.h"
#include "tod/engine/stopwatch.h"

using namespace tod::core;
using namespace tod::engine::time;

//-----------------------------------------------------------------------------
void TimeTestCase::test_TimeServer()
{
    typedef Ref<TimeServer> RefTimeServer;
    RefTimeServer ts = Kernel::instance()->
        create(STRING("TimeServer"), STRING("/sys/server/time"));

    bool pause = false;
    //while (1)
    {
        ts->trigger();
        ts->sleep(0.01f);
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            if (pause)
                ts->pause();                
            else
                ts->resume();
            pause = !pause;
        }
        
        OutputDebugString(String("%f,", ts->getTime()).c_str());
        OutputDebugString(String("%f\n", ts->getDelta()).c_str());
    }

    ts->detach();
}


//-----------------------------------------------------------------------------
void TimeTestCase::test_StopWatch()
{
    typedef Ref<TimeServer> RefTimeServer;
    RefTimeServer ts = Kernel::instance()->
        create(STRING("TimeServer"), STRING("/sys/server/time"));

    StopWatch sw(true);
    bool pause = false;
    //while (1)
    {
        ts->trigger();
        ts->sleep(0.01f);
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            if (pause)
                sw.pause();                
            else
                sw.resume();
            pause = !pause;
        }

        OutputDebugString(String("%f,", sw.elapse()).c_str());
        OutputDebugString(String("%f\n", sw.delta()).c_str());
    }

    ts->detach();
}
