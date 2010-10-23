#ifndef TOD_ENGINE_GRAPHICS_RENDERPATH_RPBASE_H
#define TOD_ENGINE_GRAPHICS_RENDERPATH_RPBASE_H
/**
    @ingroup TodEngineGraphicsRenderPath
    @class tod::engine::RpBase
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
    class RpBase : public Node, public ShaderParams
    {
    public:
        RpBase();
        virtual~RpBase();
        DECLARE_CLASS(RpBase, Node);

        virtual void validate();

        virtual uint32_t begin();
        virtual void end();
        virtual void beginPass(uint32_t pass);
        virtual void endPass();

        void setShaderUri(const Uri& uri);
        const Uri& getShaderUri() const;

        void setTechnique(const String& t);
        const String& getTechnique() const;

        Shader* getShader();

        static void bindMethod();
        static void bindProperty();

    private:
        ResourceRef<Shader> shader_;
        Uri shaderUri_;
        String technique_;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_RENDERPATH_RPBASE_H
