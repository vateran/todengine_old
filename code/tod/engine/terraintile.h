#ifndef TOD_ENGINE_NODE_TERRAINTILE_H
#define TOD_ENGINE_NODE_TERRAINTILE_H
/**
    @ingroup TodEngine
    @class tod::engine::TerrainTile
    @brief 
*/

#include "tod/core/uri.h"
#include "tod/core/vector3.h"
#include "tod/engine/resourceref.h"
#include "tod/engine/indexbuffer.h"

namespace tod
{
namespace engine
{
    class TerrainTile
    {
    public:
        enum Side
        {
            SIDE_TOP,
            SIDE_LEFT,
            SIDE_RIGHT,
            SIDE_BOTTOM,
            SIDE_TOPLEFT,
            SIDE_TOPRIGHT,
            SIDE_BOTTOMLEFT,
            SIDE_BOTTOMRIGHT,

            SIDE_MAX,
        };

    public:
        TerrainTile();
        virtual~TerrainTile();

        bool build(
            int max_lod, int split, const Vector3& center,
            int col, int row, int x, int y);

        void draw();

        void computeLOD(const Vector3& camera_pos, int lod, float step);

    public:
        template <typename T>
        int build_index(
            T* ptr, int col, int row, int step,
            int x, int y, int width, int height);
        template <typename T>
        int build_connector(
            T* ptr, int col, int row, int step,
            int x, int y, int width, int height, int side);

    public:
        typedef std::vector<ResourceRef<IndexBuffer> > IndexBuffers;

    public:
        IndexBuffers ibs_;
        IndexBuffers cibs_[SIDE_MAX];

        int detailLevel_;
        Vector3 center_;
    };

#include "tod/engine/terraintile.inl"

}
}

#endif // TOD_ENGINE_NODE_TERRAINTILE_H
