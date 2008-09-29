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
        struct PickInfo
        {
            TerrainTile* tile_; 
            int index_;
        };

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
        override void pick(int x, int y, int w, int h);

        void pick(int x, int y, int w, int h, PickInfo* info);

        void makeKernel(int radius, float strength, float softness);
        void raise(int x, int y, int w, int h);
        void lower(int x, int y, int w, int h);
        void computeNormal();

        void setHeightMapUri(const Uri& uri);
        const Uri& getHeightMapUri() const;

        void setTerrainSize(int s);
        int getTerrainSize() const;



        void setTexture(const Uri& uri);
        const Uri& getTexture() const;
        Uri diffuseUri_;

        void setUVRepeat(int s) { uvRepeat_ = s; unloadResource(); }
        int getUVRepeat() const { return uvRepeat_; }
        int uvRepeat_;




        static void bindProperty();
        static void bindMethod();

    private:
        Uri heightMapUri_;
        TerrainTileSet terrain_;        
        TerrainSection terrainSection_;

        ResourceRef<VertexBuffer> vb_;
        std::vector<std::vector<float> > kernel_;

        int col_;
        int row_;
    };
}
}

#endif // TOD_ENGINE_NODE_TERRAINNODE_H
