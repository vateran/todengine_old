#ifndef TOD_ENGINE_GRAPHICS_SCENE_NODE_ABSTRACTCAMERANODE_H
#define TOD_ENGINE_GRAPHICS_SCENE_NODE_ABSTRACTCAMERANODE_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::AbstractCameraNode
    @brief 
*/

#include "tod/engine/shadernode.h"

namespace tod
{
namespace engine
{
    class AbstractCameraNode : public ShaderNode
    {
    public:
        AbstractCameraNode();
        virtual~AbstractCameraNode();
        DECLARE_CLASS(AbstractCameraNode, ShaderNode);

        void setRenderPathSection(const String& name);
        const String& getRenderPathSection() const;

        void setViewMatrix(const Matrix44& m);
        void setProjectionMatrix(const Matrix44& m);
        const Matrix44& getViewMatrix() const;
        const Matrix44& getProjectionMatrix() const;

        static void bindProperty();

    protected:
        Matrix44 view_;
        Matrix44 projection_;
        String renderPathSection_;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_NODE_ABSTRACTCAMERANODE_H
