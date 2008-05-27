#ifndef TOD_ENGINE_NODE_QUADTREE_H
#define TOD_ENGINE_NODE_QUADTREE_H
/**
    @ingroup TodEngine
    @class tod::engine::QuadTree
    @brief 
*/

#include "tod/core/uri.h"
#include "tod/core/bbox.h"
#include "tod/engine/resourceref.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class QuadTree
    {
    public:
        QuadTree();
        virtual~QuadTree();

        void initialize(int depth, const core::BBox& BoundingBox);

    public:
        class Node
        {
        public:
        };

        class Element
        {
        public:
        };

    private:
    };
}
}
}

#endif // TOD_ENGINE_NODE_TERRAINNODE_H
