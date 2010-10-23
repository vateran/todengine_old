#ifndef TOD_ENGINE_NODE_XFILENODE_H
#define TOD_ENGINE_NODE_XFILENODE_H
/**
    @ingroup TodEngine
    @class tod::engine::XFileNode
    @brief 
*/

#include <d3dx9.h>
#include "tod/engine/shapenode.h"
#include "tod/engine/resourceref.h"

namespace tod
{
namespace engine
{
    class XFileNode : public ShapeNode
    {
    public:
        XFileNode();
        virtual~XFileNode();
        DECLARE_CLASS(XFileNode, ShapeNode);

        override void applyGeometry(SceneServer* scene_server);
        override void renderGeometry(
            SceneServer* scene_server,
            SceneContext* scene_context);
        override bool loadResource();
        override void unloadResource();
        override bool hasGeometry() const;

        void setMeshUri(const Uri& uri);
        const Uri& getMeshUri() const;

        void setInt(int a)
        {
            aa = a;
        }
        int getInt() const
        {
            return aa;
        }
        int aa;

        static void bindProperty();
        static void bindMethod();

    private:
        Uri uri_;
    };
}
}

#endif // TOD_ENGINE_NODE_XFILENODE_H
