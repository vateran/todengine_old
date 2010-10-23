#ifndef TOD_CORE_NODE_TIMENODE_H
#define TOD_CORE_NODE_TIMENODE_H
/**
    @ingroup TodCoreObject
    @class tod::core::TimeNode
    @brief 
*/

#include "tod/core/time.h"
#include "tod/core/node.h"

namespace tod
{
    class TimeNode : public Node
    {
    public:
        TimeNode();
        virtual~TimeNode();
        DECLARE_CLASS(TimeNode, Node);

        Time getTime() const;

        static void bindProperty();
    };
}

#endif // TOD_CORE_NODE_TIMENODE_H
