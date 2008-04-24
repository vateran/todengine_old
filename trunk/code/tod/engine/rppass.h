#ifndef TOD_ENGINE_GRAPHICS_RENDERPATH_RPPASS_H
#define TOD_ENGINE_GRAPHICS_RENDERPATH_RPPASS_H
/**
    @ingroup TodEngineGraphicsRenderPath
    @class tod::engine::graphics::RpPass
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
namespace graphics
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

        override core::uint32_t begin();
        override void end();

        void setClearColor(const core::Color& color);
        void setClearDepthValue(float value);
        void setClearStencilValue(core::uint32_t value);
        void setDrawQuad(bool enable);
        bool isDrawQuad() const;
        const core::Color& getClearColor() const;
        float clearDepthValue() const;
        core::uint32_t clearStencilValue() const;

        void setClearTarget(bool enable);
        bool isClearTarget() const;
        void setClearDepth(bool enable);
        bool isClearDepth() const;
        void setClearStencil(bool enable);
        bool isClearStencil() const;

        override void onAddNode(core::Node* node);
        override void onRemoveNode(core::Node* node);

        static void bindProperty();

    private:
        void draw_quad();

    private:
        core::Ref<RpRenderTarget> renderTarget_;
        core::Color clearColor_;
        float clearDepthValue_;
        core::uint32_t clearStencilValue_;
        std::bitset<FLAG_MAX> flags_;
    };
}
}
}

#endif // TOD_ENGINE_GRAPHICS_RENDERPATH_RPPASS_H
