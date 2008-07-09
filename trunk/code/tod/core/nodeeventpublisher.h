#ifndef TOD_CORE_OBJECT_NODEEVENTPUBLISHER_H
#define TOD_CORE_OBJECT_NODEEVENTPUBLISHER_H
/**
    @ingroup TodCoreObject
    @class tod::NodeEventPublisher
    @brief
*/

#include <list>
#include "tod/core/nodeevent.h"
#include "tod/core/singleton.h"

namespace tod
{
    class NodeEventPublisher : public Singleton<NodeEventPublisher>
    {
    public:
        void onAddNode(Node* node);
        void onRemoveNode(Node* node);

    private:
        typedef std::list<NodeEventSubscriber*> NodeEventSubscribers;

    private:
        NodeEventSubscribers subs_;
    };
}

#endif // TOD_CORE_OBJECT_NODEEVENTPUBLISHER_H
