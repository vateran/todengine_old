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
#include "tod/engine/terraintileset.h"
#include "tod/engine/terrainsection.h"

namespace tod
{
namespace engine
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
        override void pick(int x, int y);

        void setHeightMapUri(const Uri& uri);
        const Uri& getHeightMapUri() const;

        static void bindProperty();

    private:
        Uri heightMapUri_;
        TerrainTileSet terrain_;        
        TerrainSection terrainSection_;

        ResourceRef<VertexBuffer> vb_;

        int col_;
        int row_;
    };
}
}

#endif // TOD_ENGINE_NODE_TERRAINNODE_H
