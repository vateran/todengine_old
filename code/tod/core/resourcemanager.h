#ifndef TOD_CORE_RESOURCE_RESOURCEMANAGER_H
#define TOD_CORE_RESOURCE_RESOURCEMANAGER_H
/**
    @ingroup TodCoreResource
    @class tod::ResourceManager
    @brief
*/

#include <map>
#include "tod/core/object.h"
#include "tod/core/primitivetype.h"
#include "tod/core/singleton.h"
#include "tod/core/uri.h"
#include "tod/core/resourcestorage.h"

namespace tod
{
    class ResourceProtocol;
    class ResourceImplementator;
    class ResourceManager : 
        public Object,
        public Singleton<ResourceManager>
    {
    public:
        ResourceManager();
        virtual~ResourceManager();
        DECLARE_CLASS(ResourceManager, Object);

        void initialize(const path_t* base_path);
        void finalize();

        ResourceStorage* findStorage(const String& name);
        ResourceStorages::iterator firstStorage();
        ResourceStorages::iterator lastStorage();

        void setBasePath(const path_t* path);
        const String& getBasePath() const;
		const String& getBaseAbsPath() const;

        ResourceImplementator* create(const Uri& uri);
        bool destroy(const Uri& uri);

        static void bindMethod();

    private:
        ResourceProtocol* find_protocol(const String& protocol);

    private:
        typedef std::map<String, ResourceProtocol*> ResourceProtocols;
        typedef std::map<Uri, ResourceImplementator*> Pool;     

    private:
        String basePath_;
        ResourceProtocols protocols_;
        ResourceStorages storages_;
    };
}

#endif // TOD_CORE_RESOURCE_RESOURCEMANAGER_H
