#ifndef TOD_CORE_RESOURCE_RESOURCEENTRY_H
#define TOD_CORE_RESOURCE_RESOURCEENTRY_H
/**
    @ingroup TodCoreResource
    @class tod::ResourceEntry
    @brief
*/

#include <list>
#include "tod/core/object.h"
#include "tod/core/primitivetype.h"

namespace tod
{
    class ResourceProtocol;
    class ResourceEntry : public Object
    {
    public:
        ResourceEntry();
        ResourceEntry(const String& name, const String& type,
            bool file, bool hidden, int64_t size, int64_t write_time,
            ResourceProtocol* rp);
        virtual~ResourceEntry();
        DECLARE_CLASS(ResourceEntry, Object);
        
        const String& getName() const;
        const String& getFileType() const;
        bool isFile() const;
        bool isDirectory() const;
        bool isHidden() const;
        int64_t getSize() const;
        int64_t getWriteTime() const;

        static void bindMethod();

    private:
        String name_;
        String type_;
        bool file_;
        bool hidden_;
        int64_t size_;
        int64_t writeTime_;
        ResourceProtocol* protocol_;
    };

    typedef std::list<ResourceEntry> ResourceEntries;
}

#endif // TOD_CORE_RESOURCE_RESOURCEENTRY_H
