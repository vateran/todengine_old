#ifndef TOD_ENGINE_NODE_TERRAINNODE_H
#define TOD_ENGINE_NODE_TERRAINNODE_H
/**
    @ingroup TodEngine
    @class tod::engine::TerrainNode
    @brief 
*/

#include "tod/core/uri.h"
#include "tod/engine/resourceref.h"
#include "tod/engine/shapenode.h"
#include "tod/engine/vertexbuffer.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class TerrainNode : public ShapeNode
    {
    public:
        TerrainNode();
        virtual~TerrainNode();
        DECLARE_CLASS(TerrainNode, ShapeNode);

        override void applyGeometry(SceneServer* scene_server);
        override void renderGeometry(
            SceneServer* scene_server,
            SceneContext* scene_context);
        override bool loadResource();
        override void unloadResource();
        override bool hasGeometry() const;

        void setVBUri(const core::Uri& uri);
        const core::Uri& getVBUri() const;
        void setHeightMapUri(const core::Uri& uri);
        const core::Uri& getHeightMapUri() const;

        static void bindProperty();

    private:
        core::Uri vbUri_;
        core::Uri heightMapUri_;
        ResourceRef<VertexBuffer> vb_;
    };
}
}
}

#endif // TOD_ENGINE_NODE_TERRAINNODE_H
