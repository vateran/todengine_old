#ifndef TOD_ENGINE_NODE_TIMENODE_H
#define TOD_ENGINE_NODE_TIMENODE_H
/**
    @ingroup TodEngine
    @class tod::engine::TimeNode
    @brief 
*/

#include "tod/core/time.h"
#include "tod/core/node.h"

namespace tod
{
namespace engine
{
    class TimeNode : public core::Node
    {
    public:
        TimeNode();
        virtual~TimeNode();
        DECLARE_CLASS(TimeNode, core::Node);

        core::Time getTime() const;

        static void bindProperty();
    };
}
}

#endif // TOD_ENGINE_NODE_TIMENODE_H
