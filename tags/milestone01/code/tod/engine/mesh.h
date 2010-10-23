#ifndef TOD_ENGINE_GRAPHICS_CORE_MESH_H
#define TOD_ENGINE_GRAPHICS_CORE_MESH_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::Mesh
    @brief 
*/

#include "tod/core/uri.h"
#include "tod/engine/resource.h"

namespace tod
{
namespace engine
{
    class Mesh : public Resource
    {
    public:
        Mesh(const Uri& uri):Resource(uri) {}
        virtual~Mesh() {}

        virtual bool preload(
            bool auto_compute_normals,
            bool auto_compute_tangents,
            bool split_vertex_for_optimal_tangents)=0;

        virtual bool draw()=0;

        virtual bool valid() const=0;
        bool invalid() const { return !valid(); }

        virtual void onLostDevice()=0;
        virtual void onRestoreDevice()=0;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_MESH_H
