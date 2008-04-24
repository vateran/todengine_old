#include "tod/d3d9graphics/d3d9vertexbuffer.h"

#include "tod/core/assert.h"
#include "tod/engine/types.h"
#include "tod/d3d9graphics/d3d9exception.h"

using namespace tod::core;
using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
D3D9VertexBuffer::D3D9VertexBuffer(const Uri& uri, IDirect3DDevice9* d3d9device):
VertexBuffer(uri), d3d9device_(d3d9device), d3d9vb_(0), d3d9vdecl_(0),
d3dpool_(D3DPOOL_MANAGED), numVertice_(0), vertexComponent_(0),
usage_(0), stride_(0), lockOption_(0)
{
    d3d9device_->AddRef();
}


//-----------------------------------------------------------------------------
D3D9VertexBuffer::~D3D9VertexBuffer()
{
    destroy();
}


//-----------------------------------------------------------------------------
bool D3D9VertexBuffer::create(int num_vertice, int vertex_component, int usage)
{
    tod_assert(d3d9device_);
    tod_assert(0 == d3d9vb_);
    
    d3dpool_ = D3DPOOL_MANAGED;
    if (usage & USAGE_DYNAMIC)
    {
        d3dpool_ = D3DPOOL_DEFAULT;
        usage |= D3DUSAGE_WRITEONLY;
        lockOption_ = D3DLOCK_DISCARD;
    }
    numVertice_ = num_vertice;
    vertexComponent_ = vertex_component;
    usage_ = usage;

    if (!setup_vertex_declaration(vertex_component))
        return false;

    // create vertex buffer
    HRESULT hr;
    if (FAILED(hr = d3d9device_->CreateVertexBuffer(
        stride_ * numVertice_, usage_, 0, d3dpool_, &d3d9vb_, 0)))
    {
        THROW_D3D9EXCEPTION(D3D9GRAPHICSEXCEPTIONCODE_CREATEVERTEXBUFFERERROR,
            hr, STRING("d3d9device_->CreateVertexBuffer"));
        return false;
    }
    return true;
}


//-----------------------------------------------------------------------------
void D3D9VertexBuffer::destroy()
{
    SAFE_RELEASE(d3d9vdecl_);
    SAFE_RELEASE(d3d9vb_);
    SAFE_RELEASE(d3d9device_);
}


//-----------------------------------------------------------------------------
bool D3D9VertexBuffer::lock(void*& ptr)
{
    tod_assert(d3d9vb_);
    if (FAILED(d3d9vb_->Lock(0, 0, &ptr, lockOption_)))
        return false;
    return true;
}


//-----------------------------------------------------------------------------
bool D3D9VertexBuffer::unlock()
{
    tod_assert(d3d9vb_);
    if (FAILED(d3d9vb_->Unlock()))
        return false;
    return true;
}


//-----------------------------------------------------------------------------
bool D3D9VertexBuffer::use()
{
    tod_assert(d3d9device_);
    tod_assert(d3d9vb_);
    if (FAILED(d3d9device_->SetVertexDeclaration(d3d9vdecl_)))
        return false;
    if (FAILED(d3d9device_->SetFVF(fvf_)))
        return false;
    if (FAILED(d3d9device_->SetStreamSource(0, d3d9vb_, 0, stride_)))
        return false;
    return true;
}


//-----------------------------------------------------------------------------
bool D3D9VertexBuffer::draw(PrimitiveType type)
{
    tod_assert(d3d9device_);
    tod_assert(d3d9vb_);

    int num_primitive = 0;
    switch (type)
    {
    case PRIMITIVETYPE_POINTLIST:
        num_primitive = numVertice_;
        break;
    case PRIMITIVETYPE_LINELIST:
        num_primitive = numVertice_ / 2;
        break;
    case PRIMITIVETYPE_LINESTRIP:
        num_primitive = numVertice_ - 1;
        break;
    case PRIMITIVETYPE_TRIANGLELIST:
        num_primitive = numVertice_ / 3;
        break;
    case PRIMITIVETYPE_TRIANGLESTRIP:
    case PRIMITIVETYPE_TRIANGLEFAN:
        num_primitive = numVertice_ - 2;
        break;
    }

    if (FAILED(d3d9device_->DrawPrimitive(
        static_cast<D3DPRIMITIVETYPE>(type), 0, num_primitive)))
        return false;
    return true;
}

//-----------------------------------------------------------------------------
bool D3D9VertexBuffer::valid() const
{
    return d3d9vb_?true:false;
}


//-----------------------------------------------------------------------------
void D3D9VertexBuffer::onLostDevice()
{
    // not implement
}


//-----------------------------------------------------------------------------
void D3D9VertexBuffer::onRestoreDevice()
{
    // not implement
}


//-----------------------------------------------------------------------------
bool D3D9VertexBuffer::setup_vertex_declaration(int vertex_component)
{
    // release previous vertex declaration
    SAFE_RELEASE(d3d9vdecl_);

    fvf_ = 0;
    int mask = 1;
    int offset = 0;
    int position_usage_index = 0;
    int normal_usage_index = 0;
    int color_usage_index = 0;
    int tangent_usage_index = 0;
    int binormal_usage_index = 0;
    int weights_usage_index = 0;
    int jointindices_usage_index = 0;

    std::vector<D3DVERTEXELEMENT9> ve;

    D3DVERTEXELEMENT9 t;
    t.Stream = 0;
    t.Method = D3DDECLMETHOD_DEFAULT;

    for (int i = 0; i < VERTEXCOMPONENT_MAX; ++i, mask <<= 1)
    {
        if (!(mask & vertex_component))
            continue;

        t.Offset = offset;

        switch (mask)
        {
        case VERTEXCOMPONENT_COORD:
            t.Type = D3DDECLTYPE_FLOAT3;
            t.Usage = D3DDECLUSAGE_POSITION;
            // xxx_usage_index specifies the index in the vertex shader semantic
            // i.e. UsageIndex = 3 results in POSITION3
            t.UsageIndex = position_usage_index++;
            offset += 3 * sizeof(float);
            fvf_ |= D3DFVF_XYZ;
            break;
        case VERTEXCOMPONENT_NORMAL:
            t.Type = D3DDECLTYPE_FLOAT3;
            t.Usage = D3DDECLUSAGE_NORMAL;
            t.UsageIndex = normal_usage_index++;
            offset += 3 * sizeof(float);
            fvf_ |= D3DFVF_NORMAL;
            break;
        case VERTEXCOMPONENT_COLOR:
            t.Type = D3DDECLTYPE_D3DCOLOR;
            t.Usage = D3DDECLUSAGE_COLOR;
            t.UsageIndex = color_usage_index++;
            offset += sizeof(DWORD);
            fvf_ |= D3DFVF_DIFFUSE;
            break;        
        case VERTEXCOMPONENT_UV0:
            t.Type = D3DDECLTYPE_FLOAT2;
            t.Usage = D3DDECLUSAGE_TEXCOORD;
            t.UsageIndex = 0;
            offset += 2 * sizeof(float);
            fvf_ |= D3DFVF_TEX1;
            break;
        case VERTEXCOMPONENT_UV1:
            t.Type = D3DDECLTYPE_FLOAT2;
            t.Usage = D3DDECLUSAGE_TEXCOORD;
            t.UsageIndex = 1;
            offset += 2 * sizeof(float);
            break;
        case VERTEXCOMPONENT_UV2:
            t.Type = D3DDECLTYPE_FLOAT2;
            t.Usage = D3DDECLUSAGE_TEXCOORD;
            t.UsageIndex = 2;
            offset += 2 * sizeof(float);
            break;
        case VERTEXCOMPONENT_UV3:
            t.Type = D3DDECLTYPE_FLOAT2;
            t.Usage = D3DDECLUSAGE_TEXCOORD;
            t.UsageIndex = 3;
            offset += 2 * sizeof(float);
            break;
        case VERTEXCOMPONENT_TANGENT:
            t.Type = D3DDECLTYPE_FLOAT3;
            t.Usage = D3DDECLUSAGE_TANGENT;
            t.UsageIndex = tangent_usage_index++;
            offset += 3 * sizeof(float);
            break;
        case VERTEXCOMPONENT_BINORMAL:
            t.Type = D3DDECLTYPE_FLOAT3;
            t.Usage = D3DDECLUSAGE_BINORMAL;
            t.UsageIndex = binormal_usage_index++;
            offset += 3 * sizeof(float);
            break;
        case VERTEXCOMPONENT_WEIGHTS:            
            t.Type = D3DDECLTYPE_FLOAT4;
            t.Usage = D3DDECLUSAGE_BLENDWEIGHT;
            t.UsageIndex = weights_usage_index++;
            offset += 4 * sizeof(float);
            break;
        case VERTEXCOMPONENT_JOINTINDICES:
            t.Type = D3DDECLTYPE_UBYTE4;
            t.Usage = D3DDECLUSAGE_BLENDINDICES;
            t.UsageIndex = jointindices_usage_index++;
            offset += 4 * sizeof(uint8_t);
            break;
        }

        // add vertex declaration element
        ve.push_back(t);
    }

    // add vertex declaration terminator element
    D3DVERTEXELEMENT9 te = D3DDECL_END();
    ve.push_back(te);

    // create vertex declaration
    if (FAILED(d3d9device_->CreateVertexDeclaration(&ve[0], &d3d9vdecl_)))
        return false;
    stride_ = offset;
    return true;
}
