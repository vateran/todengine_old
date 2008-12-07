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
#include "tod/core/enumeration.h"
#include "tod/engine/resource.h"

namespace tod
{
namespace engine
{
    struct ShaderParamDesc
    {
        enum Type
        {
            TYPE_VOID,
            TYPE_BOOL,
            TYPE_INT,
            TYPE_FLOAT,
            TYPE_STRING,
            TYPE_TEXTURE,
            TYPE_TEXTURE1D,
            TYPE_TEXTURE2D,
            TYPE_TEXTURE3D,
            TYPE_TEXTURECUBE,
            TYPE_SAMPLER,
            TYPE_SAMPLER1D,
            TYPE_SAMPLER2D,
            TYPE_SAMPLER3D,
            TYPE_SAMPLERCUBE,
            TYPE_PIXELSHADER,
            TYPE_VERTEXSHADER,
            TYPE_PIXELFRAGMENT,
            TYPE_VERTEXFRAGMENT,
            TYPE_UNSUPPORTED,

            TYPE_MAX,
            TYPE_FORCE_DWORD = 0x7fffffff,
        };

        String name_;
        String semantic_;
        Type type_;
        String value_;
    };

    typedef Enumeration<ShaderParamDesc::Type,
        ShaderParamDesc::TYPE_MAX,
        ShaderParamDesc::TYPE_FORCE_DWORD>
        ShaderParamTypeEnumeration;
    struct ShaderParamTypeEnumerationInitializer : public ShaderParamTypeEnumeration
    {
        static void initialize();
    };

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

        virtual uint32_t getParameterNum() const=0;
        virtual ShaderParamDesc getParameterDesc(uint32_t index)=0; 

        virtual void commit()=0;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_SHADER_H
