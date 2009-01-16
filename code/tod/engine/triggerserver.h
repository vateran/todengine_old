#ifndef TOD_ENGINE_TRIGGER_TRIGGERSERVER_H
#define TOD_ENGINE_TRIGGER_TRIGGERSERVER_H
/**
    @ingroup TodEngineResource
    @class tod::engine::Resource
    @brief 
*/

#include <list>
#include "tod/core/time.h"
#include "tod/core/ref.h"
#include "tod/core/node.h"
#include "tod/core/singleton3.h"
#include "tod/engine/stopwatch.h"

namespace tod
{
namespace engine
{
    class TriggerServer :
        public Node,
        public Singleton3<TriggerServer>
    {
    public:
        TriggerServer();
        virtual~TriggerServer();
        DECLARE_CLASS(TriggerServer, Node);

        void quit();

        void add(Node* node, Time period);
        void remove(Node* node);        

        override bool trigger();

        void setPeriod(const Time& period);
        const Time& getPeriod() const;

        static void bindMethod();
        static void bindProperty();

    private:
        typedef Ref<Node> RefNode;
        struct Target 
        {
            Target(Node* node, Time period):
            node_(node), period_(period), sw_(true) {}
            bool operator < (const Target& rhs) const
            { return node_ < rhs.node_; }
            bool operator == (const Target& rhs) const
            { return node_ == rhs.node_; }
            RefNode node_;
            Time period_;
            StopWatch sw_;
        };
        typedef std::list<Target> TargetNodes;

    private:
        TargetNodes tnodes_;
        Time period_;
        bool requestQuit_;
        
    };
}
}

#endif // TOD_ENGINE_TRIGGER_TRIGGERSERVER_H
