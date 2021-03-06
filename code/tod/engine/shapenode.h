#ifndef TOD_ENGINE_GRAPHICS_SCENE_NODE_SHAPENODE_H
#define TOD_ENGINE_GRAPHICS_SCENE_NODE_SHAPENODE_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::ShapeNode
    @brief 
*/

#include "tod/engine/shadernode.h"

namespace tod
{
namespace engine
{
    class ShapeNode : public ShaderNode
    {
    public:
        ShapeNode();
        virtual~ShapeNode();
        DECLARE_CLASS(ShapeNode, ShaderNode);
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_NODE_SHAPENODE_H
