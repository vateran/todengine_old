#ifndef TOD_ENGINE_GRAPHICS_CORE_RENDERER_H
#define TOD_ENGINE_GRAPHICS_CORE_RENDERER_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::graphics::Renderer
    @brief 
*/

#include <stack>
#include "tod/core/color.h"
#include "tod/core/node.h"
#include "tod/core/rect.h"
#include "tod/core/uri.h"
#include "tod/core/matrix44.h"
#include "tod/core/singleton3.h"
#include "tod/engine/displaymode.h"
#include "tod/engine/types.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class Mesh;
    class Shader;
    class Texture;
    class IndexBuffer;
    class VertexBuffer;
    class Renderer :
        public core::Node,
        public core::Singleton3<Renderer>
    {
    public:
        Renderer();
        virtual~Renderer();
        DECLARE_ABSTRACTCLASS(Renderer, core::Node);

        virtual void clearScene(
            const core::Color& color, float z, core::uint32_t stencil,
            bool target, bool zbuf, bool sbuf)=0;
        virtual void beginScene()=0;
        virtual void endScene()=0;
        virtual void presentScene(int windowid_override=0)=0;

        virtual Mesh* newMesh(const core::Uri& uri)=0;
        virtual VertexBuffer* newVertexBuffer(const core::Uri& uri)=0;
        virtual IndexBuffer* newIndexBuffer(const core::Uri& uri)=0;
        virtual Texture* newTexture(const core::Uri& uri)=0;
        virtual Texture* newCubeTexture(const core::Uri& uri)=0;
        virtual Shader* newShader(const core::Uri& uri)=0;

        virtual void setDisplayMode(const DisplayMode& display_mode)=0;
        virtual const DisplayMode& getDisplayMode() const=0;
        virtual const core::String& getDisplayModeStr() const;

        virtual void pushRenderTarget(Texture* texture)=0;
        virtual Texture* popRenderTarget()=0;
        virtual Texture* getRenderTarget()=0;

        virtual void pushShader(Shader* shader)=0;
        virtual Shader* popShader()=0;
        virtual void setShader(Shader* shader)=0;
        virtual Shader* getShader()=0;

        virtual void setTransform(Transform type, const core::Matrix44& m);
        virtual const core::Matrix44& getTransform(Transform type) const;
        virtual void pushTransform(Transform type, const core::Matrix44& m);
        virtual void popTransform(Transform type);

        virtual void drawQuad(const core::Rect& r, const core::Color& color)=0;

        static void bindMethod();
        static void bindProperty();

    private:
        typedef std::stack<core::Matrix44> MatrixStack;

    private:
        void set_transform(Transform type, const core::Matrix44& m);

    private:
        MatrixStack matrixStack_[TRANSFORM_MAX];
        
    };
}
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_RENDERER_H
