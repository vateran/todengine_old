#ifndef TOD_CORE_OBJECT_NODEEVENTSUBSCRIBER_H
#define TOD_CORE_OBJECT_NODEEVENTSUBSCRIBER_H
/**
    @ingroup TodCoreObject
    @class tod::NodeEventSubscriber
    @brief
*/

namespace tod
{
    class Node;
    class NodeEventSubscriber
    {
    public:
        virtual void onAttachTo(Node* parent, Node* child) {}
        virtual void onDetachFrom(Node* parent, Node* child) {}
    };
}

#endif // TOD_CORE_OBJECT_NODEEVENTSUBSCRIBER_H
