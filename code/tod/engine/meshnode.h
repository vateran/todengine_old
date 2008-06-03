#ifndef TOD_ENGINE_GRAPHICS_SCENE_NODE_MESHNODE_H
#define TOD_ENGINE_GRAPHICS_SCENE_NODE_MESHNODE_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::MeshNode
    @brief 
*/

#include "tod/core/uri.h"
#include "tod/engine/resourceref.h"
#include "tod/engine/shapenode.h"

namespace tod
{
namespace engine
{
    class Mesh;
    class MeshNode : public ShapeNode
    {
    public:
        MeshNode();
        virtual~MeshNode();
        DECLARE_CLASS(MeshNode, ShapeNode);

        override void applyGeometry(SceneServer* scene_server);
        override void renderGeometry(
            SceneServer* scene_server,
            SceneContext* scene_context);
        override bool loadResource();
        override void unloadResource();
        override bool hasGeometry() const;

        void setMeshUri(const Uri& uri);
        const Uri& getMeshUri() const;

        static void bindProperty();

    private:
        Uri uri_;
        ResourceRef<Mesh> mesh_;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_NODE_MESHNODE_H
