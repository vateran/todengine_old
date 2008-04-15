#include "tod/d3d9graphics/d3d9shader.h"

#include "tod/core/assert.h"
#include "tod/core/log.h"
#include "tod/core/resource.h"
#include "tod/core/exception.h"
#include "tod/d3d9graphics/d3d9exception.h"
#include "tod/d3d9graphics/d3d9texture.h"
#include "tod/d3d9graphics/d3d9cubetexture.h"

using namespace tod::core;
using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
D3D9Shader::D3D9Shader
(const Uri& uri, IDirect3DDevice9* d3d9device,
 ID3DXEffectPool* d3deffectpool):
Shader(uri), d3d9device_(d3d9device), d3deffect_(0),
d3deffectpool_(d3deffectpool)
{
    d3d9device_->AddRef();
    d3deffectpool_->AddRef();
}


//-----------------------------------------------------------------------------
D3D9Shader::~D3D9Shader()
{
    SAFE_RELEASE(d3deffect_);
    SAFE_RELEASE(d3deffectpool_);
    SAFE_RELEASE(d3d9device_);
}


//-----------------------------------------------------------------------------
bool D3D9Shader::preload()
{
    tod_assert(d3d9device_);

    tod::core::Resource resource(getUri());
    if (!resource.open(
        tod::core::Resource::OPEN_READ |
        tod::core::Resource::OPEN_BINARY))
        return false;

    dynamic_buffer_t buffer;
    resource.read(buffer);

    ID3DXBuffer* compilation_error;
    HRESULT hr;
    if (FAILED(hr = D3DXCreateEffect(d3d9device_, &buffer[0],
        static_cast<UINT>(buffer.size()), 0, 0,
        D3DXSHADER_DEBUG, d3deffectpool_, &d3deffect_, &compilation_error)))
    {
        tod_log_notice((STRING("%s\n"), compilation_error->GetBufferPointer()));
        THROW_D3D9EXCEPTION(
            D3D9GRAPHICSEXCEPTIONCODE_D3D9EFFECTCOMPILATIONERROR,
            hr, String("ID3DXEffect compilation error[%s]",
            compilation_error->GetBufferPointer()));
        SAFE_RELEASE(compilation_error);
        return false;
    }

    return true;
}


//-----------------------------------------------------------------------------
void D3D9Shader::begin(uint32_t& num_pass)
{
    if (0 == d3deffect_)
        return;
    d3deffect_->Begin(reinterpret_cast<UINT*>(&num_pass),
        D3DXFX_DONOTSAVESTATE |
        D3DXFX_DONOTSAVESAMPLERSTATE |
        D3DXFX_DONOTSAVESHADERSTATE);
}


//-----------------------------------------------------------------------------
void D3D9Shader::end()
{
    if (0 == d3deffect_)
        return;
    d3deffect_->End();
}


//-----------------------------------------------------------------------------
void D3D9Shader::beginPass(uint32_t pass)
{
    if (0 == d3deffect_)
        return;
    d3deffect_->BeginPass(pass);
}


//-----------------------------------------------------------------------------
void D3D9Shader::endPass()
{
    if (0 == d3deffect_)
        return;
    d3deffect_->EndPass();
}


//-----------------------------------------------------------------------------
void D3D9Shader::setTechnique(const String& name)
{
    if (0 == d3deffect_)
        return;
    D3DXHANDLE h = d3deffect_->GetTechniqueByName(name.toAnsiString().c_str());
    if (0 == h)
        return;
    d3deffect_->SetTechnique(h);
}


//-----------------------------------------------------------------------------
void D3D9Shader::setFloat(const String& name, float v)
{
    if (0 == d3deffect_)
        return;
    D3DXHANDLE h = d3deffect_->
        GetParameterByName(0, name.toAnsiString().c_str());
    if (0 == h)
        return;
    d3deffect_->SetFloat(h, v);
}


//-----------------------------------------------------------------------------
void D3D9Shader::setMatrix(const String& name, const Matrix44& m)
{
    if (0 == d3deffect_)
        return;
    D3DXHANDLE h = d3deffect_->
        GetParameterByName(0, name.toAnsiString().c_str());
    if (0 == h)
        return;
    d3deffect_->SetMatrix(h, reinterpret_cast<const D3DXMATRIX*>(&m));
}


//-----------------------------------------------------------------------------
void D3D9Shader::setTexture(const String& name, Texture* t)
{
    if (0 == d3deffect_)
        return;
    D3DXHANDLE h = d3deffect_->
        GetParameterByName(0, name.toAnsiString().c_str());
    if (0 == h)
        return;
    D3D9Texture* d3dt = DOWN_CAST<D3D9Texture*>(t);
    if (d3dt)
        d3deffect_->SetTexture(h, d3dt->getDirect3DTexture9());
    D3D9CubeTexture* d3dct = DOWN_CAST<D3D9CubeTexture*>(t);
    if (d3dct)
        d3deffect_->SetTexture(h, d3dct->getDirect3DTexture9());
}


//-----------------------------------------------------------------------------
void D3D9Shader::commit()
{
    if (0 == d3deffect_)
        return;
    d3deffect_->CommitChanges();
}


//-----------------------------------------------------------------------------
bool D3D9Shader::valid() const
{
    return d3deffect_ ? true:false;
}


//-----------------------------------------------------------------------------
void D3D9Shader::onLostDevice()
{
    d3deffect_->OnLostDevice();
}


//-----------------------------------------------------------------------------
void D3D9Shader::onRestoreDevice()
{
    d3deffect_->OnResetDevice();
}
