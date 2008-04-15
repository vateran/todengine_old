#ifndef TOD_ENGINE_GRAPHICS_RENDERPATH_RENDERSEQUENCE_H
#define TOD_ENGINE_GRAPHICS_RENDERPATH_RENDERSEQUENCE_H
/**
    @ingroup TodEngineGraphicsRenderPath
    @class tod::engine::graphics::RpSequence
    @brief 
*/

#include "tod/engine/rpbase.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class RpSequence : public RpBase
    {
    public:
        RpSequence();
        virtual~RpSequence();
        DECLARE_CLASS(RpSequence, RpBase);

    private:
    };
}
}
}

#endif // TOD_ENGINE_GRAPHICS_RENDERPATH_RENDERSEQUENCE_H
