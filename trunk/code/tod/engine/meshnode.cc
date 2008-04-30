#include "tod/engine/meshnode.h"

#include "tod/core/simplepropertybinder.h"
#include "tod/engine/mesh.h"
#include "tod/engine/renderer.h"

using namespace tod::core;
using namespace tod::engine::graphics;

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
#include "tod/engine/shader.h"
void MeshNode::renderGeometry
(SceneServer* scene_server, SceneContext* scene_context)
{
    if (mesh_.invalid())
        return;
    Shader* shader = Renderer::instance()->getShader();
    uint32_t pass;
    shader->begin(pass);
    for (uint32_t i = 0; i < pass; ++i)
    {
        shader->beginPass(i);
        mesh_->draw();
        shader->endPass();
    }    
    shader->end();
}


//-----------------------------------------------------------------------------
bool MeshNode::loadResource()
{
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
