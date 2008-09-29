#ifndef TOD_ENGINE_GRAPHICS_SCENE_NODE_SCENENODE_H
#define TOD_ENGINE_GRAPHICS_SCENE_NODE_SCENENODE_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::SceneNode

    @brief The SceneNode is the base class of all objects which can be attached
    to a scene managed by SceneServer class. A SceneNode object may provide
    transform, geometry, shader and volume information.
*/

#include "tod/core/matrix44.h"
#include "tod/core/node.h"

namespace tod
{
namespace engine
{
    class SceneServer;
    class SceneContext;
    class SceneNode : public Node
    {
    public:
        SceneNode();
        virtual~SceneNode();
        DECLARE_CLASS(SceneNode, Node);

        /**
            @brief Attach the object to the scene if necessary. This method
            either called by the SceneServer, or by another SceneNode object
            at scene construction time. If the SceneNode needs rendering it
            should call appropriate SceneServer method to attach itself to
            the scene.
            The method will be invoked recursively on all child and depend
            nodes of the SceneNode object.

            @param scene_server     pointer to the SceneServer object.
            @param scene_context    pointer to the SceneContext object.
        */
        virtual void attach(
            SceneServer* scene_server,
            SceneContext* scene_context);

        /**
            @brief This method make sure that all resources needed by this
            object are loaded. The method does NOTE recurse into its children.
            Subclasses should expect that the loadResource() method can be
            called on them although some or all of there resources are valid.
            Thus, a check should exist, whether the resource really needs to
            be reloaded.
        */
        virtual bool loadResource();
        /**
            @brief This method make sure that all resources used by this
            object are unloaded. The method does NOT recurse into its children.
        */
        virtual void unloadResource();
        
        /**
            @brief Render the node's transformation. This should be implemented
            by a subclass. The method will only be called by SceneServer if
            the method isProvide(TRANSFORM) returns true.
        */
        virtual void renderTransform(
            SceneServer* scene_server,
            SceneContext* scene_context,
            const Matrix44& parent_matrix);
        
        /**
            @brief Perform per-instance rendering of the shader. This method
            will be called once at the beginning of rendering different
            instances of the same node. Use this method to setup shader
            attributes which are constant for a complete instance set.
        */
        virtual void applyShader(SceneServer* scene_server);
        /**
            @brief Perform pre-instance-rendering of the shader. This method
            will be called after applyShader() once for each rendered instance.
            Use this method to set shader attributes which vary from instance
            to instance.
        */
        virtual void renderShader(
            SceneServer* scene_server,
            SceneContext* scene_context);
        /**
            @brief Perform pre-instance rendering of geometry. This method will
            be called once at the beginning of rendering different instances
            of the same SceneNode. Use this method to setup geometry attributes
            which are constant for a complete instance set.
        */
        virtual void applyGeometry(SceneServer* scene_server);
        /**
            @brief Perform per-instance-rendering of geometry. This method will
            be called after applyGeometry() once for each instance of the node.
        */
        virtual void renderGeometry(
            SceneServer* scene_server,
            SceneContext* scene_context);

        /**
            @brief setup View transform and Projection transform.
        */
        virtual void renderCamera(SceneServer* scene_server);

        virtual bool hasTransform() const;
        virtual bool hasShader() const;
        virtual bool hasGeometry() const;
        virtual bool hasCamera() const;

        bool isResourceValid() const { return resourceValid_; }
        bool isResourceInvalid() const { return !resourceValid_; }

        virtual void pick(int x, int y, int w, int h) {}

    protected:
        bool resourceValid_;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_NODE_SCENENODE_H
