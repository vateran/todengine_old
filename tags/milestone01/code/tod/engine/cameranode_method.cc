#include "tod/engine/cameranode.h"

#include "tod/core/methodbinder.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
static void CameraNode_v_moveForward_f(CameraNode* self, Parameter* param)
{
    self->moveForward(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
static void CameraNode_v_moveSideward_f(CameraNode* self, Parameter* param)
{
    self->moveSideward(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
static void CameraNode_v_eulerRotateX_f(CameraNode* self, Parameter* param)
{
    self->eulerRotateX(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
static void CameraNode_v_eulerRotateY_f(CameraNode* self, Parameter* param)
{
    self->eulerRotateY(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
static void CameraNode_v_eulerRotateZ_f(CameraNode* self, Parameter* param)
{
    self->eulerRotateZ(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
static void CameraNode_v_onChangedWindowSize_ii
(CameraNode* self, Parameter* param)
{
    self->onChangedWindowSize(
        param->in()->get<int>(0),
        param->in()->get<int>(1));
}


//-----------------------------------------------------------------------------
void CameraNode::bindMethod()
{   
    BIND_METHOD(v_moveForward_f, CameraNode_v_moveForward_f);
    BIND_METHOD(v_moveSideward_f, CameraNode_v_moveSideward_f);
    BIND_METHOD(v_eulerRotateX_f, CameraNode_v_eulerRotateX_f);
    BIND_METHOD(v_eulerRotateY_f, CameraNode_v_eulerRotateY_f);
    BIND_METHOD(v_eulerRotateZ_f, CameraNode_v_eulerRotateZ_f);
    BIND_METHOD(v_onChangedWindowSize_ii, CameraNode_v_onChangedWindowSize_ii);
}
