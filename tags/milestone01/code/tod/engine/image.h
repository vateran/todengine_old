#ifndef TOD_ENGINE_GRAPHICS_CORE_IMAGE_H
#define TOD_ENGINE_GRAPHICS_CORE_IMAGE_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::Image
    @brief 
*/

#include "IL/il.h"
#include "tod/core/uri.h"
#include "tod/core/color.h"

namespace tod
{
namespace engine
{
    class Image
    {
    public:
        Image();
        Image(const Uri& uri);
        virtual~Image();

        bool create(int width, int height);
        void destroy();
        bool preload();

        int width() const;
        int height() const;

        void setUri(const Uri& uri);
        const Uri& getUri() const;

        Color getPixel(int x, int y) const;

    private:
        Uri uri_;

        ILuint id_;
        
        int width_;
        int height_;
        Color* data_;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_TEXTURE_H
