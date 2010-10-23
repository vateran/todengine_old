#ifndef TOD_D3D9GRAPHICS_D3D9MESH_H
#define TOD_D3D9GRAPHICS_D3D9MESH_H
/**
    @ingroup D3D9Graphics
    @class tod::engine::D3D9Mesh
    @brief 
*/

#include <vector>
#include <d3dx9.h>
#include "tod/core/define.h"
#include "tod/core/uri.h"
#include "tod/engine/mesh.h"

namespace tod
{
namespace engine
{
    class D3D9Mesh : public Mesh
    {
    public:
        D3D9Mesh(const Uri& uri, IDirect3DDevice9* d3d9device);
        virtual~D3D9Mesh();

        override bool preload(
            bool auto_compute_normals,
            bool auto_compute_tangents,
            bool split_vertex_for_optimal_tangents);

        override bool draw();

        override bool valid() const;

        override void onLostDevice();
        override void onRestoreDevice();
        
    private:
        IDirect3DDevice9* d3d9device_;
        ID3DXMesh* d3dmesh_;
        ID3DXBuffer* materialBuffer_;
        D3DXMATERIAL* materials_;
        DWORD numMaterial_;
    };
}
}


#endif // TOD_D3D9GRAPHICS_D3D9MESH_H
