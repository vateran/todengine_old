#ifndef TOD_CORE_RESOURCE_FSRESOURCEPROTOCOL_H
#define TOD_CORE_RESOURCE_FSRESOURCEPROTOCOL_H
/**
    @ingroup TodCoreResource
    @class tod::core::FsResourceProtocol
    @brief
*/

#include "tod/core/resourceprotocol.h"

namespace tod
{
namespace core
{
    class ResourceImplementator;
    class FsResourceProtocol : public ResourceProtocol
    {
    public:
        virtual~FsResourceProtocol();

        ResourceImplementator* create(const Uri& uri);
        bool destroy(const Uri& uri);

    private:
        void make_path(const Uri& uri);
        String combine_path(const Uri& uri);
    };

}
}

#endif // TOD_CORE_RESOURCE_FSRESOURCEPROTOCOL_H