#ifndef TOD_CORE_RESOURCE_RESOURCESTORAGE_H
#define TOD_CORE_RESOURCE_RESOURCESTORAGE_H
/**
    @ingroup TodCoreResource
    @class tod::ResourceStorage
    @brief
*/

#include <list>
#include "tod/core/object.h"
#include "tod/core/primitivetype.h"
#include "tod/core/resourceentry.h"

namespace tod
{
    class ResourceProtocol;
    class ResourceStorage : public Object
    {
    public:
        ResourceStorage();
        ResourceStorage(const ResourceStorage& rs);
        ResourceStorage(const String& name, ResourceProtocol* rp);
        virtual~ResourceStorage();
        DECLARE_CLASS(ResourceStorage, Object);
        
        void setName(const String& name);
        const String& getName() const;

        const ResourceEntries& findEntries(const path_t* path, bool file);

        static void bindMethod();

    private:
        String name_;
        ResourceProtocol* protocol_;
        ResourceEntries entries_;
    };

    typedef std::list<ResourceStorage*> ResourceStorages;
}

#endif // TOD_CORE_RESOURCE_RESOURCESTORAGE_H
