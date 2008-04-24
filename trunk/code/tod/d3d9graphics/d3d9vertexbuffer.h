#ifndef TOD_D3D9GRAPHICS_D3D9VERTEXBUFFER_H
#define TOD_D3D9GRAPHICS_D3D9VERTEXBUFFER_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::graphics::VertexBuffer
    @brief 
*/

#include <d3d9.h>
#include "tod/core/define.h"
#include "tod/core/uri.h"
#include "tod/engine/vertexbuffer.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class D3D9VertexBuffer : public VertexBuffer
    {
    public:
        D3D9VertexBuffer(const core::Uri& uri, IDirect3DDevice9* d3d9device);
        virtual~D3D9VertexBuffer();

        override bool create(int num_vertice, int vertex_component, int usage);
        override void destroy();

        override bool lock(void*& ptr);
        override bool unlock();

        override bool use();
        override bool draw(PrimitiveType type);

        override bool valid() const;

        override void onLostDevice();
        override void onRestoreDevice();

    private:
        bool setup_vertex_declaration(int vertex_component);

    private:
        IDirect3DDevice9* d3d9device_;
        IDirect3DVertexDeclaration9* d3d9vdecl_;
        IDirect3DVertexBuffer9* d3d9vb_;

        D3DPOOL d3dpool_;
        int numVertice_;
        int vertexComponent_;
        int usage_;
        int stride_;
        int lockOption_;
        DWORD fvf_;
    };
}
}
}


#endif // TOD_D3D9GRAPHICS_D3D9VERTEXBUFFER_H
