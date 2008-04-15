#ifndef TOD_ENGINE_GRAPHICS_CORE_CUBETEXTURE_H
#define TOD_ENGINE_GRAPHICS_CORE_CUBETEXTURE_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::graphics::CubeTexture
    @brief 
*/

#include "tod/engine/format.h"
#include "tod/engine/texture.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class CubeTexture : public Texture
    {
    public:
        CubeTexture(const core::Uri& uri);
        virtual~CubeTexture();
    };
}
}
}


#endif // TOD_ENGINE_GRAPHICS_CORE_CUBETEXTURE_H
