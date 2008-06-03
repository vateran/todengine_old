#ifndef TOD_ENGINE_NODE_TERRAIN_H
#define TOD_ENGINE_NODE_TERRAIN_H
/**
    @ingroup TodEngine
    @class tod::engine::Terrain
    @brief 
*/

#include "tod/core/uri.h"
#include "tod/engine/resourceref.h"
#include "tod/engine/shapenode.h"
#include "tod/engine/vertexbuffer.h"

namespace tod
{
namespace engine
{
    class Terrain
    {
    public:
        Terrain();
        virtual~Terrain();
    };
}
}

#endif // TOD_ENGINE_NODE_TERRAINNODE_H
