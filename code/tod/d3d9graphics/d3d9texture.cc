#include "tod/d3d9graphics/d3d9texture.h"

#include <d3dx9.h>
#include "tod/core/assert.h"
#include "tod/core/exception.h"
#include "tod/core/resource.h"
#include "tod/engine/types.h"
#include "tod/d3d9graphics/d3d9exception.h"

using namespace tod::core;
using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
D3D9Texture::D3D9Texture(const Uri& uri, IDirect3DDevice9* d3d9device):
Texture(uri), d3d9device_(d3d9device), d3d9texture_(0), d3dusage_(0)
{
    d3d9device_->AddRef();
}


//-----------------------------------------------------------------------------
D3D9Texture::~D3D9Texture()
{
    destroy();
    SAFE_RELEASE(d3d9device_);
}


//-----------------------------------------------------------------------------
bool D3D9Texture::create(int width, int height, int mipmap_level, Format format, int usage)
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

    HRESULT hr;
    if (FAILED(hr = d3d9device_->CreateTexture(
        width, height, mipmap_level, d3dusage_,
        format, pool, &d3d9texture_, 0)))
        THROW_D3D9EXCEPTION(D3D9GRAPHICSEXCEPTIONCODE_CREATETEXTUREERROR,
            hr, STRING("d3d9device_->CreateTexture"));
    return true;
}


//-----------------------------------------------------------------------------
void D3D9Texture::destroy()
{
    SAFE_RELEASE(d3d9texture_);
}


//-----------------------------------------------------------------------------
bool D3D9Texture::preload()
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

    HRESULT hr;
    if (FAILED(hr = D3DXCreateTextureFromFileInMemoryEx(d3d9device_,
        &buffer[0], static_cast<UINT>(buffer.size()),
        D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_FROM_FILE, D3DPOOL_MANAGED, 
        D3DX_DEFAULT, D3DX_DEFAULT, 0, &info_, 0, &d3d9texture_)))
    {
        THROW_D3D9EXCEPTION(
            D3D9GRAPHICSEXCEPTIONCODE_D3DXCREATETEXTUREFROMFILEINMEMORYEXERROR,
            hr, String(STRING("D3DXCreateTextureFromFileInMemoryEx[%s]"),
            getUri().c_str()));
        return false;
    }
    return true;
}


//-----------------------------------------------------------------------------
bool D3D9Texture::lockRect
(int level, const Rect* rect, void*& out_ptr, int* out_pitch,
 bool discard, bool read_only)
{
    tod_assert(d3d9texture_);

    int lock_flags = 0;
    D3DLOCKED_RECT locked_rect;

    if (discard)
    {
        if (0 != rect)
            lock_flags |= D3DLOCK_DISCARD;
    }
    if (read_only)
        lock_flags |= D3DLOCK_READONLY;

    if (FAILED(d3d9texture_->LockRect(
        level, &locked_rect,
        reinterpret_cast<CONST RECT*>(rect),
        lock_flags)))
        return false;
    return true;
}


//-----------------------------------------------------------------------------
bool D3D9Texture::unlockRect(int level)
{
    tod_assert(d3d9texture_);

    if (FAILED(d3d9texture_->UnlockRect(level)))
        return false;
    return true;
}


//-----------------------------------------------------------------------------
void D3D9Texture::use(int index)
{
    if (0 == d3d9texture_)
        return;
    d3d9device_->SetTexture(index, d3d9texture_);
}


//-----------------------------------------------------------------------------
void D3D9Texture::useAsRenderTarget(int index)
{
    if (0 == d3d9texture_)
        return;
    IDirect3DSurface9* s = 0;
    if (FAILED(d3d9texture_->GetSurfaceLevel(0, &s)))
        return;
    d3d9device_->SetRenderTarget(index, s);
    s->Release();
}


//-----------------------------------------------------------------------------
int D3D9Texture::width() const
{
    return info_.Width;
}


//-----------------------------------------------------------------------------
int D3D9Texture::height() const
{
    return info_.Height;
}


//-----------------------------------------------------------------------------
bool D3D9Texture::valid() const
{
    return d3d9texture_?true:false;
}


//-----------------------------------------------------------------------------
void D3D9Texture::onLostDevice()
{
    // not implement
}


//-----------------------------------------------------------------------------
void D3D9Texture::onRestoreDevice()
{
    // not implement
}


//-----------------------------------------------------------------------------
IDirect3DBaseTexture9* D3D9Texture::getDirect3DTexture9()
{
    return d3d9texture_;
}
