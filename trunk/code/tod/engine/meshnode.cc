#include "tod/engine/meshnode.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/engine/mesh.h"
#include "tod/engine/renderer.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(MeshNode, ShaderNode);

//-----------------------------------------------------------------------------
MeshNode::MeshNode()
{

}


//-----------------------------------------------------------------------------
MeshNode::~MeshNode()
{

}


//-----------------------------------------------------------------------------
void MeshNode::applyGeometry(SceneServer* scene_server)
{

}



//-----------------------------------------------------------------------------
void MeshNode::renderGeometry
(SceneServer* scene_server, SceneContext* scene_context)
{
    if (mesh_.invalid())
        return;   
    mesh_->draw();
}


//-----------------------------------------------------------------------------
bool MeshNode::loadResource()
{
    if (getMeshUri().empty())
        return false;

    super::loadResource();
    mesh_ = Renderer::instance()->newMesh(getMeshUri());
    mesh_->preload(true, true, true);
    return true;
}

//-----------------------------------------------------------------------------
void MeshNode::unloadResource()
{
    mesh_.release();

    super::unloadResource();
}


//-----------------------------------------------------------------------------
bool MeshNode::hasGeometry() const
{
    return true;
}


//-----------------------------------------------------------------------------
void MeshNode::setMeshUri(const Uri& uri)
{
    uri_ = uri;
    unloadResource();
}


//-----------------------------------------------------------------------------
const Uri& MeshNode::getMeshUri() const
{
    return uri_;
}


//-----------------------------------------------------------------------------
void MeshNode::bindProperty()
{
    BIND_PROPERTY(const Uri&, mesh_uri, &setMeshUri, &getMeshUri);
}
