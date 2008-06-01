#ifndef TOD_ENGINE_GRAPHICS_CORE_INDEXBUFFER_H
#define TOD_ENGINE_GRAPHICS_CORE_INDEXBUFFER_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::graphics::IndexBuffer
    @brief 
*/

#include "tod/core/uri.h"
#include "tod/engine/resource.h"
#include "tod/engine/format.h"
#include "tod/engine/types.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    enum IndexFormat
    {
        INDEXFORMAT_INDEX16,
        INDEXFORMAT_INDEX32,
    };

    class IndexBuffer : public Resource
    {
    public:
        IndexBuffer(const core::Uri& uri):Resource(uri) {}
        virtual~IndexBuffer() {}

        virtual bool create(int num_indices, int usage, Format format)=0;
        virtual void destroy()=0;

        virtual bool lock(void*& ptr)=0;
        virtual bool unlock()=0;

        virtual bool use()=0;
        virtual bool draw(PrimitiveType type, int num=-1)=0;

        virtual bool valid() const=0;
        bool invalid() const { return !valid(); }

        virtual void onLostDevice()=0;
        virtual void onRestoreDevice()=0;
    };
}
}
}


#endif // TOD_ENGINE_GRAPHICS_CORE_INDEXBUFFER_H
