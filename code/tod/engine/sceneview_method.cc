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
static void SceneView_v_setSceneRootPath_s(SceneView* self, Parameter* param)
{
    self->setSceneRootPath(param->in()->get<String>(0).get());
}


//-----------------------------------------------------------------------------
static void SceneView_s_getSceneRootPath_v(SceneView* self, Parameter* param)
{
    param->out()->get<String>(0) = self->getSceneRootPath();
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
    self->moveLeft(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
static void SceneView_v_moveRight_f(SceneView* self, Parameter* param)
{
    self->moveRight(param->in()->get<float>(0));
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
    BIND_METHOD(v_setSceneRootPath_s, SceneView_v_setSceneRootPath_s);
    BIND_METHOD(s_getSceneRootPath_v, SceneView_s_getSceneRootPath_v);
    BIND_METHOD(v_setWindowId_i, SceneView_v_setWindowId_i);
    BIND_METHOD(i_getWindowId_v, SceneView_i_getWindowId_v);
    BIND_METHOD(v_pick_iiii, SceneView_v_pick_iiii);
    BIND_METHOD(v_moveForward_f, SceneView_v_moveForward_f);
    BIND_METHOD(v_moveLeft_f, SceneView_v_moveLeft_f);
    BIND_METHOD(v_moveRight_f, SceneView_v_moveRight_f);
    BIND_METHOD(v_viewEulerRotationX_f, SceneView_v_viewEulerRotationX_f);
    BIND_METHOD(v_viewEulerRotationY_f, SceneView_v_viewEulerRotationY_f);
    BIND_METHOD(v_viewEulerRotationZ_f, SceneView_v_viewEulerRotationZ_f);
}
