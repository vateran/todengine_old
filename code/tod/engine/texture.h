#ifndef TOD_ENGINE_GRAPHICS_CORE_TEXTURE_H
#define TOD_ENGINE_GRAPHICS_CORE_TEXTURE_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::graphics::Texture
    @brief 
*/

#include "tod/core/rect.h"
#include "tod/engine/format.h"
#include "tod/engine/resource.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class Texture : public Resource
    {
    public:
        Texture(const core::Uri& uri);
        virtual~Texture();

        virtual bool create(
            int width, int height, int mipmap_level,
            Format format, int usage)=0;
        virtual void destroy()=0;
        virtual bool preload()=0;

        virtual bool lockRect(
            int level, const core::Rect* rect,
            void*& out_ptr, int* out_pitch,
            bool discard=true, bool read_only=false)=0;
        virtual bool unlockRect(int level)=0;

        virtual void use(int index)=0;
        virtual void useAsRenderTarget(int index)=0;

        virtual int width() const=0;
        virtual int height() const=0;
    };
}
}
}


#endif // TOD_ENGINE_GRAPHICS_CORE_TEXTURE_H
