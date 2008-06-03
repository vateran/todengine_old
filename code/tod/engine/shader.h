#ifndef TOD_ENGINE_GRAPHICS_CORE_SHADER_H
#define TOD_ENGINE_GRAPHICS_CORE_SHADER_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::Shader
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
    class Texture;
    class Shader : public Resource
    {
    public:
        Shader(const Uri& uri):Resource(uri) {}
        virtual~Shader() {}

        virtual bool preload()=0;

        virtual void begin(uint32_t& num_pass, bool restore=false)=0;
        virtual void end()=0;
        virtual void beginPass(uint32_t pass)=0;
        virtual void endPass()=0;

        virtual void setTechnique(const String& name)=0;

        virtual void setFloat(const String& name, float v)=0;

        virtual void setMatrix(
            const String& name,
            const Matrix44& m)=0;
        virtual void setTexture(const String& name, Texture* t)=0;

        virtual void commit()=0;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_SHADER_H
