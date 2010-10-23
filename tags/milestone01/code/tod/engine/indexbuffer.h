#ifndef TOD_ENGINE_GRAPHICS_CORE_INDEXBUFFER_H
#define TOD_ENGINE_GRAPHICS_CORE_INDEXBUFFER_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::IndexBuffer
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
    enum IndexFormat
    {
        INDEXFORMAT_INDEX16,
        INDEXFORMAT_INDEX32,
    };

    class IndexBuffer : public Resource
    {
    public:
        IndexBuffer(const Uri& uri):Resource(uri) {}
        virtual~IndexBuffer() {}

        virtual bool create(uint32_t num_indices, int usage, Format format)=0;
        virtual void destroy()=0;

        virtual bool lock(void*& ptr)=0;
        virtual bool unlock()=0;

        virtual bool use()=0;
        virtual bool draw(PrimitiveType type, int num_vertice, int num=-1)=0;

        virtual bool valid() const=0;
        bool invalid() const { return !valid(); }

        virtual uint32_t getNumIndices() const=0;

        virtual void onLostDevice()=0;
        virtual void onRestoreDevice()=0;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_INDEXBUFFER_H
