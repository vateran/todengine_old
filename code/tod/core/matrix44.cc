#include "tod/core/matrix44.h"

#include <d3dx9.h>
#include "tod/core/quaternion.h"

using namespace tod::core;

//-----------------------------------------------------------------------------
Matrix44::Matrix44():
m11_(1), m12_(0), m13_(0), m14_(0),
m21_(0), m22_(1), m23_(0), m24_(0),
m31_(0), m32_(0), m33_(1), m34_(0),
m41_(0), m42_(0), m43_(0), m44_(1)
{
    // empty
}

//-----------------------------------------------------------------------------
void Matrix44::setTranslation(const Vector3& translation)
{
    m41_ = translation.x_;
    m42_ = translation.y_;
    m43_ = translation.z_;
}


//-----------------------------------------------------------------------------
void Matrix44::setTranslation(real_t x, real_t y, real_t z)
{
    m41_ = x;
    m42_ = y;
    m43_ = z;
}


//-----------------------------------------------------------------------------
void Matrix44::setEulerRotationAxis(const Vector3& rotation, real_t angle)
{
    D3DXMatrixRotationAxis(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXVECTOR3*>(&rotation), angle);
}


//-----------------------------------------------------------------------------
void Matrix44::setEulerRotationAxis(real_t x, real_t y, real_t z, real_t angle)
{
    D3DXMatrixRotationAxis(
        reinterpret_cast<D3DXMATRIX*>(this),
        &D3DXVECTOR3(x, y, z), angle);
}


//-----------------------------------------------------------------------------
void Matrix44::setRotation(const Quaternion& q)
{
    D3DXMatrixRotationQuaternion(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXQUATERNION*>(&q));
}


//-----------------------------------------------------------------------------
void Matrix44::setScaling(const Vector3& scaling)
{
    D3DXMatrixScaling(
        reinterpret_cast<D3DXMATRIX*>(this),
        scaling.x_, scaling.y_, scaling.z_);
}


//-----------------------------------------------------------------------------
void Matrix44::setScaling(real_t x, real_t y, real_t z)
{
    D3DXMatrixScaling(reinterpret_cast<D3DXMATRIX*>(this), x, y, z);
}


//-----------------------------------------------------------------------------
void Matrix44::translate(const Vector3& translation)
{
    m41_ += translation.x_;
    m42_ += translation.y_;
    m43_ += translation.z_;
}


//-----------------------------------------------------------------------------
void Matrix44::translate(real_t x, real_t y, real_t z)
{
    m41_ += x;
    m42_ += y;
    m43_ += z;
}


//-----------------------------------------------------------------------------
void Matrix44::scale(const Vector3& scaling)
{
    for (int i = 0; i < 4; ++i)
    {
        m_[i][0] *= scaling.x_;
        m_[i][1] *= scaling.y_;
        m_[i][2] *= scaling.z_;
    }
}


//-----------------------------------------------------------------------------
void Matrix44::scale(real_t x, real_t y, real_t z)
{
    for (int i = 0; i < 4; ++i)
    {
        m_[i][0] *= x;
        m_[i][1] *= y;
        m_[i][2] *= z;
    }
}


//-----------------------------------------------------------------------------
void Matrix44::rotateX(real_t x)
{

}


//-----------------------------------------------------------------------------
void Matrix44::rotateY(real_t y)
{

}


//-----------------------------------------------------------------------------
void Matrix44::rotateZ(real_t z)
{

}


//-----------------------------------------------------------------------------
void Matrix44::eulerRotate(real_t x, real_t y, real_t z)
{
    Matrix44 r;
    D3DXMatrixRotationYawPitchRoll(
        reinterpret_cast<D3DXMATRIX*>(&r), x, y, z);
    *this *= r;
}


//-----------------------------------------------------------------------------
void Matrix44::rotateQuaternion(const Quaternion& q)
{

}


//-----------------------------------------------------------------------------
real_t Matrix44::getTx() const
{
    return m41_;
}


//-----------------------------------------------------------------------------
real_t Matrix44::getTy() const
{
    return m42_;
}


//-----------------------------------------------------------------------------
real_t Matrix44::getTz() const
{
    return m43_;
}


//-----------------------------------------------------------------------------
void Matrix44::identity()
{
    D3DXMatrixIdentity(reinterpret_cast<D3DXMATRIX*>(this));
}


//-----------------------------------------------------------------------------
bool Matrix44::isIdentity() const
{
    return D3DXMatrixIsIdentity(
        reinterpret_cast<CONST D3DXMATRIX*>(this))?true:false;
}


//-----------------------------------------------------------------------------
void Matrix44::inverse(real_t* determinant)
{
    D3DXMatrixInverse(
        reinterpret_cast<D3DXMATRIX*>(this),
        determinant,
        reinterpret_cast<CONST D3DXMATRIX*>(this));
}


//-----------------------------------------------------------------------------
void Matrix44::transpose()
{
    D3DXMatrixTranspose(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(this));
}


//-----------------------------------------------------------------------------
float Matrix44::determinant()
{
    return D3DXMatrixDeterminant(reinterpret_cast<CONST D3DXMATRIX*>(this));
}


//-----------------------------------------------------------------------------
void Matrix44::multiply(const Matrix44& m)
{
    D3DXMatrixMultiply(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(&m));
}


//-----------------------------------------------------------------------------
void Matrix44::multiplyTranspose(const Matrix44& m)
{
    D3DXMatrixMultiplyTranspose(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(&m));
}


//-----------------------------------------------------------------------------
void Matrix44::lookAtLH
(const Vector3& eye, const Vector3& at, const Vector3& up)
{
    D3DXMatrixLookAtLH(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<const D3DXVECTOR3*>(&eye),
        reinterpret_cast<const D3DXVECTOR3*>(&at),
        reinterpret_cast<const D3DXVECTOR3*>(&up));
}


//-----------------------------------------------------------------------------
void Matrix44::lookAtRH
(const Vector3& eye, const Vector3& at, const Vector3& up)
{
    D3DXMatrixLookAtRH(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<const D3DXVECTOR3*>(&eye),
        reinterpret_cast<const D3DXVECTOR3*>(&at),
        reinterpret_cast<const D3DXVECTOR3*>(&up));
}


//-----------------------------------------------------------------------------
void Matrix44::orthogonalLH(real_t w, real_t h, real_t z_near, real_t z_far)
{
    D3DXMatrixOrthoLH(reinterpret_cast<D3DXMATRIX*>(this), w, h, z_near, z_far);
}


//-----------------------------------------------------------------------------
void Matrix44::orthogonalRH(real_t w, real_t h, real_t z_near, real_t z_far)
{
    D3DXMatrixOrthoRH(reinterpret_cast<D3DXMATRIX*>(this), w, h, z_near, z_far);
}


//-----------------------------------------------------------------------------
void Matrix44::orthogonalOffsetCenterLH
(real_t l, real_t t, real_t r, real_t b, real_t z_near, real_t z_far)
{
    D3DXMatrixOrthoOffCenterLH(
        reinterpret_cast<D3DXMATRIX*>(this), l, r, b, t, z_near, z_far);
}


//-----------------------------------------------------------------------------
void Matrix44::orthogonalOffsetCenterRH
(real_t l, real_t t, real_t r, real_t b, real_t z_near, real_t z_far)
{
    D3DXMatrixOrthoOffCenterRH(
        reinterpret_cast<D3DXMATRIX*>(this), l, r, b, t, z_near, z_far);
}


//-----------------------------------------------------------------------------
void Matrix44::perspectiveFovLH
(real_t fov_y, real_t aspect_ratio, real_t z_near, real_t z_far)
{
    D3DXMatrixPerspectiveFovLH(
        reinterpret_cast<D3DXMATRIX*>(this),
        fov_y, aspect_ratio, z_near, z_far);
}


//-----------------------------------------------------------------------------
void Matrix44::perspectiveFovRH
(real_t fov_y, real_t aspect_ratio, real_t z_near, real_t z_far)
{
    D3DXMatrixPerspectiveFovRH(
        reinterpret_cast<D3DXMATRIX*>(this),
        fov_y, aspect_ratio, z_near, z_far);
}


//-----------------------------------------------------------------------------
void Matrix44::perspectiveOffsetCenterLH
(real_t l, real_t t, real_t r, real_t b, real_t z_near, real_t z_far)
{
    D3DXMatrixPerspectiveOffCenterLH(
        reinterpret_cast<D3DXMATRIX*>(this), l, r, b, t, z_near, z_far);
}


//-----------------------------------------------------------------------------
void Matrix44::perspectiveOffsetCenterRH
(real_t l, real_t t, real_t r, real_t b, real_t z_near, real_t z_far)
{
    D3DXMatrixPerspectiveOffCenterRH(
        reinterpret_cast<D3DXMATRIX*>(this), l, r, b, t, z_near, z_far);
}


//-----------------------------------------------------------------------------
void Matrix44::reflect(const Plane& plane)
{
    D3DXMatrixReflect(
        reinterpret_cast<D3DXMATRIX*>(this), 
        reinterpret_cast<CONST D3DXPLANE*>(&plane));
}


//-----------------------------------------------------------------------------
void Matrix44::setRotateQuaternion(const Quaternion& quaternion)
{
    D3DXMatrixRotationQuaternion(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXQUATERNION*>(&quaternion));
}


//-----------------------------------------------------------------------------
void Matrix44::setRotateX(real_t x)
{
    D3DXMatrixRotationX(reinterpret_cast<D3DXMATRIX*>(this), x);
}


//-----------------------------------------------------------------------------
void Matrix44::setRotateY(real_t y)
{
    D3DXMatrixRotationY(reinterpret_cast<D3DXMATRIX*>(this), y);
}


//---------------------------------------------------------------------------
void Matrix44::setRotateZ(real_t z)
{
    D3DXMatrixRotationZ(reinterpret_cast<D3DXMATRIX*>(this), z);
}


//-----------------------------------------------------------------------------
void Matrix44::setRotateYawRollPitch(real_t yaw, real_t roll, real_t pitch)
{
    D3DXMatrixRotationYawPitchRoll(
        reinterpret_cast<D3DXMATRIX*>(this), yaw, pitch, roll);
}


//-----------------------------------------------------------------------------
Matrix44 Matrix44::operator * (const Matrix44& lhs) const
{
    Matrix44 m(*this);
    D3DXMatrixMultiply(
        reinterpret_cast<D3DXMATRIX*>(&m),
        reinterpret_cast<CONST D3DXMATRIX*>(&m),
        reinterpret_cast<CONST D3DXMATRIX*>(&lhs));
    return m;
}


//-----------------------------------------------------------------------------
void Matrix44::operator *= (const Matrix44& lhs)
{
    D3DXMatrixMultiply(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(&lhs));
}
