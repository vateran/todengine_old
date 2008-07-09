#ifndef TOD_ENGINE_NODE_TERRAIN_H
#define TOD_ENGINE_NODE_TERRAIN_H
/**
    @ingroup TodEngine
    @class tod::engine::Terrain
    @brief 
*/

#include <vector>
#include "tod/core/uri.h"
#include "tod/engine/resourceref.h"
#include "tod/engine/indexbuffer.h"
#include "tod/engine/terraintile.h"
#include "tod/engine/quadtree.h"

namespace tod
{
namespace engine
{
    class Terrain
    {
    public:
        Terrain();
        virtual~Terrain();

        void draw(const Vector3& offset);

        void build(int col, int row, int tile_size);

    private:
        void build_index(int col, int row, int max_lod, int split);
        int compute_max_lod_level(int size, int split);

    private:
        class TerrainTileElement : public QuadTree::Element
        {
        public:
            override void render(
                const Matrix44& view_proj,
                BBox::ClipStatus clip_status);

            void computeLOD(const Vector3& camera_pos, int lod, float step)
            {
                tile_.computeLOD(camera_pos, lod, step);
            }
            bool build(int max_lod, int split, const Vector3& center, int col, int row, int x, int y)
            {
                return tile_.build(max_lod, split, center, col, row, x, y);
            }

        public:
            TerrainTile tile_;
            TerrainTile::JunctionFlag flag_;
        };
        typedef std::vector<TerrainTileElement> Tiles;

    private:
        int col_;
        int row_;
        int split_;
        int maxLOD_;

        Tiles tiles_;

        QuadTree qtree_;        
    };
}
}

#endif // TOD_ENGINE_NODE_TERRAINNODE_H
