#include "tod/engine/timeserver.h"

#include "tod/core/methodbinder.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
static void TimeServer_v_pause_v(TimeServer* self, Parameter* param)
{
    self->pause();
}


//-----------------------------------------------------------------------------
static void TimeServer_b_isPause_v(TimeServer* self, Parameter* param)
{
    param->out()->get<bool>(0) = self->isPause();
}


//-----------------------------------------------------------------------------
static void TimeServer_v_resume_v(TimeServer* self, Parameter* param)
{
    self->resume();
}


//-----------------------------------------------------------------------------
static void TimeServer_v_step_f(TimeServer* self, Parameter* param)
{
    self->step(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
static void TimeServer_v_scale_f(TimeServer* self, Parameter* param)
{
    self->scale(param->in()->get<float>(0));
}


//-----------------------------------------------------------------------------
static void TimeServer_f_getScale_v(TimeServer* self, Parameter* param)
{
    param->out()->get<float>(0) = self->getScale();
}


//-----------------------------------------------------------------------------
static void TimeServer_d_getTime_v(TimeServer* self, Parameter* param)
{
    param->out()->get<double>(0) = self->getTime();
}


//-----------------------------------------------------------------------------
void TimeServer::bindMethod()
{
    BIND_METHOD(v_pause_v, TimeServer_v_pause_v);
    BIND_METHOD(b_isPause_v, TimeServer_b_isPause_v);
    BIND_METHOD(v_resume_v, TimeServer_v_resume_v);
    BIND_METHOD(v_step_f, TimeServer_v_step_f);
    BIND_METHOD(v_scale_f, TimeServer_v_scale_f);
    BIND_METHOD(f_getScale_v, TimeServer_f_getScale_v);
    BIND_METHOD(d_getTime_v, TimeServer_d_getTime_v);
}
