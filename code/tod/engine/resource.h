#ifndef TOD_ENGINE_RESOURE_RESOURCE_H
#define TOD_ENGINE_RESOURE_RESOURCE_H
/**
    @ingroup TodEngineResource
    @class tod::engine::Resource
    @brief 
*/

#include "tod/core/uri.h"

namespace tod
{
namespace engine
{
    class Resource
    {
    public:
        Resource(const core::Uri& uri);
        virtual~Resource();

        int addRef();
        int getRef() const;
        int release();

        virtual bool valid() const=0;
        bool invalid() const;

        const core::Uri& getUri() const;

        virtual void onLostDevice()=0;
        virtual void onRestoreDevice()=0;

    private:
        core::Uri uri_;
        int refCount_;
    };
}
}


#endif // TOD_ENGINE_RESOURE_RESOURCE_H
