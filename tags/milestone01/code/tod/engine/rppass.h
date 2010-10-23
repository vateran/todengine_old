#ifndef TOD_ENGINE_GRAPHICS_RENDERPATH_RPPASS_H
#define TOD_ENGINE_GRAPHICS_RENDERPATH_RPPASS_H
/**
    @ingroup TodEngineGraphicsRenderPath
    @class tod::engine::RpPass
    @brief 
*/

#include <bitset>
#include "tod/core/ref.h"
#include "tod/core/color.h"
#include "tod/engine/rpbase.h"

namespace tod
{
namespace engine
{
    class RpRenderTarget;
    class RpPass : public RpBase
    {
    public:
        enum Flag
        {
            FLAG_CLEARTARGET,
            FLAG_CLEARDEPTH,
            FLAG_CLEARSTENCIL,
            FLAG_DRAWQUAD,

            FLAG_MAX,
        };

    public:
        RpPass();
        virtual~RpPass();
        DECLARE_CLASS(RpPass, RpBase);

        override void validate();

        override uint32_t begin();
        override void end();

        void setClearColor(const Color& color);
        void setClearDepthValue(float value);
        void setClearStencilValue(uint32_t value);
        void setDrawQuad(bool enable);
        bool isDrawQuad() const;
        const Color& getClearColor() const;
        float clearDepthValue() const;
        uint32_t clearStencilValue() const;

        void setClearTarget(bool enable);
        bool isClearTarget() const;
        void setClearDepth(bool enable);
        bool isClearDepth() const;
        void setClearStencil(bool enable);
        bool isClearStencil() const;

        override void onAddNode(Node* node);
        override void onRemoveNode(Node* node);

        static void bindProperty();

    private:
        void draw_quad();

    private:
        Ref<RpRenderTarget> renderTarget_;
        Color clearColor_;
        float clearDepthValue_;
        uint32_t clearStencilValue_;
        std::bitset<FLAG_MAX> flags_;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_RENDERPATH_RPPASS_H
