#ifndef TOD_ENGINE_GRAPHICS_SCENE_SCENESERVER_H
#define TOD_ENGINE_GRAPHICS_SCENE_SCENESERVER_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::SceneServer
    @brief 
*/

#include <vector>
#include "tod/core/matrix44.h"
#include "tod/core/node.h"
#include "tod/core/singleton3.h"

namespace tod
{
namespace engine
{
    class SceneNode;
    class SceneContext;
    class SceneServer :
        public Node,
        public Singleton3<SceneServer>
    {
    public:
        SceneServer();
        virtual~SceneServer();
        DECLARE_CLASS(SceneServer, Node);

        void beginScene();
        void attach(SceneContext* scene_context);
        void endScene();
        void renderScene();
        void presentScene(int windowid_override=0);

        void beginGroup(SceneNode* scene_node, SceneContext* scene_context);
        void endGroup();

        void splitNodes();
        void validateNodeResources();
        void sortNodes();
        void renderCameraScenes();
        void doRenderPath(const String& section_name);

        void pick(int x, int y, int w, int h);

        /**
            @brief Set CURRENT Group's model transform.
            This method will be called by SceneNode's renderTransform() method.
        */
        void setModelTransform(const Matrix44& m);

    private:
        struct Group
        {
            int parentGroupId_;
            SceneNode* sceneNode_;
            SceneContext* sceneContext_;
            Matrix44 modelTransform_;
        };

        template <typename T, uint32_t SIZE>
        class Bucket
        {
        public:
            typedef std::vector<T> array_type;

        public:
            void clear()
            {
                for (uint32_t i = 0; i < SIZE; ++i)
                    array_[i].clear();
            }
            array_type& operator [] (uint32_t index)
            {
                return array_[index];
            }

        private:
            array_type array_[SIZE];
        };
        typedef Bucket<int, 64> Shapes;

    private:
        std::vector<Group> groups_;
        std::vector<int> cameras_;
        Shapes shapes_;

        std::vector<int> groupStack_;
        int stackDepth_;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_SCENE_SCENESERVER_H
