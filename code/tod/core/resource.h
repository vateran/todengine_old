#ifndef TOD_CORE_RESOURCE_RESOURCE_H
#define TOD_CORE_RESOURCE_RESOURCE_H
/**
    @ingroup TodCoreResource
    @class tod::core::Resource
    @brief
*/

#include "tod/core/primitivetype.h"
#include "tod/core/uri.h"

namespace tod
{
namespace core
{
    class ResourceImplementator;
    class Resource
    {
    public:
        enum Open
        {
            OPEN_WRITE = 1<<0,
            OPEN_READ = 1<<1,
            OPEN_BINARY = 1<<2,

            OPEN_FORCEDWORD = 0x7fffffff,
        };

    public:
        Resource(const Uri& uri);
        virtual~Resource();

        bool open(int mode);
        void close();
        int write(const buffer_t* buffer, length_t len);
        int read(buffer_t* buffer, length_t len);
        int read(dynamic_buffer_t& buffer);
        int size() const;

    private:
        ResourceImplementator* ri_;
    };
}
}

#endif // TOD_CORE_RESOURCE_RESOURCE_H
