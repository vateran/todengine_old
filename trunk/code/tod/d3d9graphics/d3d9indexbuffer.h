#ifndef TOD_D3D9GRAPHICS_D3D9INDEXBUFFER_H
#define TOD_D3D9GRAPHICS_D3D9INDEXBUFFER_H
/**
    @ingroup D3D9Graphics
    @class tod::engine::D3D9IndexBuffer
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
    class D3D9IndexBuffer : public IndexBuffer
    {
    public:
        D3D9IndexBuffer(const Uri& uri, IDirect3DDevice9* d3d9device);
        virtual~D3D9IndexBuffer();

        override bool create(uint32_t num_indices, int usage, Format format);
        override void destroy();

        override bool lock(void*& ptr);
        override bool unlock();

        override bool use();
        override bool draw(PrimitiveType type, int num_vertice, int num=-1);

        override bool valid() const;

        override uint32_t getNumIndices() const;
        
        override void onLostDevice();
        override void onRestoreDevice();

    private:
        IDirect3DDevice9* d3d9device_;
        IDirect3DIndexBuffer9* d3d9ib_;

        D3DPOOL d3dpool_;
        uint32_t numIndices_;
        int usage_;
        int lockOption_;
        int stride_;
        Format format_;
    };
}
}

#endif // TOD_D3D9GRAPHICS_D3D9INDEXBUFFER_H
