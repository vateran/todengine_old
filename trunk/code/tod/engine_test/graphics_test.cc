#include "tod/engine_test/graphics_test.h"

#include <Windows.h>
#include <MMSystem.h>
#include "tod/core/cwnguard.h"
#include "tod/core/ref.h"
#include "tod/core/kernel.h"
#include "tod/core/exception.h"
#include "tod/core/linknode.h"
#include "tod/core/compositeproperty.h"
#include "tod/engine/displaymode.h"
#include "tod/engine/renderer.h"
#include "tod/engine/mesh.h"
#include "tod/engine/vertexbuffer.h"
#include "tod/engine/shader.h"
#include "tod/engine/texture.h"
#include "tod/engine/types.h"
#include "tod/engine/renderpath.h"
#include "tod/engine/rpsection.h"
#include "tod/engine/rppass.h"
#include "tod/engine/rprendertarget.h"
#include "tod/engine/sceneserver.h"
#include "tod/engine/scenecontext.h"
#include "tod/engine/meshnode.h"
#include "tod/engine/cameranode.h"
#include "tod/engine/timenode.h"
#include "tod/engine/timeserver.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
void GraphicsTestCase::test_Format()
{
    TODUNIT_ASSERT(sizeof(Format) == 4);
    Format format;
    format = Format::A1R5G5B5;
    TODUNIT_ASSERT(format.toString() == STRING("A1R5G5B5"));
    format = STRING("R8G8B8");
    TODUNIT_ASSERT(format == Format::R8G8B8);

    Format::Value values[] =
    {
        Format::R8G8B8, Format::A8R8G8B8, Format::X8R8G8B8,
        Format::R5G6B5, Format::X1R5G5B5, Format::A1R5G5B5,
        Format::A4R4G4B4, Format::R3G3B2, Format::A8, Format::A8R3G3B2,
        Format::X4R4G4B4, Format::A2B10G10R10, Format::G16R16, Format::A8P8,
        Format::P8, Format::L8, Format::A8L8, Format::A4L4, Format::V8U8,
        Format::L6V5U5, Format::X8L8V8U8, Format::Q8W8V8U8, Format::V16U16,
        Format::W11V11U10, Format::A2W10V10U10, Format::UYVY, Format::YUY2,
        Format::DXT1, Format::DXT2, Format::DXT3, Format::DXT4, Format::DXT5,
        Format::D16_LOCKABLE, Format::D32, Format::D15S1, Format::D24S8,
        Format::D16, Format::D24X8, Format::D24X4S4, Format::VERTEXDATA,
        Format::INDEX16, Format::INDEX32,
        Format::D32_LOCKABLE, Format::S8_LOCKABLE, Format::L16,
        Format::Q16W16V16U16, Format::MULTI2_ARGB8, Format::R16F,
        Format::G16R16F, Format::A16B16G16R16F, Format::R32F, Format::G32R32F,
        Format::A32B32G32R32F, Format::CxV8U8, Format::A1,
    };

    int index = 0;
    for (Format::enumerator e = format.beginEnum(); e != format.endEnum(); ++e)
        TODUNIT_ASSERT(*e == values[index++]);
}

//-----------------------------------------------------------------------------
void GraphicsTestCase::test_DisplayMode()
{
    DisplayMode display_mode(
        STRING("w[640]h[480]f[A8R8G8B8]sbuf[8]zbuf[24]fullscreen[false]title[test]vsync[false]"));
    TODUNIT_ASSERT(display_mode.getWidth() == 640);
    TODUNIT_ASSERT(display_mode.getHeight() == 480);
    TODUNIT_ASSERT(display_mode.getFormat() == Format::A8R8G8B8);
    TODUNIT_ASSERT(display_mode.getDepthAndStencilFormat() == Format::D24S8);
    TODUNIT_ASSERT(!display_mode.isFullscreen());
    TODUNIT_ASSERT(display_mode.isWindowed());
    TODUNIT_ASSERT(display_mode.getTitle() == STRING("test"));
    TODUNIT_ASSERT(!display_mode.isVSync());
}


//-----------------------------------------------------------------------------
#define IDD_RENDERTESTDIALOG            101
BOOL CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    return FALSE;
}
#include <d3dx9.h>
void GraphicsTestCase::test_D3D9Renderer()
{
    HWND hwnd = CreateDialog(
        GetModuleHandle(0),
        MAKEINTRESOURCE(IDD_RENDERTESTDIALOG),
        0,
        DialogProc);
    ShowWindow(hwnd, SW_NORMAL);

    typedef Ref<Renderer> RefRenderer;
    RefRenderer renderer = Kernel::instance()->create(
        STRING("D3D9Renderer"), STRING("/sys/server/renderer"));
    renderer->setDisplayMode(STRING("w[640]h[480]f[A8R8G8B8]sbuf[8]zbuf[24]fullscreen[false]title[test]"));
    DestroyWindow(hwnd);
    renderer->detach();
}


//-----------------------------------------------------------------------------
void GraphicsTestCase::test_VertexBuffer()
{
    try
    {
        HWND hwnd = CreateDialog(
            GetModuleHandle(0),
            MAKEINTRESOURCE(IDD_RENDERTESTDIALOG),
            0,
            DialogProc);
        ShowWindow(hwnd, SW_NORMAL);

        typedef Ref<Renderer> RefRenderer;
        RefRenderer renderer = Kernel::instance()->create(
            STRING("D3D9Renderer"), STRING("/sys/server/renderer"));
        renderer->setDisplayMode(STRING("w[640]h[480]f[A8R8G8B8]sbuf[8]zbuf[24]fullscreen[false]title[test]"));

        struct CUSTOMVERTEX
        {
            FLOAT x, y, z; // The transformed position for the vertex.
            DWORD diffuse;
            FLOAT u,v;
        };
        CUSTOMVERTEX vertices[] =
        {
            -3.0f, -3.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), 0, 1,
            -3.0f,  3.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 255), 0, 0,
            3.0f, -3.0f, 0.0f,  D3DCOLOR_XRGB(255, 0, 255), 1, 1,
            3.0f,  3.0f, 0.0f,  D3DCOLOR_XRGB(255, 255, 0), 1, 0,
        };
        VertexBuffer* vb = renderer->newVertexBuffer(
            STRING("managed://test#test.vb"));
        vb->create(4,
            VERTEXCOMPONENT_COORD |
            VERTEXCOMPONENT_COLOR |
            VERTEXCOMPONENT_UV0, 0);
        void* ptr;
        vb->lock(ptr);
        memcpy(ptr, vertices, sizeof(vertices));
        vb->unlock();

        Shader* shader = renderer->newShader(
            STRING("managed://shader#test_shader00.fx"));
        shader->preload();

        Texture* texture = renderer->newTexture(
            STRING("managed://texture#t0.jpg"));
        texture->preload();

        shader->setTexture(STRING("Diffuse"), texture);

        while (!GetAsyncKeyState(VK_ESCAPE))
        {
            renderer->clearScene(
                Color(0, 0, 255, 255), 1.0f, 0, true, true, true);
            renderer->beginScene();

            // 각종 Matrix 들을 설정한다.
            Matrix44 matWorld;
            //matWorld.identity();
            matWorld.rotateY(timeGetTime()/300.0f);

            Vector3 vEyePt   ( 0.0f, 0.0f,-20.0f );
            Vector3 vLookatPt( 0.0f, 0.0f, 0.0f );
            Vector3 vUpVec   ( 0.0f, 1.0f, 0.0f );
            Matrix44 matView;
            matView.lookAtLH(vEyePt, vLookatPt, vUpVec);

            Matrix44 matProj;
            matProj.perspectiveFovLH(3.14f/4.0f, 1.0f, 1.0f, 100.0f);

            shader->setTechnique(STRING("Test"));

            // 각 Matrix 를 shader 파라메터로 전달한다.
            Matrix44 m = matWorld * matView * matProj;
            shader->setMatrix(STRING("WorldViewProjectionMatrix"), m);            
            shader->commit();

            // effect 를 적용하여 그린다.
            uint32_t num_pass = 0;
            shader->begin(num_pass);
            vb->use();
            for (uint32_t pass = 0; pass < num_pass; ++pass)
            {
                shader->beginPass(pass);
                vb->draw(PRIMITIVETYPE_TRIANGLESTRIP);
                shader->endPass();
            }
            shader->end();

            renderer->endScene();
            renderer->presentScene(reinterpret_cast<int>(hwnd));
            Sleep(0);

            MSG msg;
            while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        DestroyWindow(hwnd);
        renderer->detach();
    }
    catch(const tod::Exception& e)
    {
        String s(STRING("%s(%d) :\n\nException(%d):%s:\n%s"),
            e.getFile().c_str(), e.getLine(), e.getErrorCode(),
            e.getFunction().c_str(), e.getDescription().c_str());
        MessageBox(0, s.c_str(), STRING("TodEngine Exception"), MB_OK);
    }
}


//-----------------------------------------------------------------------------
void GraphicsTestCase::test_Mesh()
{
    try
    {
        HWND hwnd = CreateDialog(
            GetModuleHandle(0),
            MAKEINTRESOURCE(IDD_RENDERTESTDIALOG),
            0,
            DialogProc);
        ShowWindow(hwnd, SW_NORMAL);

        typedef Ref<Renderer> RefRenderer;
        RefRenderer renderer = Kernel::instance()->create(
            STRING("D3D9Renderer"), STRING("/sys/server/renderer"));
        renderer->setDisplayMode(STRING("w[640]h[480]f[A8R8G8B8]sbuf[8]zbuf[24]fullscreen[false]title[test]"));

        Mesh* mesh = renderer->newMesh(STRING("managed://mesh#tiger.x"));
        mesh->preload(true, true, true);

        Shader* shader = renderer->newShader(
            STRING("managed://shader#test_shader01.fx"));
        shader->preload();

        Texture* texture = renderer->newTexture(
            STRING("managed://texture#tiger.dds"));
        texture->preload();

        shader->setTexture(STRING("Diffuse"), texture);

        while (!GetAsyncKeyState(VK_ESCAPE))
        {
            renderer->clearScene(
                Color(0, 0, 255, 255), 1.0f, 0, true, true, true);
            renderer->beginScene();

            // 각종 Matrix 들을 설정한다.
            Matrix44 matWorld;
            //matWorld.identity();
            matWorld.rotateY(timeGetTime()/1000.0f);

            Vector3 vEyePt   ( 0.0f, 0.0f,-5.0f );
            Vector3 vLookatPt( 0.0f, 0.0f, 0.0f );
            Vector3 vUpVec   ( 0.0f, 1.0f, 0.0f );
            Matrix44 matView;
            matView.lookAtLH(vEyePt, vLookatPt, vUpVec);

            Matrix44 matProj;
            matProj.perspectiveFovLH(3.14f/4.0f, 1.0f, 1.0f, 100.0f);

            shader->setTechnique(STRING("Test"));

            // 각 Matrix 를 shader 파라메터로 전달한다.
            Matrix44 m = matWorld * matView * matProj;
            shader->setMatrix(STRING("WorldViewProjectionMatrix"), m);
            shader->setFloat(STRING("Time"), timeGetTime() / 1000.0f);
            shader->commit();

            // effect 를 적용하여 그린다.
            uint32_t num_pass = 0;
            shader->begin(num_pass);
            for (uint32_t pass = 0; pass < num_pass; ++pass)
            {
                shader->beginPass(pass);                
                mesh->draw();
                shader->endPass();
            }
            shader->end();

            renderer->endScene();
            renderer->presentScene(reinterpret_cast<int>(hwnd));
            Sleep(0);

            MSG msg;
            while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        DestroyWindow(hwnd);
        renderer->detach();
    }
    catch(const tod::Exception& e)
    {
        String s(STRING("%s(%d) :\n\nException(%d):%s:\n%s"),
            e.getFile().c_str(), e.getLine(), e.getErrorCode(),
            e.getFunction().c_str(), e.getDescription().c_str());
        MessageBox(0, s.c_str(), STRING("TodEngine Exception"), MB_OK);
    }
}


//-----------------------------------------------------------------------------
void GraphicsTestCase::test_Scene()
{
    try
    {
        /*HWND hwnd = CreateDialog(
            GetModuleHandle(0),
            MAKEINTRESOURCE(IDD_RENDERTESTDIALOG),
            0,
            DialogProc);
        ShowWindow(hwnd, SW_NORMAL);

        Ref<TimeServer> ts= Kernel::instance()->create(
            STRING("TimeServer"), STRING("/sys/server/time"));

        typedef Ref<Renderer> RefRenderer;
        RefRenderer renderer = Kernel::instance()->create(
            STRING("D3D9Renderer"), STRING("/sys/server/renderer"));
        renderer->setDisplayMode(STRING("w[640]h[480]f[A8R8G8B8]sbuf[8]zbuf[24]fullscreen[false]title[test]"));

        typedef Ref<SceneServer> RefSceneServer;
        RefSceneServer scene_server = Kernel::instance()->create(
            STRING("SceneServer"), STRING("/sys/server/sceneserver"));
        typedef Ref<TransformNode> RefTransformNode;
        RefTransformNode scene_root = Kernel::instance()->create(
            STRING("TransformNode"), STRING("/usr/scene"));
        typedef Ref<MeshNode> RefMeshNode;
        RefMeshNode mesh_node = Kernel::instance()->create(
            STRING("MeshNode"), STRING("/usr/scene/mesh"));
        mesh_node->setShaderUri(STRING("managed://shader#mesh.fx"));
        mesh_node->setTechnique(STRING("Mesh"));
        mesh_node->setMeshUri(STRING("managed://mesh#tiger.x"));

        Ref<TimeNode> time_node = Kernel::instance()->create(
            STRING("TimeNode"), STRING("/usr/scene/time"));
        Ref<LinkNode> r_link = Kernel::instance()->create(
            STRING("LinkNode"), STRING("/usr/scene/r_link"));
        CompositeProperty<const Vector3&>* r_property =
            static_cast<CompositeProperty<const Vector3&>*>(mesh_node->
                getType().findProperty(STRING("euler_rotation")));
        Property* ry_property = r_property->findProperty(STRING("y"));
        Property* time_property = time_node->
            getType().findProperty(STRING("time"));
        r_link->connect(time_node, time_property, mesh_node, ry_property);

        Ref<CameraNode> camera_node = Kernel::instance()->create(
            STRING("CameraNode"), STRING("/usr/scene/camera"));
        camera_node->setRenderPathSection(STRING("default"));
        camera_node->setShaderUri(STRING("managed://shader#hdr.fx"));
        camera_node->setTranslation(Vector3(0, -10, 0));

        typedef Ref<RenderPath> RefRenderPath;
        RefRenderPath rp = Kernel::instance()->create(
            STRING("RenderPath"), STRING("/usr/renderpath"));
        Ref<RpSection> default_section = Kernel::instance()->create(
            STRING("RpSection"), STRING("/usr/renderpath/default"));
        Ref<RpPass> final_scene_pass = Kernel::instance()->create(
            STRING("RpPass"),
            STRING("/usr/renderpath/default/final_scene"));
        final_scene_pass->setClearColor(Color(0, 0, 255, 255));
        final_scene_pass->setDrawQuad(true);
        final_scene_pass->setShaderUri(STRING("managed://shader#hdr.fx"));
        final_scene_pass->setTechnique(STRING("ComposeScene"));
        SimpleVariable<float>* time_shader_param =
            static_cast<SimpleVariable<float>*>(
            final_scene_pass->addShaderParam<float>(STRING("Time")));
        Ref<RpRenderTarget> final_scene = Kernel::instance()->create(
            STRING("RpRenderTarget"),
            STRING("/usr/renderpath/default/final_scene/rt"));
        final_scene->setTextureUri(STRING("managed://rt#final_scene"));
        final_scene->setFormat(STRING("X8R8G8B8"));
        
        SceneContext scene_context;
        scene_context.setRootSceneNode(scene_root);
        while (!GetAsyncKeyState(VK_ESCAPE))
        {
            ts->sleep(0.001);
            ts->trigger();
            r_link->update();
            *time_shader_param = static_cast<float>(
                TimeServer::instance()->getTime());

            scene_server->beginScene();
            scene_server->attach(&scene_context);
            scene_server->endScene();
            scene_server->renderScene();
            scene_server->presentScene(reinterpret_cast<int>(hwnd));

            MSG msg;
            while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        DestroyWindow(hwnd);
        renderer->detach();*/
    }
    catch(const tod::Exception& e)
    {
        String s(STRING("%s(%d) :\n\nException(%d):%s:\n%s"),
            e.getFile().c_str(), e.getLine(), e.getErrorCode(),
            e.getFunction().c_str(), e.getDescription().c_str());
        MessageBox(0, s.c_str(), STRING("TodEngine Exception"), MB_OK);
    }
}
