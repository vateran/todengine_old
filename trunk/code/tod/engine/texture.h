#ifndef TOD_ENGINE_GRAPHICS_CORE_TEXTURE_H
#define TOD_ENGINE_GRAPHICS_CORE_TEXTURE_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::graphics::Texture
    @brief 
*/

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

        virtual void useAsRenderTarget(int index)=0;
    };
}
}
}


#endif // TOD_ENGINE_GRAPHICS_CORE_TEXTURE_H
