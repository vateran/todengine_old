#ifndef TOD_CORE_RESOURCE_RESOURCEIMPLEMENTATOR_H
#define TOD_CORE_RESOURCE_RESOURCEIMPLEMENTATOR_H
/**
    @ingroup TodCoreResource
    @class tod::ResourceImplementator
    @brief
*/

#include "tod/core/primitivetype.h"

namespace tod
{
    class ResourceImplementator
    {
    public:
        class iterator;

    public:
        virtual~ResourceImplementator() {}

        virtual bool open(int mode)=0;
        virtual void close()=0;
        virtual int write(const buffer_t* buffer, length_t len)=0;
        virtual int read(buffer_t* buffer, length_t len)=0;
        virtual int size() const=0;
    };
}

#endif // TOD_CORE_RESOURCE_RESOURCEIMPLEMENTATOR_H