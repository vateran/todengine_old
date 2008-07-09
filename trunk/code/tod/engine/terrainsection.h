#ifndef TOD_ENGINE_NODE_TERRAINSECTION_H
#define TOD_ENGINE_NODE_TERRAINSECTION_H
/**
    @ingroup TodEngine
    @class tod::engine::TerrainSection
    @brief 
*/

#include "tod/core/uri.h"
#include "tod/core/vector3.h"
#include "tod/engine/resourceref.h"
#include "tod/engine/vertexbuffer.h"
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

        void use();

        bool build(int col, int row, const Vector3& scale);
        
    private:
        ResourceRef<VertexBuffer> vb_;

        int col_;
        int row_;
    };

    typedef std::vector<TerrainSection> TerrainSections;
}
}

#endif // TOD_ENGINE_NODE_TERRAINSECTION_H
