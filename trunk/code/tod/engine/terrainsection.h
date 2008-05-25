#ifndef TOD_ENGINE_NODE_TERRAINSECTION_H
#define TOD_ENGINE_NODE_TERRAINSECTION_H
/**
    @ingroup TodEngine
    @class tod::engine::TerrainSection
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
namespace graphics
{
    class TerrainSection
    {
    public:
        TerrainSection();
        virtual~TerrainSection();
    };
}
}
}

#endif // TOD_ENGINE_NODE_TERRAINSECTION_H
