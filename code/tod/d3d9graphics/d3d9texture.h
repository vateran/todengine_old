#ifndef TOD_D3D9GRAPHICS_D3D9TEXTURE_H
#define TOD_D3D9GRAPHICS_D3D9TEXTURE_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::graphics::D3D9Texture
    @brief 
*/

#include <d3d9.h>
#include "tod/core/define.h"
#include "tod/engine/texture.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class D3D9Texture : public Texture
    {
    public:
        D3D9Texture(const core::Uri& uri, IDirect3DDevice9* d3d9device);
        virtual~D3D9Texture();

        override bool create(
            int width, int height, int mipmap_level,
            Format format, int usage);
        override void destroy();
        override bool preload();

        override void useAsRenderTarget(int index);

        override bool valid() const;

        override void onLostDevice();
        override void onRestoreDevice();

    public:
        IDirect3DBaseTexture9* getDirect3DTexture9();

    private:
        IDirect3DDevice9* d3d9device_;
        IDirect3DTexture9* d3d9texture_;
        int d3dusage_;
    };
}
}
}


#endif // TOD_D3D9GRAPHICS_D3D9TEXTURE_H
