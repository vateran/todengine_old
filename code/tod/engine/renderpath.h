#ifndef TOD_ENGINE_GRAPHICS_RENDERPATH_RENDERPATH_H
#define TOD_ENGINE_GRAPHICS_RENDERPATH_RENDERPATH_H
/**
    @ingroup TodEngineGraphicsRenderPath
    @class tod::engine::graphics::RenderPath
    @brief A RenderPath is an abstract description of HOW a scene should be
    rendered. This includes things like what shaders to apply and in which
    order, what render targets to render to, highlevel differences between
    DX9 and DX10 scene rendering.
*/

#include "tod/core/node.h"
#include "tod/core/singleton3.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class RpSection;
    class RpShader;
    class RenderPath :
        public core::Node,
        public core::Singleton3<RenderPath>
    {
    public:
        RenderPath();
        virtual~RenderPath();
        DECLARE_CLASS(RenderPath, core::Node);

        RpSection* findSection(const core::Name& name);

        void validate();
    };
}
}
}

#endif // TOD_ENGINE_GRAPHICS_RENDERPATH_RENDERPATH_H
