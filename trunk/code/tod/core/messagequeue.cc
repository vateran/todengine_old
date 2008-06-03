#include "tod/core/messagequeue.h"

using namespace tod;

//-----------------------------------------------------------------------------
bool MessageQueue::Message::operator < (const Message& lhs)
{
    return delay < lhs.delay;
}

