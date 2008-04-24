#ifndef TOD_ENGINE_GRAPHICS_RENDERPATH_RENDERTARGET_H
#define TOD_ENGINE_GRAPHICS_RENDERPATH_RENDERTARGET_H
/**
    @ingroup TodEngineGraphicsRenderPath
    @class tod::engine::graphics::RpRenderTarget
    @brief 
*/

#include "tod/core/node.h"
#include "tod/core/uri.h"
#include "tod/engine/resourceref.h"
#include "tod/engine/format.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class Texture;
    class RpRenderTarget : public core::Node
    {
    public:
        RpRenderTarget();
        virtual~RpRenderTarget();
        DECLARE_CLASS(RpRenderTarget, core::Node);

        void preload();

        void begin();
        void end();

        void setAlias(const core::Name& alias);
        const core::Name& getAlias() const;

        void setTextureUri(const core::Uri& uri);
        const core::Uri& getTextureUri() const;

        void setFormat(const Format& format);
        const Format& getFormat() const;

        void setRelativeSize(float s);
        float getRelativeSize() const;

        Texture* getTexture();

        static void bindProperty();

    private:
        void create_texture();

    private:
        ResourceRef<Texture> texture_;
        core::Name alias_;
        core::Uri uri_;
        Format format_;
        float relativeSize_;
    };
}
}
}

#endif // TOD_ENGINE_GRAPHICS_RENDERPATH_RENDERTARGET_H
