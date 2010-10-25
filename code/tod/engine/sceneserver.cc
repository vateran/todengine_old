#include "tod/engine/sceneserver.h"

#include "tod/core/assert.h"
#include "tod/core/exception.h"
#include "tod/engine/renderer.h"
#include "tod/engine/renderpath.h"
#include "tod/engine/rpsection.h"
#include "tod/engine/rppass.h"
#include "tod/engine/scenecontext.h"
#include "tod/engine/scenenode.h"
#include "tod/engine/abstractshadernode.h"
#include "tod/engine/abstractcameranode.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(SceneServer, Node);

//-----------------------------------------------------------------------------
SceneServer::SceneServer():
stackDepth_(0)
{
    groupStack_.resize(1024);
}


//-----------------------------------------------------------------------------
SceneServer::~SceneServer()
{
    // empty
}


//-----------------------------------------------------------------------------
void SceneServer::beginScene()
{
    groups_.clear();
    stackDepth_ = 0;
}


//-----------------------------------------------------------------------------
void SceneServer::attach(SceneContext* scene_context)
{
    tod_assert(scene_context);
    SceneNode* root = scene_context->getRootSceneNode();
    tod_assert(root);

    // let root node hierarchy attach itself to scene
    root->attach(this, scene_context);
}


//-----------------------------------------------------------------------------
void SceneServer::endScene()
{
    tod_assert(0 == stackDepth_);
}


//-----------------------------------------------------------------------------
void SceneServer::renderScene(CameraNode* override_camera)
{
    RenderPath::instance()->validate();

    // split nodes into shapes and cameras etc..
    splitNodes();

    // this must happen after make sure node resources are loaded
    // because the reflection/refraction camera stuff depends on it
    validateNodeResources();

    // sort ShapeNodes for optimal rendering
    sortNodes();

    // render cameras
    renderCameraScenes(override_camera);
}


//-----------------------------------------------------------------------------
void SceneServer::presentScene(int windowid_override)
{
    Renderer::instance()->presentScene(windowid_override);
}


//-----------------------------------------------------------------------------
void SceneServer::beginGroup
(SceneNode* scene_node, SceneContext* scene_context)
{
    tod_assert(scene_node);
    tod_assert(scene_context);

    // initialize new group node
    Group group;
    group.sceneNode_ = scene_node;
    group.sceneContext_ = scene_context;
    bool isTopLevel = false;
    if (0 == stackDepth_)
    {
        isTopLevel = true;
        group.parentGroupId_ = -1;
    }
    else
    {
        group.parentGroupId_ = groupStack_[stackDepth_ - 1];
    }
    
    // add group node
    groups_.push_back(group);

    // push pointer to group onto hierarchy stack
    groupStack_[stackDepth_] = static_cast<int>(groups_.size() - 1);
    ++stackDepth_;

    // immediately call the SceneNode's renderTransform() method
    if (isTopLevel)
    {
        scene_node->renderTransform
        (
            this, scene_context, scene_context->getTransform()
        );
    }
    else
    {
        scene_node->renderTransform
        (
            this, scene_context,
            groups_[group.parentGroupId_].modelTransform_
        );
    }
}


//-----------------------------------------------------------------------------
void SceneServer::endGroup()
{
    tod_assert(stackDepth_ > 0);
    --stackDepth_;
}


//-----------------------------------------------------------------------------
void SceneServer::splitNodes()
{
    cameras_.clear();
    shapes_.clear();

    int num_groups = static_cast<int>(groups_.size());
    for (int i = 0; i < num_groups; ++i)
    {
        Group& group = groups_[i];
        SceneNode* scene_node = group.sceneNode_;
        tod_assert(scene_node);

        if (scene_node->hasGeometry())
        {
            AbstractShaderNode* shader_node =
                dynamic_cast<AbstractShaderNode*>(scene_node);
            if (0 == shader_node)
                continue;
            if (shader_node->getRpPassIndex() > -1)
                shapes_[shader_node->getRpPassIndex()].push_back(i);
        }
        else if (scene_node->hasCamera())
        {
            cameras_.push_back(i);
        }
    }
}


//-----------------------------------------------------------------------------
void SceneServer::validateNodeResources()
{
    // validate ShapeNodes
    for (int i = 0; i < 64; ++i)
    {
        Shapes::array_type& shape = shapes_[i];
        for (size_t shape_index = 0; shape_index < shape.size(); ++shape_index)
        {
            SceneNode* scene_node = groups_[shape[shape_index]].sceneNode_;
            if (scene_node->isResourceInvalid())
                scene_node->loadResource();
        }
    }

    // validate CameraNodes
    for (size_t i = 0; i < cameras_.size(); ++i)
    {
        SceneNode* scene_node = groups_[cameras_[i]].sceneNode_;
        if (scene_node->isResourceInvalid())
            scene_node->loadResource();
    }
}


//-----------------------------------------------------------------------------
void SceneServer::sortNodes()
{

}


//-----------------------------------------------------------------------------
void SceneServer::renderCameraScenes(CameraNode* camera_override)
{
    if (camera_override)
    {

    }
    else
    {
        for (size_t i = 0; i < cameras_.size(); ++i)
        {
            Group& group = groups_[cameras_[i]];
            AbstractCameraNode* camera_node =
                dynamic_cast<AbstractCameraNode*>(group.sceneNode_);
            tod_assert(camera_node);
            camera_node->applyShader(this);
            camera_node->renderCamera(this);
            camera_node->renderShader(this, group.sceneContext_);            
            doRenderPath(camera_node->getRenderPathSection());
        }
    }
}


//-----------------------------------------------------------------------------
void SceneServer::doRenderPath(const String& section_name)
{
    // find RpSection
    RpSection* section = RenderPath::instance()->findSection(section_name);
    if (0 == section)
    {
        TOD_THROW_EXCEPTION(0,
            String("findSection(%s failed)", section_name.c_str()));
        return;
    }

    // iteration RpPasses of RpSection
    for (uint32_t pass_index = 0; pass_index < section->getNumPass();
         ++pass_index)
    {
        RpPass* pass = section->getPass(pass_index);
        if (0 == pass)
            continue;
        pass->begin();

        Shapes::array_type shapes = shapes_[pass_index];
        for (size_t shape_index = 0; shape_index < shapes.size(); ++shape_index)
        {
            Group& group = groups_[shapes[shape_index]];
            SceneNode* scene_node = group.sceneNode_;

            scene_node->applyShader(this);
            scene_node->applyGeometry(this);
            
            Renderer::instance()->setTransform(
                TRANSFORM_WORLD, group.modelTransform_);
            scene_node->renderShader(this, group.sceneContext_);



            scene_node->renderGeometry(this, group.sceneContext_);


            /*Shader* shader = Renderer::instance()->getShader();
            uint32_t pass;
            shader->begin(pass);
            for (uint32_t i = 0; i < pass; ++i)
            {
                shader->beginPass(i);
                scene_node->renderGeometry(this, group.sceneContext_);
                shader->endPass();
            }    
            shader->end();*/
        }

        pass->end();
    }
}


//-----------------------------------------------------------------------------
void SceneServer::pick(int x, int y, int w, int h)
{
    // find RpSection
    RpSection* section = RenderPath::instance()->findSection("default");

    // iteration RpPasses of RpSection
    for (uint32_t pass_index = 0; pass_index < section->getNumPass();
        ++pass_index)
    {
        Shapes::array_type shapes = shapes_[pass_index];
        for (size_t shape_index = 0; shape_index < shapes.size(); ++shape_index)
        {
            Group& group = groups_[shapes[shape_index]];
            SceneNode* scene_node = group.sceneNode_;
            scene_node->pick(x, y, w, h);            
        }
    }
}


//-----------------------------------------------------------------------------
void SceneServer::setModelTransform(const Matrix44& m)
{
    groups_.back().modelTransform_ = m;
}
