#include "tod/d3d9graphics/d3d9cubetexture.h"

#include <d3dx9.h>
#include "tod/core/assert.h"
#include "tod/core/exception.h"
#include "tod/core/resource.h"
#include "tod/engine/types.h"
#include "tod/d3d9graphics/d3d9exception.h"

using namespace tod::core;
using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
D3D9CubeTexture::D3D9CubeTexture(const Uri& uri, IDirect3DDevice9* d3d9device):
CubeTexture(uri), d3d9device_(d3d9device), d3d9texture_(0), d3dusage_(0)
{
    d3d9device_->AddRef();
}


//-----------------------------------------------------------------------------
D3D9CubeTexture::~D3D9CubeTexture()
{
    destroy();
    SAFE_RELEASE(d3d9device_);
}


//-----------------------------------------------------------------------------
bool D3D9CubeTexture::create(int width, int height, int mipmap_level, Format format, int usage)
{
    tod_assert(d3d9device_);
    tod_assert(d3d9texture_ == 0);

    d3dusage_ = 0;
    D3DPOOL pool = D3DPOOL_MANAGED;
    if (usage & USAGE_RENDERTARGET)
    {
        d3dusage_ |= D3DUSAGE_RENDERTARGET;
        pool = D3DPOOL_DEFAULT;
    }
    return true;
}


//-----------------------------------------------------------------------------
void D3D9CubeTexture::destroy()
{
    SAFE_RELEASE(d3d9texture_);
}


//-----------------------------------------------------------------------------
bool D3D9CubeTexture::preload()
{
    tod_assert(d3d9device_);

    if (d3d9texture_)
        return true;

    tod::core::Resource resource(getUri());
    if (!resource.open(
        tod::core::Resource::OPEN_READ |
        tod::core::Resource::OPEN_BINARY))
        return false;

    dynamic_buffer_t buffer;
    resource.read(buffer);

    D3DXIMAGE_INFO img_info;
    HRESULT hr;
    if (FAILED(hr = D3DXCreateCubeTextureFromFileInMemoryEx(d3d9device_,
        &buffer[0], static_cast<UINT>(buffer.size()), D3DX_DEFAULT, 1,
        0, D3DFMT_FROM_FILE, D3DPOOL_MANAGED, D3DX_FILTER_LINEAR,                          D3DX_FILTER_LINEAR, 0, &img_info, 0, &d3d9texture_)))
    {
        THROW_D3D9EXCEPTION(
            D3D9GRAPHICSEXCEPTIONCODE_D3DXCREATETEXTUREFROMFILEINMEMORYEXERROR,
            hr, String(STRING("D3DXCreateCubeTextureFromFileInMemoryEx[%s]"),
            getUri().c_str()));
        return false;
    }
    return true;
}


//-----------------------------------------------------------------------------
bool D3D9CubeTexture::lockRect
(int level, const Rect* rect, void*& out_ptr, int* out_pitch,
 bool discard, bool read_only)
{
    // not implement
    return false;
}


//-----------------------------------------------------------------------------
bool D3D9CubeTexture::unlockRect(int level)
{
    // not implement
    return false;
}


//-----------------------------------------------------------------------------
void D3D9CubeTexture::use(int index)
{
    // not implement
}


//-----------------------------------------------------------------------------
void D3D9CubeTexture::useAsRenderTarget(int index)
{
    if (0 == d3d9texture_)
        return;
}


//-----------------------------------------------------------------------------
int D3D9CubeTexture::width() const
{
    // not implement
    return -1;
}


//-----------------------------------------------------------------------------
int D3D9CubeTexture::height() const
{
    // not implement
    return -1;
}


//-----------------------------------------------------------------------------
bool D3D9CubeTexture::valid() const
{
    return d3d9texture_?true:false;
}


//-----------------------------------------------------------------------------
void D3D9CubeTexture::onLostDevice()
{
    // not implement
}


//-----------------------------------------------------------------------------
void D3D9CubeTexture::onRestoreDevice()
{
    // not implement
}


//-----------------------------------------------------------------------------
IDirect3DBaseTexture9* D3D9CubeTexture::getDirect3DTexture9()
{
    return d3d9texture_;
}
