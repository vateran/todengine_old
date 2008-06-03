#ifndef TOD_ENGINE_NODE_TERRAINSECTION_H
#define TOD_ENGINE_NODE_TERRAINSECTION_H
/**
    @ingroup TodEngine
    @class tod::engine::TerrainSection
    @brief 
*/

#include <vector>
#include "tod/core/uri.h"
#include "tod/engine/indexbuffer.h"
#include "tod/engine/resourceref.h"
#include "tod/engine/terraintile.h"

namespace tod
{
namespace engine
{
    class TerrainSection
    {
    public:
        class DetailLevel
        {
        public:
            enum Side
            {
                SIDE_TOP,
                SIDE_LEFT,
                SIDE_RIGHT,
                SIDE_BOTTOM,

                SIDE_MAX,
            };

        public:

        private:
            typedef std::vector<ResourceRef<IndexBuffer> > IndexBuffers;
            typedef std::vector<IndexBuffers> Connectors;

        private:
            IndexBuffers tiles_;
            Connectors connectors_[SIDE_MAX];
        };

    public:
        TerrainSection();
        virtual~TerrainSection();

        void render();

        void rebuild(int lod);

    private:
        typedef std::vector<TerrainTile> TerrainTiles;
        typedef std::vector<DetailLevel> DetailLevels;

    private:
        TerrainTiles tiles_;
        DetailLevels detailLevels_;
    };
}
}

#endif // TOD_ENGINE_NODE_TERRAINSECTION_H
