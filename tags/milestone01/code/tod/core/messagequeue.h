#ifndef TOD_CORE_OBJECT_MESSAGEQUEUE_H
#define TOD_CORE_OBJECT_MESSAGEQUEUE_H
/**
    
*/

#include <queue>
#include "tod/core/primitivetype.h"
#include "tod/core/time.h"

namespace tod
{
    class Method;
    class Argument;
    class MessageQueue
    {
    public:

    private:
        struct Message 
        {
            bool operator < (const Message& lhs);

            Method* method;
            const Argument* argument;
            Time delay;
        };
        typedef std::priority_queue<Message> Messages;

    private:
        Messages messages_;
    };
}

#endif // TOD_CORE_OBJECT_MESSAGEQUEUE_H
