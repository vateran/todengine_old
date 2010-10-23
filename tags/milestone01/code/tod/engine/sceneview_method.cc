#include "tod/engine/sceneview.h"

#include "tod/core/methodbinder.h"
#include "tod/engine/sceneserver.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
static void SceneView_v_render_v(SceneView* self, Parameter* param)
{
    self->render(SceneServer::instance());
}


//-----------------------------------------------------------------------------
static void SceneView_v_setSceneRoot_o(SceneView* self, Parameter* param)
{
    self->setSceneRoot(param->in()->get<Node*>(0).get());
}


//-----------------------------------------------------------------------------
static void SceneView_o_getSceneRoot_v(SceneView* self, Parameter* param)
{
    param->out()->get<Node*>(0) = self->getSceneRoot();
}


//-----------------------------------------------------------------------------
static void SceneView_v_setCamera_o(SceneView* self, Parameter* param)
{
    self->setCamera(
        dynamic_cast<CameraNode*>
            (param->in()->get<Node*>(0).get()));
}


//-----------------------------------------------------------------------------
static void SceneView_o_getCamera_v(SceneView* self, Parameter* param)
{
    param->out()->get<Node*>(0) = self->getCamera();
}


//-----------------------------------------------------------------------------
static void SceneView_v_setWindowId_i(SceneView* self, Parameter* param)
{
    self->setWindowId(param->in()->get<int>(0));
}


//-----------------------------------------------------------------------------
static void SceneView_i_getWindowId_v(SceneView* self, Parameter* param)
{
    param->out()->get<int>(0) = self->getWindowId();
}


//-----------------------------------------------------------------------------
static void SceneView_v_pick_iiii(SceneView* self, Parameter* param)
{
    self->pick(
        param->in()->get<int>(0),
        param->in()->get<int>(1),
        param->in()->get<int>(2),
        param->in()->get<int>(3));
}


//-----------------------------------------------------------------------------
static void SceneView_v_moveForward_f(SceneView* self, Parameter* param)
{
    self->moveForward(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
static void SceneView_v_moveLeft_f(SceneView* self, Parameter* param)
{
    self->moveSideward(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
static void SceneView_v_viewEulerRotationX_f(SceneView* self, Parameter* param)
{
    self->viewEulerRotationX(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
static void SceneView_v_viewEulerRotationY_f(SceneView* self, Parameter* param)
{
    self->viewEulerRotationY(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
static void SceneView_v_viewEulerRotationZ_f(SceneView* self, Parameter* param)
{
    self->viewEulerRotationZ(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
void SceneView::bindMethod()
{
    BIND_METHOD(v_render_v, SceneView_v_render_v);
    BIND_METHOD(v_setSceneRoot_o, SceneView_v_setSceneRoot_o);
    BIND_METHOD(o_getSceneRoot_v, SceneView_o_getSceneRoot_v);
    BIND_METHOD(v_setCamera_o, SceneView_v_setCamera_o);
    BIND_METHOD(o_getCamera_v, SceneView_o_getCamera_v);
    BIND_METHOD(v_setWindowId_i, SceneView_v_setWindowId_i);
    BIND_METHOD(i_getWindowId_v, SceneView_i_getWindowId_v);
    BIND_METHOD(v_pick_iiii, SceneView_v_pick_iiii);
    BIND_METHOD(v_moveForward_f, SceneView_v_moveForward_f);
    BIND_METHOD(v_moveSideward_f, SceneView_v_moveLeft_f);
    BIND_METHOD(v_viewEulerRotationX_f, SceneView_v_viewEulerRotationX_f);
    BIND_METHOD(v_viewEulerRotationY_f, SceneView_v_viewEulerRotationY_f);
    BIND_METHOD(v_viewEulerRotationZ_f, SceneView_v_viewEulerRotationZ_f);
}
