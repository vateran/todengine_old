#include "tod/d3d9graphics/d3d9renderer.h"

#include <WindowsX.h>
#include <d3dx9.h>
#include "tod/core/assert.h"
#include "tod/core/exception.h"
#include "tod/d3d9graphics/d3d9exception.h"
#include "tod/d3d9graphics/d3d9mesh.h"
#include "tod/d3d9graphics/d3d9vertexbuffer.h"
#include "tod/d3d9graphics/d3d9indexbuffer.h"
#include "tod/d3d9graphics/d3d9texture.h"
#include "tod/d3d9graphics/d3d9cubetexture.h"
#include "tod/d3d9graphics/d3d9shader.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
IMPLEMENT_CLASS(D3D9Renderer, Renderer);

//-----------------------------------------------------------------------------
D3D9Renderer::D3D9Renderer():
d3d9_(0), d3d9device_(0), d3dbasicRenderTarget_(0), d3deffectpool_(0),
d3dsprite_(0), d3dline_(0), windowHandle_(0), renderTarget_(0), shader_(0)
{
    d3d9_ = Direct3DCreate9(D3D_SDK_VERSION);
    if (0 == d3d9_)
        TOD_THROW_EXCEPTION(
            D3D9GRAPHICSEXCEPTIONCODE_COULDNOTCREATED3D9,
            "Could not create IDirect3D9");
}


//-----------------------------------------------------------------------------
D3D9Renderer::~D3D9Renderer()
{
    shaders_.clear();
    textures_.clear();
    vertexBuffers_.clear();
    indexBuffers_.clear();
    meshes_.clear();
    quadVb_.release();
    shader_.release();
    renderTarget_.release();
    while (shaderStack_.size()) shaderStack_.pop();
    while (renderTargetStack_.size()) renderTargetStack_.pop();
    SAFE_RELEASE(d3dline_);
    SAFE_RELEASE(d3dsprite_);
    SAFE_RELEASE(d3deffectpool_);
    SAFE_RELEASE(d3dbasicRenderTarget_);
    SAFE_RELEASE(d3d9device_);
    SAFE_RELEASE(d3d9_);
    finalize_window();
}


//-----------------------------------------------------------------------------
void D3D9Renderer::clearScene
(const Color& color, float z, uint32_t stencil,
 bool clear_target, bool clear_zbuf, bool clear_sbuf)
{
    tod_assert(d3d9device_);

    DWORD flag = 0;
    if (clear_target)
        flag |= D3DCLEAR_TARGET;
    if (clear_zbuf)
        flag |= D3DCLEAR_ZBUFFER;
    if (clear_sbuf)
        flag |= D3DCLEAR_STENCIL;
    d3d9device_->Clear(0, 0, flag, color.data_, z, stencil);
}


//-----------------------------------------------------------------------------
void D3D9Renderer::beginScene()
{
    tod_assert(d3d9device_);
    d3d9device_->BeginScene();
}


//-----------------------------------------------------------------------------
void D3D9Renderer::endScene()
{
    tod_assert(d3d9device_);
    d3d9device_->EndScene();
}


//-----------------------------------------------------------------------------
void D3D9Renderer::presentScene(int windowid_override)
{
    tod_assert(d3d9device_);
    d3d9device_->Present(0, 0, reinterpret_cast<HWND>(windowid_override), 0);
}


//-----------------------------------------------------------------------------
Mesh* D3D9Renderer::newMesh(const Uri& uri)
{
    Mesh* mesh = meshes_.find(uri);
    if (0 == mesh)
    {
        mesh = new D3D9Mesh(uri, d3d9device_);
        meshes_.add(mesh);
    }
    return mesh;
}


//-----------------------------------------------------------------------------
VertexBuffer* D3D9Renderer::newVertexBuffer(const Uri& uri)
{
    VertexBuffer* vb = 0;
    if (!uri.empty())
    {
        // find exist vertex buffer in named resources
        vb = vertexBuffers_.find(uri);
        if (vb)
            return vb;
    }

    // create new vertex buffer
    vb = new D3D9VertexBuffer(uri, d3d9device_);
    vertexBuffers_.add(vb);
    return vb;
}


//-----------------------------------------------------------------------------
IndexBuffer* D3D9Renderer::newIndexBuffer(const Uri& uri)
{
    IndexBuffer* ib = 0;
    if (!uri.empty())
    {
        // find exist index buffer in named resources
        ib = indexBuffers_.find(uri);
        if (ib)
            return ib;
    }

    // create new index buffer
    ib = new D3D9IndexBuffer(uri, d3d9device_);
    indexBuffers_.add(ib);
    return ib;
}


//-----------------------------------------------------------------------------
Texture* D3D9Renderer::newTexture(const Uri& uri)
{
    Texture* t = textures_.find(uri);
    if (0 == t)
    {
        t = new D3D9Texture(uri, d3d9device_);
        textures_.add(t);
    }
    return t;
}


//-----------------------------------------------------------------------------
Texture* D3D9Renderer::newCubeTexture(const Uri& uri)
{
    Texture* t = textures_.find(uri);
    if (0 == t)
    {
        t = new D3D9CubeTexture(uri, d3d9device_);
        textures_.add(t);
    }
    return t;
}


//-----------------------------------------------------------------------------
Shader* D3D9Renderer::newShader(const Uri& uri)
{
    Shader* shader = shaders_.find(uri);
    if (0 == shader)
    {
        shader = new D3D9Shader(uri, d3d9device_, d3deffectpool_);
        shaders_.add(shader);
    }
    return shader;
}


//-----------------------------------------------------------------------------
void D3D9Renderer::setDisplayMode(const DisplayMode& display_mode)
{
    displayMode_ = display_mode;
    initialize_window(display_mode);

    // setup presentation parameters
    memset(&d3dpp_, 0, sizeof(d3dpp_));
    if (d3dpp_.Windowed = display_mode.isWindowed())
        d3dpp_.SwapEffect = D3DSWAPEFFECT_DISCARD;
    else
        d3dpp_.SwapEffect = D3DSWAPEFFECT_FLIP;
    Format ds_format = display_mode.getDepthAndStencilFormat();
    if (ds_format != Format::UNKNOWN)
    {
        d3dpp_.EnableAutoDepthStencil = true;
        d3dpp_.AutoDepthStencilFormat = ds_format;
    }
        
    d3dpp_.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp_.BackBufferCount = 1;
    if (display_mode.isVSync())
        d3dpp_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    else
        d3dpp_.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    d3dpp_.hDeviceWindow = windowHandle_;

    // create IDirect3DDevice9
    SAFE_RELEASE(d3d9device_);
    HRESULT hr;
    if(FAILED(hr = d3d9_->CreateDevice(
        D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle_,
        D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
        &d3dpp_, &d3d9device_)))
        THROW_D3D9EXCEPTION(D3D9GRAPHICSEXCEPTIONCODE_COULDNOTCREATED3D9DEVICE,
            hr, "d3d9_->CreateDevice");
    d3d9device_->GetRenderTarget(0, &d3dbasicRenderTarget_);

    // create ID3DXEffectPool
    SAFE_RELEASE(d3deffectpool_);
    if (FAILED(hr = D3DXCreateEffectPool(&d3deffectpool_)))
        THROW_D3D9EXCEPTION
            (D3D9GRAPHICSEXCEPTIONCODE_COULDNOTCREATED3D9EFFECTPOOL,
            hr, "D3DXCreateEffectPool");

    // create ID3DXSprite
    SAFE_RELEASE(d3dsprite_);
    if (FAILED(hr = D3DXCreateSprite(d3d9device_, &d3dsprite_)))
        THROW_D3D9EXCEPTION
            (D3D9GRAPHICSEXCEPTIONCODE_COULDNOTCREATED3DSPRITE,
            hr, "D3DXSprite");

    // create ID3DXLine
    SAFE_RELEASE(d3dline_);
    if (FAILED(hr = D3DXCreateLine(d3d9device_, &d3dline_)))
        THROW_D3D9EXCEPTION
            (D3D9GRAPHICSEXCEPTIONCODE_COULDNOTCREATED3DLINE,
            hr, "D3DXLine");
    d3dline_->SetAntialias(true);
    
    setup_quad();
}


//-----------------------------------------------------------------------------
const DisplayMode& D3D9Renderer::getDisplayMode() const
{
    return displayMode_;
}


//-----------------------------------------------------------------------------
void D3D9Renderer::setRenderTarget(Texture* texture)
{
    if (texture)
    {
        texture->useAsRenderTarget(0);
        renderTarget_ = texture;
    }
    else
    {
        renderTarget_.release();
        d3d9device_->SetRenderTarget(0, d3dbasicRenderTarget_);
    }
}


//-----------------------------------------------------------------------------
Texture* D3D9Renderer::getRenderTarget()
{
    return renderTarget_;
}


//-----------------------------------------------------------------------------
void D3D9Renderer::pushRenderTarget(Texture* texture)
{
    renderTargetStack_.push(texture);
    setRenderTarget(texture);    
}


//-----------------------------------------------------------------------------
void D3D9Renderer::popRenderTarget()
{
    tod_assert(renderTargetStack_.size() > 0);

    Texture* t = renderTargetStack_.top();
    renderTargetStack_.pop();

    if(renderTargetStack_.empty())
    {
        setRenderTarget(0);
    }
    else
    {
        setRenderTarget(t);
    }
}


//-----------------------------------------------------------------------------
void D3D9Renderer::setShader(Shader* shader)
{
    shader_ = shader;
}


//-----------------------------------------------------------------------------
Shader* D3D9Renderer::getShader()
{
    return shader_;
}


//-----------------------------------------------------------------------------
void D3D9Renderer::setTransform(Transform type, const Matrix44& m)
{
    super::setTransform(type, m);

    D3DTRANSFORMSTATETYPE tt = static_cast<D3DTRANSFORMSTATETYPE>(type);
    if (TRANSFORM_WORLD == type) return;
    d3d9device_->SetTransform(tt, reinterpret_cast<CONST D3DMATRIX*>(&m));
}


//-----------------------------------------------------------------------------
void D3D9Renderer::drawQuad(const Rect& r, const Color& color)
{
    struct VertexType
    {
        float x, y, z;
        Color diffuse;
        float u,v;
    };
    
    VertexType* ptr = 0;
    if (!quadVb_->lock(reinterpret_cast<void*&>(ptr)))
        return;

    float w = static_cast<float>(r.width_simple());
    float h = static_cast<float>(r.height_simple());

    // coord
    ptr[0].x = ptr[1].x = -0.5f;
    ptr[2].x = ptr[3].x = w - 0.5f;
    ptr[0].y = ptr[2].y = h - 0.5f;
    ptr[1].y = ptr[3].y = -0.5f;

    // color
    ptr[0].z = ptr[1].z = ptr[2].z = ptr[3].z = 0;
    ptr[0].diffuse = ptr[1].diffuse = ptr[2].diffuse = ptr[3].diffuse = color;

    // uv
    ptr[0].u = ptr[1].u = 0;
    ptr[2].u = ptr[3].u = 1;
    ptr[1].v = ptr[3].v = 0;
    ptr[2].v = ptr[0].v = 1;

    quadVb_->unlock();

    quadVb_->use();
    quadVb_->draw(PRIMITIVETYPE_TRIANGLESTRIP);
}


//-----------------------------------------------------------------------------
void D3D9Renderer::drawLine()
{
    d3dline_->Begin();

    Vector3 l[2];
    l[0].x_ = 100;
    l[0].y_ = 100;
    l[0].z_ = 0;
    l[1].x_ = 400;
    l[1].y_ = 100;
    l[1].z_ = 0;

    Matrix44 m;
    m.identity();
    
    d3dline_->DrawTransform((const D3DXVECTOR3*)&l, 2, (const D3DXMATRIX*)&m, Color(255, 255, 255, 255).data_);

    d3dline_->End();
}


//-----------------------------------------------------------------------------
IDirect3DDevice9* D3D9Renderer::getD3DDevice()
{
    return d3d9device_;
}


//-----------------------------------------------------------------------------
Texture* D3D9Renderer::findTextureByD3D9Texture(IDirect3DBaseTexture9* texture)
{
    for (ResourceHolder<Texture>::NamedResources::iterator
         i = textures_.begin();
         i != textures_.end(); ++i)
    {
        D3D9Texture* t = i->second;
        if (0 == t)
            continue;
        if (t->getDirect3DTexture9() == texture)
            return t;
    }

    return 0;
}


//-----------------------------------------------------------------------------
void D3D9Renderer::setup_quad()
{
    quadVb_.release();
    quadVb_ = newVertexBuffer("managed://stock#quad");
    quadVb_->create(4,
        VERTEXCOMPONENT_COORD |
        VERTEXCOMPONENT_COLOR |
        VERTEXCOMPONENT_UV0,
        USAGE_DYNAMIC);
}


//-----------------------------------------------------------------------------
void D3D9Renderer::initialize_window(const DisplayMode& display_mode)
{
    // finalize previous window handle
    finalize_window();

    if (display_mode.getTitle().empty())
        TOD_THROW_EXCEPTION(
            D3D9GRAPHICSEXCEPTIONCODE_TITLEISEMPTY,
            "Title paramter is empty");

    // register application's window
    String title = display_mode.getTitle();
    WNDCLASSEXA wc =
    {
        sizeof(WNDCLASSEX), CS_CLASSDC, message_proc, 0, 0,
        GetModuleHandle(0), 0, 0, 0, 0, title.c_str(), 0
    };
    if (!RegisterClassExA(&wc))
        TOD_THROW_EXCEPTION(
            D3D9GRAPHICSEXCEPTIONCODE_COULDNOTREGISTERWINDOW,
            "Could not register window");

    // Create the application's window.
    windowHandle_ = CreateWindowA(display_mode.getTitle(),
        display_mode.getTitle(), 
        WS_OVERLAPPEDWINDOW, 0, 0,
        display_mode.getWidth(), display_mode.getHeight(), 0, 0, wc.hInstance, 0);
    if (0 == windowHandle_)
        TOD_THROW_EXCEPTION(
            D3D9GRAPHICSEXCEPTIONCODE_COULDNOTCREATEWINDOW,
            "Could not create rendering window");
    RECT rect = { 0, 0, display_mode.getWidth(), display_mode.getHeight() };
    AdjustWindowRectEx(
        &rect, GetWindowStyle(windowHandle_),
        false, GetWindowExStyle(windowHandle_));
    OffsetRect(&rect, -rect.left, -rect.top);
    MoveWindow(windowHandle_, rect.left, rect.top,
        rect.right - rect.left, rect.bottom - rect.top, false);
    //ShowWindow(windowHandle_, SW_NORMAL);
}


//-----------------------------------------------------------------------------
void D3D9Renderer::finalize_window()
{
    if (windowHandle_)
        DestroyWindow(windowHandle_);
    windowHandle_ = 0;
    UnregisterClassA(displayMode_.getTitle(), GetModuleHandle(0));
}

//-----------------------------------------------------------------------------
LRESULT CALLBACK D3D9Renderer::message_proc
(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    return DefWindowProc(hwnd, msg, wparam, lparam);
}
