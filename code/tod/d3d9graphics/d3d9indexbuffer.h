#ifndef TOD_D3D9GRAPHICS_D3D9INDEXBUFFER_H
#define TOD_D3D9GRAPHICS_D3D9INDEXBUFFER_H
/**
    @ingroup D3D9Graphics
    @class tod::engine::graphics::D3D9IndexBuffer
    @brief 
*/

#include <d3d9.h>
#include "tod/core/define.h"
#include "tod/core/uri.h"
#include "tod/engine/indexbuffer.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class D3D9IndexBuffer : public IndexBuffer
    {
    public:
        D3D9IndexBuffer(const core::Uri& uri, IDirect3DDevice9* d3d9device);
        virtual~D3D9IndexBuffer();

        override bool create(int num_indices, int usage, Format format);
        override void destroy();

        override bool lock(void*& ptr);
        override bool unlock();

        override bool use();
        override bool draw(PrimitiveType type);

        override bool valid() const;
        
        override void onLostDevice();
        override void onRestoreDevice();

    private:
        IDirect3DDevice9* d3d9device_;
        IDirect3DIndexBuffer9* d3d9ib_;

        D3DPOOL d3dpool_;
        int numIndices_;
        int usage_;
        int lockOption_;
        int stride_;
    };
}
}
}

#endif // TOD_D3D9GRAPHICS_D3D9INDEXBUFFER_H
