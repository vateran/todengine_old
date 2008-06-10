#include "tod/d3d9graphics/d3d9indexbuffer.h"

#include "tod/core/assert.h"
#include "tod/d3d9graphics/d3d9exception.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
D3D9IndexBuffer::D3D9IndexBuffer
(const Uri& uri, IDirect3DDevice9* d3d9device):
IndexBuffer(uri), d3d9device_(d3d9device), d3d9ib_(0)
{
    d3d9device_->AddRef();
}


//-----------------------------------------------------------------------------
D3D9IndexBuffer::~D3D9IndexBuffer()
{
    destroy();
    SAFE_RELEASE(d3d9device_);
}


//-----------------------------------------------------------------------------
bool D3D9IndexBuffer::create(uint32_t num_indices, int usage, Format format)
{
    tod_assert(d3d9device_);
    tod_assert(0 == d3d9ib_);

    numIndices_ = num_indices;
    usage_ = 0;
    d3dpool_ = D3DPOOL_MANAGED;
    if (usage & USAGE_DYNAMIC)
    {
        d3dpool_ = D3DPOOL_DEFAULT;
        usage_ |= D3DUSAGE_DYNAMIC;
        lockOption_ = D3DLOCK_DISCARD;
    }

    switch (format)
    {
    case Format::INDEX16:
        stride_ = 2;
        break;
    case Format::INDEX32:
        stride_ = 4;
        break;
    default:
        return false;
    }
    
    // create index buffer
    HRESULT hr;
    if (FAILED(hr = d3d9device_->CreateIndexBuffer(
        numIndices_ * stride_, usage, format, d3dpool_, &d3d9ib_, 0)))
    {
        THROW_D3D9EXCEPTION(D3D9GRAPHICSEXCEPTIONCODE_CREATEINDEXBUFFERERROR,
            hr, STRING("d3d9device_->CreateIndexBuffer"));
        return false;
    }

    return true;
}


//-----------------------------------------------------------------------------
void D3D9IndexBuffer::destroy()
{
    SAFE_RELEASE(d3d9ib_);
}


//-----------------------------------------------------------------------------
bool D3D9IndexBuffer::lock(void*& ptr)
{
    tod_assert(d3d9ib_);
    if (FAILED(d3d9ib_->Lock(0, numIndices_ * stride_, &ptr, lockOption_)))
        return false;
    return true;
}


//-----------------------------------------------------------------------------
bool D3D9IndexBuffer::unlock()
{
    tod_assert(d3d9ib_);
    if (FAILED(d3d9ib_->Unlock()))
        return false;
    return true;
}


//-----------------------------------------------------------------------------
bool D3D9IndexBuffer::use()
{
    tod_assert(d3d9device_);
    tod_assert(d3d9ib_);

    if (FAILED(d3d9device_->SetIndices(d3d9ib_)))
        return false;
    return true;
}


//-----------------------------------------------------------------------------
bool D3D9IndexBuffer::draw(PrimitiveType type, int num)
{
    tod_assert(d3d9device_);
    tod_assert(d3d9ib_);

    int num_primitive = num;
    if (num == -1)
    {
        switch (type)
        {
        case PRIMITIVETYPE_POINTLIST:
            num_primitive = numIndices_;
            break;
        case PRIMITIVETYPE_LINELIST:
            num_primitive = numIndices_ / 2;
            break;
        case PRIMITIVETYPE_LINESTRIP:
            num_primitive = numIndices_ - 1;
            break;
        case PRIMITIVETYPE_TRIANGLELIST:
            num_primitive = numIndices_ / 3;
            break;
        case PRIMITIVETYPE_TRIANGLESTRIP:
        case PRIMITIVETYPE_TRIANGLEFAN:
            num_primitive = numIndices_ - 2;
            break;
        }
    }
    
    if (FAILED(d3d9device_->DrawIndexedPrimitive(
        static_cast<D3DPRIMITIVETYPE>(type),
        0, 0, numIndices_, 0, num_primitive)))
        return false;
    return true;
}


//-----------------------------------------------------------------------------
bool D3D9IndexBuffer::valid() const
{
    return d3d9ib_?true:false;
}


//-----------------------------------------------------------------------------
void D3D9IndexBuffer::onLostDevice()
{
    // not implement
}


//-----------------------------------------------------------------------------
void D3D9IndexBuffer::onRestoreDevice()
{
    // not implement
}
