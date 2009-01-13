#include "tod/d3d9graphics/d3d9mesh.h"

#include "tod/core/assert.h"
#include "tod/core/log.h"
#include "tod/core/resource.h"
#include "tod/core/exception.h"
#include "tod/d3d9graphics/d3d9exception.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
D3D9Mesh::D3D9Mesh(const Uri& uri, IDirect3DDevice9* d3d9device):
Mesh(uri), d3d9device_(d3d9device), d3dmesh_(0), materials_(0),
materialBuffer_(0)
{
    d3d9device_->AddRef();
}


//-----------------------------------------------------------------------------
D3D9Mesh::~D3D9Mesh()
{
    SAFE_RELEASE(materialBuffer_);
    SAFE_RELEASE(d3dmesh_);
    SAFE_RELEASE(d3d9device_);
}


//-----------------------------------------------------------------------------
bool D3D9Mesh::preload
(bool auto_compute_normals, bool auto_compute_tangents,
 bool split_vertex_for_optimal_tangents)
{
    tod_assert(d3d9device_);
    if (d3dmesh_)
        return true;

    tod::Resource resource(getUri());
    if (!resource.open(
        tod::Resource::OPEN_READ |
        tod::Resource::OPEN_BINARY))
        return false;

    dynamic_buffer_t buffer;
    resource.read(buffer);

    // load
    HRESULT hr;
    SAFE_RELEASE(materialBuffer_);
    if (FAILED(hr = D3DXLoadMeshFromXInMemory(
        &buffer[0], static_cast<DWORD>(buffer.size()), D3DXMESH_MANAGED,
        d3d9device_, 0, &materialBuffer_, 0, &numMaterial_, &d3dmesh_)))
    {
        THROW_D3D9EXCEPTION(0, hr,
            String(STRING("D3DXLoadD3D9MeshFromXInMemory(%s)"),
                getUri().c_str()));
        return false;
    }
    materials_ = static_cast<D3DXMATERIAL*>(materialBuffer_->GetBufferPointer());

    // Check if the old declaration contains a normal
    bool had_normals = false;
    bool had_tangents = false;
    D3DVERTEXELEMENT9 old_decl[MAX_FVF_DECL_SIZE];
    if (FAILED(d3dmesh_->GetDeclaration(old_decl)))
    {
        THROW_D3D9EXCEPTION(0, hr,
            String(STRING("d3dmesh_->GetDeclaration(%s)"), getUri().c_str()));
        return false;
    }
    for (UINT i = 0; i < D3DXGetDeclLength(old_decl); ++i)
    {
        if (old_decl[i].Usage == D3DDECLUSAGE_NORMAL)
            had_normals = true;
        else if (old_decl[i].Usage == D3DDECLUSAGE_TANGENT)
            had_tangents = true;
    }

    struct DeclTypeSize
    {
        int type_;
        int size_;
    };

    typedef unsigned char UBYTE;
    static DeclTypeSize dts[] = 
    {
        { D3DDECLTYPE_FLOAT1, sizeof(float) },
        { D3DDECLTYPE_FLOAT2, sizeof(float) * 2 },
        { D3DDECLTYPE_FLOAT3, sizeof(float) * 3 },
        { D3DDECLTYPE_FLOAT4, sizeof(float) * 4 },
        { D3DDECLTYPE_D3DCOLOR, sizeof(DWORD) },
        { D3DDECLTYPE_UBYTE4, sizeof(UBYTE) * 4 },
        { D3DDECLTYPE_SHORT2, sizeof(SHORT) * 2 },
        { D3DDECLTYPE_SHORT4, sizeof(SHORT) * 4 },
        { D3DDECLTYPE_UBYTE4N, sizeof(UBYTE) * 4 },
        { D3DDECLTYPE_SHORT2N, sizeof(SHORT) * 2 },
        { D3DDECLTYPE_SHORT4N, sizeof(SHORT) * 4 },
        { D3DDECLTYPE_USHORT2N, sizeof(USHORT) * 2 },
        { D3DDECLTYPE_USHORT4N, sizeof(USHORT) * 4 },
        { D3DDECLTYPE_UDEC3, sizeof(UINT) * 3 },
        { D3DDECLTYPE_DEC3N, sizeof(INT) * 3 },
        { D3DDECLTYPE_FLOAT16_2, sizeof(DOUBLE) * 2 },
        { D3DDECLTYPE_FLOAT16_4, sizeof(DOUBLE) * 4 },
    };

    if (!had_normals && auto_compute_normals)
    {
        D3DVERTEXELEMENT9 new_decl[MAX_FVF_DECL_SIZE];
        memcpy(new_decl, old_decl, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);
        UINT old_length = D3DXGetDeclLength(old_decl);
        new_decl[old_length].Offset =
            new_decl[old_length - 1].Offset +
            dts[new_decl[old_length - 1].Type].size_;
        new_decl[old_length].Method = D3DDECLMETHOD_DEFAULT;
        new_decl[old_length].Type = D3DDECLTYPE_FLOAT3;
        new_decl[old_length].Usage = D3DDECLUSAGE_NORMAL;
        new_decl[old_length].UsageIndex = 0;
        new_decl[old_length].Stream = 0;
        D3DVERTEXELEMENT9 te = D3DDECL_END();
        new_decl[old_length + 1] = te;

        ID3DXMesh* new_mesh = 0;
        d3dmesh_->CloneMesh(d3dmesh_->GetOptions(), new_decl, d3d9device_, &new_mesh);
        SAFE_RELEASE(d3dmesh_);
        D3DXComputeNormals(new_mesh, 0);        
        d3dmesh_ = new_mesh;
    }
    
    return true;
}


//-----------------------------------------------------------------------------
#include "tod/engine/shader.h"
#include "tod/engine/renderer.h"
#include "tod/engine/texture.h"
bool D3D9Mesh::draw()
{
    tod_assert(d3d9device_);

    if (0 == d3dmesh_)
        return false;

    Shader* shader = Renderer::instance()->getShader();
    
    for (DWORD i = 0; i < numMaterial_; ++i)
    {
        /*if (materials_[i].pTextureFilename)
        {
            String uri = getUri().getProtocol() + STRING("://") +
                getUri().getPackage() + STRING("#") +
                getUri().extractPath() + STRING("/") +
                String(materials_[i].pTextureFilename);
            Texture* t = Renderer::instance()->newTexture(uri);
            if (t)
            {
                if (t->invalid())
                    t->preload();
                shader->setTexture(STRING("Diffuse"), t);
                shader->commit();
            }
        }
        else
        {
            shader->setTexture(STRING("Diffuse"), 0);
            shader->commit();
        }*/

        uint32_t num_passes;
        shader->begin(num_passes);
        for (uint32_t pass = 0; pass < num_passes; ++pass)
        {
            shader->beginPass(pass);
            d3dmesh_->DrawSubset(i);
            shader->endPass();
        }    
        shader->end();
    }   
    return true;
}


//-----------------------------------------------------------------------------
bool D3D9Mesh::valid() const
{
    return d3dmesh_?true:false;
}


//-----------------------------------------------------------------------------
void D3D9Mesh::onLostDevice()
{
    // not implement
}


//-----------------------------------------------------------------------------
void D3D9Mesh::onRestoreDevice()
{
    // not implement
}
