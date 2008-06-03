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

        void setVBUri(const Uri& uri);
        const Uri& getVBUri() const;
        void setHeightMapUri(const Uri& uri);
        const Uri& getHeightMapUri() const;

        void setLOD(int lod) { lod_ = lod; ts_.rebuild(lod_); }
        int getLOD() const { return lod_; }

        static void bindProperty();

    private:
        Uri vbUri_;
        Uri heightMapUri_;
        TerrainSection ts_;

        int lod_;
    };
}
}

#endif // TOD_ENGINE_NODE_TERRAINNODE_H
