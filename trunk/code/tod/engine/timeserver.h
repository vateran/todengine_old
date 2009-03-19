#ifndef TOD_ENGINE_TIME_TIMESERVER_H
#define TOD_ENGINE_TIME_TIMESERVER_H
/**
    @ingroup TodEngineTime
    @class tod::engine::TimeServer
    @brief 
*/

#include "tod/core/define.h"
#include "tod/core/time.h"
#include "tod/core/node.h"
#include "tod/core/singleton3.h"

namespace tod
{
namespace engine
{
    class TimeServer :
        public Node,
        public Singleton3<TimeServer>
    {
    public:
        TimeServer();
        virtual~TimeServer();
        DECLARE_CLASS(TimeServer, Node);

        void pause(bool pause=true);
        void resume();
        void step(Time d);
        void scale(float scale);

        bool isPause() const;
        float getScale() const;

        Time getTime() const;
        uint64_t getSystemTime() const;
        Time getDelta() const;

        void sleep(Time t);

        override bool trigger();
        
        static void bindProperty();
        static void bindMethod();
        
    private:
        static bool s_pause_;
        static float s_scale_;
        static Time s_delta_;
        static Time s_time_;
        static LARGE_INTEGER s_prevSystemTime_;
        static LARGE_INTEGER s_currentSystemTime_;
        static LARGE_INTEGER s_Frequency_;
    };
}
}

#endif // TOD_ENGINE_TIME_TIMESERVER_H
