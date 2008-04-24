#ifndef TOD_ENGINE_GRAPHICS_RENDERPATH_RPBASE_H
#define TOD_ENGINE_GRAPHICS_RENDERPATH_RPBASE_H
/**
    @ingroup TodEngineGraphicsRenderPath
    @class tod::engine::graphics::RpBase
    @brief 
*/

#include "tod/core/node.h"
#include "tod/engine/shaderparams.h"
#include "tod/engine/shader.h"
#include "tod/engine/resourceref.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class RpBase : public core::Node, public ShaderParams
    {
    public:
        RpBase();
        virtual~RpBase();
        DECLARE_CLASS(RpBase, core::Node);

        virtual void validate();

        virtual core::uint32_t begin();
        virtual void end();
        virtual void beginPass(core::uint32_t pass);
        virtual void endPass();

        void setShaderUri(const core::Uri& uri);
        const core::Uri& getShaderUri() const;

        void setTechnique(const core::String& t);
        const core::String& getTechnique() const;

        Shader* getShader();

        static void bindMethod();
        static void bindProperty();

    private:
        ResourceRef<Shader> shader_;
        core::Uri shaderUri_;
        core::String technique_;
    };
}
}
}

#endif // TOD_ENGINE_GRAPHICS_RENDERPATH_RPBASE_H
