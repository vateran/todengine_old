#ifndef TOD_ENGINE_GRAPHICS_RENDERPATH_RPSHADER_H
#define TOD_ENGINE_GRAPHICS_RENDERPATH_RPSHADER_H
/**
    @ingroup TodEngineGraphicsRenderPath
    @class tod::engine::graphics::RpShader
    @brief 
*/

#include "tod/core/node.h"
#include "tod/core/uri.h"
#include "tod/engine/shader.h"
#include "tod/engine/resourceref.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class RpShader : public core::Node
    {
    public:
        RpShader();
        virtual~RpShader();
        DECLARE_CLASS(RpShader, core::Node);

        void setShaderUri(const core::Uri& uri);
        const core::Uri& getShaderUri() const;

        Shader* getShader();

    private:
        ResourceRef<Shader> shader_;
        core::Uri uri_;
    };
}
}
}

#endif // TOD_ENGINE_GRAPHICS_RENDERPATH_RPSHADER_H
