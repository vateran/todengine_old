#ifndef TOD_CORE_RESOURCE_RESOURCEPROTOCOL_H
#define TOD_CORE_RESOURCE_RESOURCEPROTOCOL_H
/**
    @ingroup TodCoreResource
    @class tod::core::ResourceProtocol
    @brief
*/

#include "tod/core/uri.h"

namespace tod
{
namespace core
{
    class ResourceImplementator;
    class ResourceProtocol
    {
    public:
        virtual~ResourceProtocol() {}

        virtual ResourceImplementator* create(const Uri& uri)=0;
        virtual bool destroy(const Uri& uri)=0;

        void setBasePath(const path_t* path);
        const String& getBasePath() const;

    private:
        String basePath_;
    };

#include "tod/core/resourceprotocol.inl"

}
}

#endif // TOD_CORE_RESOURCE_RESOURCEPROTOCOL_H