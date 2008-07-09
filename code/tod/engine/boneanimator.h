#ifndef TOD_ENGINE_GRAPHICS_CORE_BONEANIMATOR_H
#define TOD_ENGINE_GRAPHICS_CORE_BONEANIMATOR_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::BoneAnimator
    @brief 
*/

#include "tod/core/uri.h"
#include "tod/engine/resource.h"
#include "tod/engine/format.h"
#include "tod/engine/types.h"

namespace tod
{
namespace engine
{
    class SkinInfo
    {
    public:
    };

    class MeshContainer
    {
    public:

    private:
        Name name_;
        ResourceRef<Mesh> mesh_;
        std::vector<Material> materials_;
        uint32_t* adjacency_;
        SkinInfo* skinInfo_;
    };

    class Bone
    {
    public:

    private:
        Name name_;
        Matrix44 transformation_;
        MeshContainer meshContainer_;

        Bone* sibling_;
        Bone* firstChild_;
    };

    class BoneAnimator : public Resource
    {
    public:
        BoneAnimator(const Uri& uri):Resource(uri) {}
        virtual~BoneAnimator() {}

        virtual bool create()=0;
        virtual void destroy()=0;

        virtual bool draw()=0;

        virtual bool valid() const=0;
        bool invalid() const { return !valid(); }

        virtual void onLostDevice()=0;
        virtual void onRestoreDevice()=0;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_BONEANIMATOR_H

