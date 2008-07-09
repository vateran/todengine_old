#ifndef TOD_ENGINE_NODE_TREENODE_H
#define TOD_ENGINE_NODE_TREENODE_H
/**
    @ingroup TodEngine
    @class tod::engine::TreeNode
    @brief 
*/

#include "tod/engine/shapenode.h"
#include "tod/engine/resourceref.h"

namespace tod
{
namespace engine
{
    class TreeNode : public ShapeNode
    {
    public:
        TreeNode();
        virtual~TreeNode();
        DECLARE_CLASS(TreeNode, ShapeNode);

        override void applyGeometry(SceneServer* scene_server);
        override void renderGeometry(
            SceneServer* scene_server,
            SceneContext* scene_context);
        override bool loadResource();
        override void unloadResource();
        override bool hasGeometry() const;

    private:

    };
}
}

#endif // TOD_ENGINE_NODE_TREENODE_H
