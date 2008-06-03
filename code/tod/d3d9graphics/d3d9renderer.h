#ifndef TOD_D3D9GRAPHICS_D3D9RENDERER_H
#define TOD_D3D9GRAPHICS_D3D9RENDERER_H
/**
    @ingroup D3D9Graphics
    @class tod::engine::D3D9Renderer
    @brief
*/

#if defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif

#include <stack>
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "tod/engine/renderer.h"
#include "tod/engine/resourceref.h"
#include "tod/engine/resourcehoder.h"

namespace tod
{
namespace engine
{
    class D3D9Renderer : public Renderer
    {
    public:
        D3D9Renderer();
        virtual~D3D9Renderer();
        DECLARE_CLASS(D3D9Renderer, Renderer);

        override void clearScene(
            const Color& color, float z, uint32_t stencil,
            bool clear_target, bool clear_zbuf, bool clear_sbuf);
        override void beginScene();
        override void endScene();
        override void presentScene(int windowid_override=0);

        override Mesh* newMesh(const Uri& uri);
        override VertexBuffer* newVertexBuffer(const Uri& uri);
        override IndexBuffer* newIndexBuffer(const Uri& uri);
        override Texture* newTexture(const Uri& uri);
        override Texture* newCubeTexture(const Uri& uri);
        override Shader* newShader(const Uri& uri);

        override void setDisplayMode(const DisplayMode& display_mode);
        override const DisplayMode& getDisplayMode() const;

        override void pushRenderTarget(Texture* texture);
        override Texture* popRenderTarget();
        override Texture* getRenderTarget();

        override void pushShader(Shader* shader);
        override Shader* popShader();
        override void setShader(Shader* shader);
        override Shader* getShader();

        override void setTransform(Transform type, const Matrix44& m);

        override void drawQuad(const Rect& r, const Color& color);

    private:
        typedef std::stack<Texture*> RenderTargetStack;
        typedef std::stack<Shader*> ShaderStack;

    private:
        void initialize_window(const DisplayMode& display_mode);
        void finalize_window();
        static LRESULT CALLBACK message_proc(HWND, UINT, WPARAM, LPARAM);

    private:
        DisplayMode displayMode_;
        IDirect3D9* d3d9_;
        IDirect3DDevice9* d3d9device_;
        ID3DXEffectPool* d3deffectpool_;
        IDirect3DSurface9* d3dbasicRenderTarget_;
        ID3DXSprite* d3dsprite_;
        D3DPRESENT_PARAMETERS d3dpp_;
        HWND windowHandle_;

        RenderTargetStack renderTargetStack_;
        ShaderStack shaderStack_;

        ResourceRef<VertexBuffer> quadVb_;

        ResourceHolder<Shader> shaders_;
        ResourceHolder<Texture> textures_;
        ResourceHolder<VertexBuffer> vertexBuffers_;
        ResourceHolder<IndexBuffer> indexBuffers_;
        ResourceHolder<Mesh> meshes_;

    };
}
}

#endif // TOD_D3D9GRAPHICS_D3D9RENDERER_H
