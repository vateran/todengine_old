#ifndef TOD_ENGINE_GRAPHICS_SCENE_NODE_ABSTRACTCAMERANODE_H
#define TOD_ENGINE_GRAPHICS_SCENE_NODE_ABSTRACTCAMERANODE_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::graphics::AbstractCameraNode
    @brief 
*/

#include "tod/engine/shadernode.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class AbstractCameraNode : public ShaderNode
    {
    public:
        AbstractCameraNode();
        virtual~AbstractCameraNode();
        DECLARE_CLASS(AbstractCameraNode, ShaderNode);

        void setRenderPathSection(const core::Name& name);
        const core::Name& getRenderPathSection() const;

        void setViewMatrix(const core::Matrix44& m);
        void setProjectionMatrix(const core::Matrix44& m);
        const core::Matrix44& getViewMatrix() const;
        const core::Matrix44& getProjectionMatrix() const;

        static void bindProperty();

    protected:
        core::Matrix44 view_;
        core::Matrix44 projection_;
        core::Name renderPathSection_;
    };
}
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_NODE_ABSTRACTCAMERANODE_H
