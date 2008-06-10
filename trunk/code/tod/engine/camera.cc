#include "tod/engine/camera.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
Camera::Camera()
{
    eye_.set(0, 0, 0);
    at_.set(0, 0, 1);
    up_.set(0, 1, 0);

    setView(eye_, at_, up_);
}


//-----------------------------------------------------------------------------
void Camera::setView
(const Vector3& eye, const Vector3& at, const Vector3& up)
{
    eye_ = eye;
    at_ = at;
    up_ = up;

    view_ = at_ - eye_;
    view_.normalize();

    cross_ = up_;
    cross_.cross(view_);

    viewMatrix_.lookAtLH(eye_, at_, up_);
    invViewMatrix_ = viewMatrix_;
    invViewMatrix_.inverse();
}


//-----------------------------------------------------------------------------
void Camera::setTranslation(const Vector3& v)
{
    Vector3 dv = v - eye_;
    eye_ = v;
    at_ += dv;
    setView(eye_, at_, up_);
}


//-----------------------------------------------------------------------------
void Camera::translateX(float dist)
{
    Vector3 move(cross_);
    move.normalize();
    move *= dist;
    setView(eye_ + move, at_ + move, up_);
}


//-----------------------------------------------------------------------------
void Camera::translateY(float dist)
{
    Vector3 move(up_);
    move.normalize();
    move *= dist;
    setView(eye_ + move, at_ + move, up_);
}


//-----------------------------------------------------------------------------
void Camera::translateZ(float dist)
{
    Vector3 move(view_);
    move.normalize();
    move *= dist;
    setView(eye_ + move, at_ + move, up_);
}


//-----------------------------------------------------------------------------
void Camera::rotateX(float angle)
{
    Matrix44 r;
    r.setRotateAxis(cross_, angle);

    view_.transformCoord(r);

    setView(eye_, view_ + eye_, up_);
}


//-----------------------------------------------------------------------------
void Camera::rotateY(float angle)
{
    Matrix44 r;
    r.setRotateAxis(up_, angle);

    view_.transformCoord(r);

    setView(eye_, view_ + eye_, up_);
}


//-----------------------------------------------------------------------------
void Camera::rotateZ(float angle)
{
    Matrix44 r;
    r.setRotateAxis(view_, angle);

    view_.transformCoord(r);

    setView(eye_, view_ + eye_, up_);
}


//-----------------------------------------------------------------------------
const Vector3& Camera::getEye() const
{
    return eye_;
}

//-----------------------------------------------------------------------------
const Matrix44& Camera::getMatrix()
{
    return viewMatrix_;
}
