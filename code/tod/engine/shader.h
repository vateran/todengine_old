#ifndef TOD_ENGINE_GRAPHICS_CORE_SHADER_H
#define TOD_ENGINE_GRAPHICS_CORE_SHADER_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::graphics::Shader
    @brief 
*/

#include "tod/core/matrix44.h"
#include "tod/core/primitivetype.h"
#include "tod/core/uri.h"
#include "tod/engine/resource.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class Texture;
    class Shader : public Resource
    {
    public:
        Shader(const core::Uri& uri):Resource(uri) {}
        virtual~Shader() {}

        virtual bool preload()=0;

        virtual void begin(core::uint32_t& num_pass)=0;
        virtual void end()=0;
        virtual void beginPass(core::uint32_t pass)=0;
        virtual void endPass()=0;

        virtual void setTechnique(const core::String& name)=0;

        virtual void setFloat(const core::String& name, float v)=0;

        virtual void setMatrix(
            const core::String& name,
            const core::Matrix44& m)=0;
        virtual void setTexture(const core::String& name, Texture* t)=0;

        virtual void commit()=0;
    };
}
}
}


#endif // TOD_ENGINE_GRAPHICS_CORE_SHADER_H
