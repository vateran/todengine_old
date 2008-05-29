#ifndef TOD_ENGINE_GRAPHICS_CORE_IMAGE_H
#define TOD_ENGINE_GRAPHICS_CORE_IMAGE_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::graphics::Image
    @brief 
*/

#include "IL/il.h"
#include "tod/core/uri.h"
#include "tod/core/color.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class Image
    {
    public:
        Image(const core::Uri& uri);
        virtual~Image();

        bool create(int width, int height);
        void destroy();
        bool preload();

        int width() const;
        int height() const;
        const core::Uri& getUri() const;

        core::Color getPixel(int x, int y) const;

    private:
        core::Uri uri_;

        ILuint id_;
        
        int width_;
        int height_;
        core::Color* data_;
    };
}
}
}


#endif // TOD_ENGINE_GRAPHICS_CORE_TEXTURE_H
