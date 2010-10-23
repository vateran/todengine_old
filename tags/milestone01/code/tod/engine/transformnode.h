#ifndef TOD_ENGINE_GRAPHICS_SCENE_NODE_TRANSFORMNODE_H
#define TOD_ENGINE_GRAPHICS_SCENE_NODE_TRANSFORMNODE_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::TransformNode
    @brief 
*/

#include <bitset>
#include "tod/core/transform44.h"
#include "tod/engine/scenenode.h"

namespace tod
{
namespace engine
{
    class TransformNode : public SceneNode
    {
    public:
        enum Flag
        {
            ACTIVE,
            VISIBLE,
            LOCKVIEWER,

            FLAG_MAX,
        };

    public:
        TransformNode();
        virtual~TransformNode();
        DECLARE_CLASS(TransformNode, SceneNode);

        override void attach(
            SceneServer* scene_server,
            SceneContext* scene_context);
        override void renderTransform(
            SceneServer* scene_server,
            SceneContext* scene_context,
            const Matrix44& parent_matrix);
        override bool hasTransform() const;

        bool checkFlags(const Flag& flag) const;
        bool isActive() const;
        bool isVisible() const;
        bool isLockViewer() const;

        void setActive(bool v);
        void setVisible(bool v);
        void setLockViewer(bool v);

        void setTranslation(const Vector3& t);
        void setEulerRotation(const Vector3& r);
        void setQuaternionRotation(const Quaternion& q);
        void setScaling(const Vector3& s);

        void setTx(float x);
        void setTy(float y);
        void setTz(float z);
        void setEulerRx(float x);
        void setEulerRy(float y);
        void setEulerRz(float z);
        void setSx(float x);
        void setSy(float y);
        void setSz(float z);

        void setTransform(const Matrix44& m);
        const Matrix44& getTransform() const;

        const Vector3& getTranslation() const;
        const Vector3& getEulerRotation() const;
        const Quaternion& getRotation() const;
        const Vector3& getScaling() const;

        float getTx() const;
        float getTy() const;
        float getTz() const;
        float getEulerRx() const;
        float getEulerRy() const;
        float getEulerRz() const;
        float getSx() const;
        float getSy() const;
        float getSz() const;

        static void bindProperty();

    private:
        std::bitset<FLAG_MAX> flags_;
        Transform44 transform_;
    };

#include "tod/engine/transformnode.inl"

}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_NODE_TRANSFORMNODE_H
