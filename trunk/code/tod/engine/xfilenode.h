#ifndef TOD_ENGINE_NODE_XFILENODE_H
#define TOD_ENGINE_NODE_XFILENODE_H
/**
    @ingroup TodEngine
    @class tod::engine::XFileNode
    @brief 
*/

#include "tod/engine/shapenode.h"
#include "tod/engine/resourceref.h"

namespace tod
{
namespace engine
{
    class XFileNode : public ShapeNode
    {
    public:
        XFileNode();
        virtual~XFileNode();
        DECLARE_CLASS(XFileNode, ShapeNode);

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

#endif // TOD_ENGINE_NODE_XFILENODE_H
