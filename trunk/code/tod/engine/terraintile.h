#ifndef TOD_ENGINE_NODE_TERRAINTILE_H
#define TOD_ENGINE_NODE_TERRAINTILE_H
/**
    @ingroup TodEngine
    @class tod::engine::TerrainTile
    @brief 
*/

#include <bitset>
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
        enum Junction
        {
            JUNCTION_TOP,
            JUNCTION_LEFT,
            JUNCTION_RIGHT,
            JUNCTION_BOTTOM,
            JUNCTION_TOPLEFT,
            JUNCTION_TOPRIGHT,
            JUNCTION_BOTTOMLEFT,
            JUNCTION_BOTTOMRIGHT,

            JUNCTION_MAX,
        };

        typedef std::bitset<4> JunctionFlag;

    public:
        TerrainTile();
        virtual~TerrainTile();

        bool build(
            int max_lod, int split, const Vector3& center,
            int col, int row, int x, int y);

        void draw(const JunctionFlag& flag);

        void computeLOD(const Vector3& camera_pos, int lod, float step);
        
        int getLOD() const;

        void setCenter(const Vector3& center);
        const Vector3& getCenter() const;

    private:
        template <typename T>
        int build_index(
            T* ptr, int col, int row, int step,
            int x, int y, int width, int height);
        template <typename T>
        int build_connector(
            T* ptr, int col, int row, int step,
            int x, int y, int width, int height, int junction);

    private:
        typedef std::vector<ResourceRef<IndexBuffer> > IndexBuffers;

    public:
        IndexBuffers ibs_;
        IndexBuffers cibs_[JUNCTION_MAX];

        int lod_;
        Vector3 center_;
    };

#include "tod/engine/terraintile.inl"

}
}

#endif // TOD_ENGINE_NODE_TERRAINTILE_H
