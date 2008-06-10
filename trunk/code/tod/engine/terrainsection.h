#ifndef TOD_ENGINE_NODE_TERRAINSECTION_H
#define TOD_ENGINE_NODE_TERRAINSECTION_H
/**
    @ingroup TodEngine
    @class tod::engine::TerrainSection
    @brief 
*/

#include <vector>
#include "tod/core/uri.h"
#include "tod/engine/resourceref.h"
#include "tod/engine/indexbuffer.h"
#include "tod/engine/vertexbuffer.h"
#include "tod/engine/terraintile.h"
#include "tod/engine/image.h"

namespace tod
{
namespace engine
{
    class TerrainSection
    {
    public:
        TerrainSection();
        virtual~TerrainSection();

        void render();

        void build(const Uri& uri, const Vector3& scale, int split);

    private:
        bool build_tile(const Uri& uri, const Vector3& scale);
        void build_index(int col, int row, int max_lod, int split);
        int compute_max_lod_level(int size, int split);

    private:
        typedef std::vector<TerrainTile> Tiles;

    private:
        Image hmap_;
        Tiles tiles_;
        int maxLOD_;
        int split_;

        ResourceRef<VertexBuffer> vb_;
    };
}
}

#endif // TOD_ENGINE_NODE_TERRAINSECTION_H
