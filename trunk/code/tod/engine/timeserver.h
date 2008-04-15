#ifndef TOD_ENGINE_TIME_TIMESERVER_H
#define TOD_ENGINE_TIME_TIMESERVER_H
/**
    @ingroup TodEngineTime
    @class tod::engine::time::TimeServer
    @brief 
*/

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "tod/core/time.h"
#include "tod/core/node.h"
#include "tod/core/singleton3.h"

namespace tod
{
namespace engine
{
namespace time
{
    class TimeServer :
        public core::Node,
        public core::Singleton3<TimeServer>
    {
    public:
        TimeServer();
        virtual~TimeServer();
        DECLARE_CLASS(TimeServer, core::Node);

        void pause(bool pause=true);
        void resume();
        void step(core::Time d);
        void scale(float scale);

        bool isPause() const;
        float getScale() const;

        core::Time getTime() const;
        core::uint64_t getSystemTime() const;
        core::Time getDelta() const;

        void sleep(core::Time t);

        override bool trigger();
        
        static void bindProperty();
        
    private:
        static bool s_pause_;
        static float s_scale_;
        static core::Time s_delta_;
        static core::Time s_time_;
        static LARGE_INTEGER s_prevSystemTime_;
        static LARGE_INTEGER s_currentSystemTime_;
        static LARGE_INTEGER s_Frequency_;
    };
}
}
}

#endif // TOD_ENGINE_TIME_TIMESERVER_H
