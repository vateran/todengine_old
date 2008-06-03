#ifndef TOD_ENGINE_GRAPHICS_SCENE_NODE_SHADERNODE_H
#define TOD_ENGINE_GRAPHICS_SCENE_NODE_SHADERNODE_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::ShaderNode
    @brief 
*/

#include "tod/core/uri.h"
#include "tod/engine/abstractshadernode.h"
#include "tod/engine/resourceref.h"

namespace tod
{
namespace engine
{
    class Shader;
    class ShaderNode : public AbstractShaderNode
    {
    public:
        ShaderNode();
        virtual~ShaderNode();
        DECLARE_CLASS(ShaderNode, AbstractShaderNode);

        override void applyShader(SceneServer* scene_server);
        override void renderShader(
            SceneServer* scene_server,
            SceneContext* scene_context);
        override bool hasShader() const;
        override bool loadResource();
        override void unloadResource();

        void setShaderUri(const Uri& uri);
        const Uri& getShaderUri() const;

        void setTechnique(const String& t);
        const String& getTechnique() const;

        static void bindProperty();

    private:
        Uri uri_;
        ResourceRef<Shader> shader_;
        String technique_;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_NODE_SHADERNODE_H
