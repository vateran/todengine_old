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

        bool build(const Uri& uri, const Vector3& scale, int split);

        int getWidth() const { return hmap_.width(); }
        int getHeight() const { return hmap_.height(); }
    
    private:
        Image hmap_;
    
        ResourceRef<VertexBuffer> vb_;
    };
}
}

#endif // TOD_ENGINE_NODE_TERRAINSECTION_H
