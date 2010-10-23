#ifndef TOD_ENGINE_GRAPHICS_CORE_VERTEXBUFFER_H
#define TOD_ENGINE_GRAPHICS_CORE_VERTEXBUFFER_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::VertexBuffer
    @brief 
*/

#include "tod/core/uri.h"
#include "tod/engine/resource.h"
#include "tod/engine/types.h"

namespace tod
{
namespace engine
{
    enum VertexComponent
    {
        VERTEXCOMPONENT_COORD           = (1<<0),
        VERTEXCOMPONENT_NORMAL          = (1<<1),
        VERTEXCOMPONENT_COLOR           = (1<<2),
        VERTEXCOMPONENT_UV0             = (1<<3),
        VERTEXCOMPONENT_UV1             = (1<<4),
        VERTEXCOMPONENT_UV2             = (1<<5),
        VERTEXCOMPONENT_UV3             = (1<<6),
        VERTEXCOMPONENT_TANGENT         = (1<<7),
        VERTEXCOMPONENT_BINORMAL        = (1<<8),
        VERTEXCOMPONENT_WEIGHTS         = (1<<9),
        VERTEXCOMPONENT_JOINTINDICES    = (1<<10),
        VERTEXCOMPONENT_COORD4          = (1<<11),

        VERTEXCOMPONENT_MAX             = 12,
    };

    class VertexBuffer : public Resource
    {
    public:
        VertexBuffer(const Uri& uri):Resource(uri) {}
        virtual~VertexBuffer() {}

        virtual bool create(int num_vertice, int vertex_component, int usage)=0;
        virtual void destroy()=0;

        virtual bool lock(void*& ptr)=0;
        virtual bool unlock()=0;

        virtual bool use()=0;
        virtual bool draw(PrimitiveType type)=0;

        virtual bool valid() const=0;
        bool invalid() const { return !valid(); }

        virtual void onLostDevice()=0;
        virtual void onRestoreDevice()=0;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_VERTEXBUFFER_H
