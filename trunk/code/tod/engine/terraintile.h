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
#include "tod/engine/vertexbuffer.h"

namespace tod
{
namespace engine
{
    class TerrainTile
    {
    public:
        TerrainTile();
        virtual~TerrainTile();

        bool build(const Vector3& scale);
        void render();

        void computeLOD(const Vector3& camera_pos);
        
    private:
        int detailLevel_;
        Vector3 center_;
        ResourceRef<VertexBuffer> vb_;
    };
}
}

#endif // TOD_ENGINE_NODE_TERRAINTILE_H
