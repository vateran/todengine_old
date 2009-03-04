#ifndef TOD_CORE_RESOURCE_RESOURCECACHE_H
#define TOD_CORE_RESOURCE_RESOURCECACHE_H
/**
    @ingroup TodCoreResource
    @class tod::ResourceCache
    @brief
*/

#include <map>
#include "tod/core/primitivetype.h"
#include "tod/core/uri.h"
#include "tod/core/singleton.h"

namespace tod
{
    class ResourceImplementator;
    class ResourceCache : public Singleton<ResourceCache>
    {
    public:
        ResourceCache();
        virtual~ResourceCache();

        bool add(const Uri& uri, ResourceImplementator* ri);
        ResourceImplementator* find(const Uri& uri);

    private:
        typedef std::map<Uri, ResourceImplementator*> Cache;

    private:
        Cache cache_;
    };
}

#endif // TOD_CORE_RESOURCE_RESOURCECACHE_H
