#ifndef TOD_CORE_OBJECT_NODEEVENTPUBLISHER_H
#define TOD_CORE_OBJECT_NODEEVENTPUBLISHER_H
/**
    @ingroup TodCoreObject
    @class tod::NodeEventPublisher
    @brief
*/

#include <list>
#include "tod/core/nodeeventsubscriber.h"
#include "tod/core/singleton.h"

namespace tod
{
    class NodeEventPublisher : public Singleton<NodeEventPublisher>
    {
    public:
        void add(NodeEventSubscriber* s);
        void remove(NodeEventSubscriber* s);

        void onAttachTo(Node* parent, Node* child);
        void onDetachFrom(Node* parent, Node* child);

    private:
        typedef std::list<NodeEventSubscriber*> NodeEventSubscribers;

    private:
        NodeEventSubscribers subs_;
    };
}

#endif // TOD_CORE_OBJECT_NODEEVENTPUBLISHER_H
