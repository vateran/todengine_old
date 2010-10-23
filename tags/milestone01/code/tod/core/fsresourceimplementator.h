#ifndef TOD_CORE_RESOURCE_FSRESOURCEIMPLEMENTATOR_H
#define TOD_CORE_RESOURCE_FSRESOURCEIMPLEMENTATOR_H
/**
    @ingroup TodCoreResource
    @class tod::FsResourceImplementator
    @brief
*/

#include <fstream>
#include "tod/core/define.h"
#include "tod/core/string.h"
#include "tod/core/resourceimplementator.h"

namespace tod
{
    class FsResourceImplementator : public ResourceImplementator
    {
    public:
        FsResourceImplementator(const String& path);
        virtual~FsResourceImplementator();

        override bool open(int mode);
        override void close();
        override int write(const dynamic_buffer_t& buffer);
        override int write(const buffer_t* buffer, length_t len);
        override int read(buffer_t* buffer, length_t len);
        override int size() const;

        override bool isUpdated() const;
        override void reload();

    private:
        uint64_t get_mtime() const;

    private:        
        mutable std::fstream file_;        
        String path_;

        dynamic_buffer_t buffer_;
        uint64_t mtime_;
    };
}

#endif // TOD_CORE_RESOURCE_FSRESOURCEIMPLEMENTATOR_H