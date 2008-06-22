#ifndef TOD_ENGINE_NODE_TERRAINTILESET_H
#define TOD_ENGINE_NODE_TERRAINTILESET_H
/**
    @ingroup TodEngine
    @class tod::engine::TerrainTileSet
    @brief 
*/

#include <vector>
#include "tod/core/uri.h"
#include "tod/engine/resourceref.h"
#include "tod/engine/indexbuffer.h"
#include "tod/engine/terraintile.h"

namespace tod
{
namespace engine
{
    class TerrainTileSet
    {
    public:
        TerrainTileSet();
        virtual~TerrainTileSet();

        void draw();

        void build(int col, int row, int split);

    private:
        void build_index(int col, int row, int max_lod, int split);
        int compute_max_lod_level(int size, int split);

    private:
        typedef std::vector<TerrainTile> Tiles;

    private:
        int col_;
        int row_;
        int split_;
        int maxLOD_;

        Tiles tiles_;
    };
}
}

#endif // TOD_ENGINE_NODE_TERRAINTILESET_H
