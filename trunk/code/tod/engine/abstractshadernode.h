#ifndef TOD_ENGINE_GRAPHICS_SCENE_NODE_ABSTRACTSHADERNODE_H
#define TOD_ENGINE_GRAPHICS_SCENE_NODE_ABSTRACTSHADERNODE_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::graphics::AbstractShaderNode
    @brief 
*/

#include "tod/core/name.h"
#include "tod/core/uri.h"
#include "tod/engine/shaderparams.h"
#include "tod/engine/transformnode.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class AbstractShaderNode : public TransformNode, public ShaderParams
    {
    public:
        AbstractShaderNode();
        virtual~AbstractShaderNode();
        DECLARE_CLASS(AbstractShaderNode, TransformNode);

        void addTexture(const core::Name& name, const core::Uri& uri);
        void addCubeTexture(const core::Name& name, const core::Uri& uri);

        void setRpPassIndex(int index);
        int getRpPassIndex() const;

        static void bindMethod();
        static void bindProperty();

    private:
        int renderPassIndex_;

    };

#include "tod/engine/abstractshadernode.inl"

}
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_NODE_ABSTRACTSHADERNODE_H
