#include "tod/d3d9graphics/d3d9shader.h"

#include "tod/core/define.h"
#include "tod/core/assert.h"
#include "tod/core/log.h"
#include "tod/core/resource.h"
#include "tod/core/exception.h"
#include "tod/d3d9graphics/d3d9exception.h"
#include "tod/d3d9graphics/d3d9texture.h"
#include "tod/d3d9graphics/d3d9cubetexture.h"
#include "tod/d3d9graphics/d3d9renderer.h"

using namespace tod;
using namespace tod::engine;

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
    tod_assert(d3deffectpool_);
    if (d3deffect_)
        return true;

    tod::Resource resource(getUri());
    if (!resource.open(
        tod::Resource::OPEN_READ |
        tod::Resource::OPEN_BINARY))
        return false;

    dynamic_buffer_t buffer;
    resource.read(&buffer);

    ID3DXBuffer* compilation_error;
    HRESULT hr;
    if (FAILED(hr = D3DXCreateEffect(d3d9device_, &buffer[0],
        static_cast<UINT>(buffer.size()), 0, 0,
        0, d3deffectpool_, &d3deffect_, &compilation_error)))
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
void D3D9Shader::begin(uint32_t& num_pass, bool restore)
{
    if (0 == d3deffect_)
        return;
    DWORD flags = 0;
        
    if (!restore)
    {
        flags =
            D3DXFX_DONOTSAVESTATE |
            D3DXFX_DONOTSAVESAMPLERSTATE |
            D3DXFX_DONOTSAVESHADERSTATE;
    }

    d3deffect_->Begin(reinterpret_cast<UINT*>(&num_pass), flags);
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
void D3D9Shader::setInt(const String& name, int v)
{
    if (0 == d3deffect_)
        return;
    D3DXHANDLE h = d3deffect_->
        GetParameterByName(0, name.toAnsiString().c_str());
    if (0 == h)
        return;
    d3deffect_->SetInt(h, v);
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
void D3D9Shader::setMatrixArray
(const String& name, const Matrix44* ma, uint32_t count)
{
    if (0 == d3deffect_)
        return;
    D3DXHANDLE h = d3deffect_->
        GetParameterByName(0, name.toAnsiString().c_str());
    if (0 == h)
        return;
    d3deffect_->SetMatrixArray(h, reinterpret_cast<const D3DXMATRIX*>(ma), count);
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
    
    if (D3D9Texture* d3dt = DOWN_CAST<D3D9Texture*>(t))
        d3deffect_->SetTexture(h, d3dt->getDirect3DTexture9());
    else if (D3D9CubeTexture* d3dct = DOWN_CAST<D3D9CubeTexture*>(t))
        d3deffect_->SetTexture(h, d3dct->getDirect3DTexture9());
    else
        d3deffect_->SetTexture(h, 0);
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


//-----------------------------------------------------------------------------
uint32_t D3D9Shader::getParameterNum() const
{
    D3DXEFFECT_DESC desc;
    d3deffect_->GetDesc(&desc);
    return desc.Parameters;
}


//-----------------------------------------------------------------------------
ShaderParamDesc D3D9Shader::getParameterDesc(uint32_t index)
{
    D3DXHANDLE handle = d3deffect_->GetParameter(0, index);
    D3DXPARAMETER_DESC d3ddesc;
    d3deffect_->GetParameterDesc(handle, &d3ddesc);
    
    ShaderParamDesc result;
    if (d3ddesc.Name)
        result.name_ = d3ddesc.Name;
    if (d3ddesc.Semantic)
        result.semantic_ = d3ddesc.Semantic;
    result.type_ = static_cast<ShaderParamDesc::Type>(d3ddesc.Type);

    switch (d3ddesc.Type)
    {
    case D3DXPT_BOOL:
        {
            BOOL value;
            d3deffect_->GetBool(handle, &value);
            char_t buf[4];
            tod_snprintf(buf, 4, STRING("%d"), value);
            result.value_ = buf;
            break;
        }
    case D3DXPT_INT:
        {
            INT value;
            d3deffect_->GetInt(handle, &value);
            char_t buf[16];
            tod_snprintf(buf, 16, STRING("%d"), value);
            result.value_ = buf;
            break;
        }
    case D3DXPT_FLOAT:
        {
            FLOAT value;
            d3deffect_->GetFloat(handle, &value);
            char_t buf[32];
            tod_snprintf(buf, 32, STRING("%.3f"), value);
            result.value_ = buf;
            break;
        }
    case D3DXPT_STRING:
        {
            LPCSTR value;
            d3deffect_->GetString(handle, &value);
            char_t buf[32];
            tod_snprintf(buf, 32, STRING(""), value);
            result.value_ = buf;
            break;
        }
    case D3DXPT_TEXTURE:
    case D3DXPT_TEXTURE1D:
    case D3DXPT_TEXTURE2D:
    case D3DXPT_TEXTURE3D:
    case D3DXPT_TEXTURECUBE:
        {
            IDirect3DBaseTexture9* value = 0;
            d3deffect_->GetTexture(handle, &value);
            D3D9Renderer* r = dynamic_cast<D3D9Renderer*>(Renderer::instance());
            Texture* texture = r->findTextureByD3D9Texture(value);
            if (texture)
                result.value_ = texture->getUri();
            break;
        }
    default:
        break;
    }

    return result;
}
