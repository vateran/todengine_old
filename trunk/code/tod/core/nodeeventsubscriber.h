#ifndef TOD_CORE_OBJECT_NODEEVENTSUBSCRIBER_H
#define TOD_CORE_OBJECT_NODEEVENTSUBSCRIBER_H
/**
    @ingroup TodCoreObject
    @class tod::NodeEventSubscriber
    @brief
*/

namespace tod
{
    class NodeEventSubscriber
    {
    public:
        virtual void onAddNode(Node* node);
        virtual void onRemoveNode(Node* node);
    };
}

#endif // TOD_CORE_OBJECT_NODEEVENTSUBSCRIBER_H
