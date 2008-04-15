#ifndef TOD_ENGINE_GRAPHICS_RENDERPATH_RPSECTION_H
#define TOD_ENGINE_GRAPHICS_RENDERPATH_RPSECTION_H
/**
    @ingroup TodEngineGraphicsRenderPath
    @class tod::engine::graphics::RpSection
    @brief 
*/

#include <vector>
#include "tod/engine/rpbase.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class RpPass;
    class RpSection : public RpBase
    {
    public:
        typedef std::vector<RpPass*> RpPasses;

    public:
        RpSection();
        virtual~RpSection();
        DECLARE_CLASS(RpSection, RpBase);

        void addPass(RpPass* pass);
        void removePass(RpPass* pass);
        RpPass* getPass(core::index_t index);
        core::uint32_t getNumPass() const;

        RpPasses::iterator firstPass();
        RpPasses::iterator lastPass();
        RpPasses::const_iterator firstPass() const;
        RpPasses::const_iterator lastPass() const;

        override void onAddNode(core::Node* node);
        override void onRemoveNode(core::Node* node);

    private:
        RpPasses passes_;

    };
}
}
}

#endif // TOD_ENGINE_GRAPHICS_RENDERPATH_RPSECTION_H
