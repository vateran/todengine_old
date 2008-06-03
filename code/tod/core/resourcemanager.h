#ifndef TOD_CORE_RESOURCE_RESOURCEMANAGER_H
#define TOD_CORE_RESOURCE_RESOURCEMANAGER_H
/**
    @ingroup TodCoreResource
    @class tod::ResourceManager
    @brief
*/

#include <map>
#include "tod/core/primitivetype.h"
#include "tod/core/singleton.h"
#include "tod/core/uri.h"

namespace tod
{
    class ResourceProtocol;
    class ResourceImplementator;
    class ResourceManager : public Singleton<ResourceManager>
    {
    public:
        ResourceManager(); 
        virtual~ResourceManager();

        void initialize(const path_t* base_path);
        void finalize();

        void setBasePath(const path_t* path);

        ResourceImplementator* create(const Uri& uri);
        bool destroy(const Uri& uri);

    private:
        ResourceProtocol* find_protocol(const String& protocol);

    private:
        typedef std::map<String, ResourceProtocol*> ResourceProtocols;
        typedef std::map<Uri, ResourceImplementator*> Pool;

    private:
        String basePath_;
        ResourceProtocols protocols_;
    };
}

#endif // TOD_CORE_RESOURCE_RESOURCEMANAGER_H
