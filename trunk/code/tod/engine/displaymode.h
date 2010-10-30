#ifndef TOD_ENGINE_GRAPHICS_CORE_DISPLAYMODE_H
#define TOD_ENGINE_GRAPHICS_CORE_DISPLAYMODE_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::DisplayMode
    @brief 
*/

#include "tod/core/primitivetype.h"
#include "tod/core/string.h"
#include "tod/engine/format.h"

namespace tod
{
namespace engine
{
    class DisplayMode : public String
    {
    public:
        DisplayMode();
        DisplayMode(const char_t* mode);
        DisplayMode(const String& mode);

        void set(const char_t* mode);

        const String getTitle() const;
        int getWidth() const;
        int getHeight() const;
        Format getFormat() const;
        Format getDepthAndStencilFormat() const;
        bool isFullscreen() const;
        bool isWindowed() const;
        bool isVSync() const;

        DisplayMode& operator = (const char_t* mode);
        
    public:
        String title_;
        int width_;
        int height_;
        Format format_;
        Format depthAndStencilFormat_;
        int sbuf_;
        int zbuf_;
        bool fullscreen_;
        bool vsync_;
    };
}
}

#endif //TOD_ENGINE_GRAPHICS_CORE_DISPLAYMODE_H
