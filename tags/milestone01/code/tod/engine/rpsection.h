#ifndef TOD_ENGINE_GRAPHICS_RENDERPATH_RPSECTION_H
#define TOD_ENGINE_GRAPHICS_RENDERPATH_RPSECTION_H
/**
    @ingroup TodEngineGraphicsRenderPath
    @class tod::engine::RpSection
    @brief 
*/

#include <vector>
#include "tod/engine/rpbase.h"

namespace tod
{
namespace engine
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
        RpPass* getPass(index_t index);
        uint32_t getNumPass() const;

        RpPasses::iterator firstPass();
        RpPasses::iterator lastPass();
        RpPasses::const_iterator firstPass() const;
        RpPasses::const_iterator lastPass() const;

        override void onAddNode(Node* node);
        override void onRemoveNode(Node* node);

    private:
        RpPasses passes_;

    };
}
}

#endif // TOD_ENGINE_GRAPHICS_RENDERPATH_RPSECTION_H
