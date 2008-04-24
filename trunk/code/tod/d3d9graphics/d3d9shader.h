#ifndef TOD_D3D9GRAPHICS_D3D9SHADER_H
#define TOD_D3D9GRAPHICS_D3D9SHADER_H
/**
    @ingroup D3D9Graphics
    @class tod::engine::graphics::D3D9Shader
    @brief 
*/

#include <d3dx9.h>
#include "tod/core/define.h"
#include "tod/core/uri.h"
#include "tod/engine/shader.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class D3D9Shader : public Shader
    {
    public:
        D3D9Shader(
            const core::Uri& uri,
            IDirect3DDevice9* d3d9device,
            ID3DXEffectPool* d3deffectpool);
        virtual~D3D9Shader();
        
        override bool preload();

        override void begin(core::uint32_t& num_pass, bool restore=false);
        override void end();
        override void beginPass(core::uint32_t pass);
        override void endPass();

        override void setTechnique(const core::String& name);

        override void setFloat(const core::String& name, float v);
        override void setMatrix(
            const core::String& name,
            const core::Matrix44& m);
        override void setTexture(const core::String& name, Texture* t);

        override void commit();

        override bool valid() const;
        override void onLostDevice();
        override void onRestoreDevice();

    private:
        IDirect3DDevice9* d3d9device_;
        ID3DXEffect* d3deffect_;
        ID3DXEffectPool* d3deffectpool_;
    };
}
}
}


#endif // TOD_D3D9GRAPHICS_D3D9SHADER_H
