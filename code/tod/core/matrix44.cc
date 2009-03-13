#include "tod/core/matrix44.h"

#ifdef __WIN32__
#include <d3dx9.h>
#endif

using namespace tod;

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
#ifdef __WIN32__
    D3DXMatrixRotationAxis(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXVECTOR3*>(&rotation), angle);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::setEulerRotationAxis(real_t x, real_t y, real_t z, real_t angle)
{
#ifdef __WIN32__
    D3DXMatrixRotationAxis(
        reinterpret_cast<D3DXMATRIX*>(this),
        &D3DXVECTOR3(x, y, z), angle);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::setRotation(const Quaternion& q)
{
#ifdef __WIN32__
    D3DXMatrixRotationQuaternion(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXQUATERNION*>(&q));
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::setScaling(const Vector3& scaling)
{
#ifdef __WIN32__
    D3DXMatrixScaling(
        reinterpret_cast<D3DXMATRIX*>(this),
        scaling.x_, scaling.y_, scaling.z_);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::setScaling(real_t x, real_t y, real_t z)
{
#ifdef __WIN32__
    D3DXMatrixScaling(reinterpret_cast<D3DXMATRIX*>(this), x, y, z);
#else
#endif
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
#ifdef __WIN32__
    D3DXMatrixRotationYawPitchRoll(
        reinterpret_cast<D3DXMATRIX*>(&r), x, y, z);
#else
#endif
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
Vector3 Matrix44::getTranslation() const
{
    return Vector3(m41_, m42_, m43_);
}


//-----------------------------------------------------------------------------
void Matrix44::identity()
{
#ifdef __WIN32__
    D3DXMatrixIdentity(reinterpret_cast<D3DXMATRIX*>(this));
#else
#endif
}


//-----------------------------------------------------------------------------
bool Matrix44::isIdentity() const
{
#ifdef __WIN32__
    return D3DXMatrixIsIdentity(
        reinterpret_cast<CONST D3DXMATRIX*>(this))?true:false;
#else
    return false;
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::inverse(real_t* determinant)
{
#ifdef __WIN32__
    D3DXMatrixInverse(
        reinterpret_cast<D3DXMATRIX*>(this),
        determinant,
        reinterpret_cast<CONST D3DXMATRIX*>(this));
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::transpose()
{
#ifdef __WIN32__
    D3DXMatrixTranspose(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(this));
#else
#endif
}


//-----------------------------------------------------------------------------
float Matrix44::determinant()
{
#ifdef __WIN32__
    return D3DXMatrixDeterminant(reinterpret_cast<CONST D3DXMATRIX*>(this));
#else
    return 0;
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::multiply(const Matrix44& m)
{
#ifdef __WIN32__
    D3DXMatrixMultiply(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(&m));
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::multiplyTranspose(const Matrix44& m)
{
#ifdef __WIN32__
    D3DXMatrixMultiplyTranspose(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(&m));
#else
#endif
}


//-----------------------------------------------------------------------------
Vector3 Matrix44::multiplyDivW(const Vector3& v) const
{
    Vector4 v4(v.x_, v.y_, v.z_, 1.0f);
    v4 = *this * v4;
    return Vector3(v4.x_ / v4.w_, v4.y_ / v4.w_, v4.z_ / v4.w_);
}


//-----------------------------------------------------------------------------
void Matrix44::lookAtLH
(const Vector3& eye, const Vector3& at, const Vector3& up)
{
#ifdef __WIN32__
    D3DXMatrixLookAtLH(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<const D3DXVECTOR3*>(&eye),
        reinterpret_cast<const D3DXVECTOR3*>(&at),
        reinterpret_cast<const D3DXVECTOR3*>(&up));
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::lookAtRH
(const Vector3& eye, const Vector3& at, const Vector3& up)
{
#ifdef __WIN32__
    D3DXMatrixLookAtRH(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<const D3DXVECTOR3*>(&eye),
        reinterpret_cast<const D3DXVECTOR3*>(&at),
        reinterpret_cast<const D3DXVECTOR3*>(&up));
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::orthogonalLH(real_t w, real_t h, real_t z_near, real_t z_far)
{
#ifdef __WIN32__
    D3DXMatrixOrthoLH(reinterpret_cast<D3DXMATRIX*>(this), w, h, z_near, z_far);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::orthogonalRH(real_t w, real_t h, real_t z_near, real_t z_far)
{
#ifdef __WIN32__
    D3DXMatrixOrthoRH(reinterpret_cast<D3DXMATRIX*>(this), w, h, z_near, z_far);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::orthogonalOffsetCenterLH
(real_t l, real_t t, real_t r, real_t b, real_t z_near, real_t z_far)
{
#ifdef __WIN32__
    D3DXMatrixOrthoOffCenterLH(
        reinterpret_cast<D3DXMATRIX*>(this), l, r, b, t, z_near, z_far);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::orthogonalOffsetCenterRH
(real_t l, real_t t, real_t r, real_t b, real_t z_near, real_t z_far)
{
#ifdef __WIN32__
    D3DXMatrixOrthoOffCenterRH(
        reinterpret_cast<D3DXMATRIX*>(this), l, r, b, t, z_near, z_far);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::perspectiveFovLH
(real_t fov_y, real_t aspect_ratio, real_t z_near, real_t z_far)
{
#ifdef __WIN32__
    D3DXMatrixPerspectiveFovLH(
        reinterpret_cast<D3DXMATRIX*>(this),
        fov_y, aspect_ratio, z_near, z_far);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::perspectiveFovRH
(real_t fov_y, real_t aspect_ratio, real_t z_near, real_t z_far)
{
#ifdef __WIN32__
    D3DXMatrixPerspectiveFovRH(
        reinterpret_cast<D3DXMATRIX*>(this),
        fov_y, aspect_ratio, z_near, z_far);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::perspectiveOffsetCenterLH
(real_t l, real_t t, real_t r, real_t b, real_t z_near, real_t z_far)
{
#ifdef __WIN32__
    D3DXMatrixPerspectiveOffCenterLH(
        reinterpret_cast<D3DXMATRIX*>(this), l, r, b, t, z_near, z_far);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::perspectiveOffsetCenterRH
(real_t l, real_t t, real_t r, real_t b, real_t z_near, real_t z_far)
{
#ifdef __WIN32__
    D3DXMatrixPerspectiveOffCenterRH(
        reinterpret_cast<D3DXMATRIX*>(this), l, r, b, t, z_near, z_far);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::reflect(const Plane& plane)
{
#ifdef __WIN32__
    D3DXMatrixReflect(
        reinterpret_cast<D3DXMATRIX*>(this), 
        reinterpret_cast<CONST D3DXPLANE*>(&plane));
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::setRotateAxis(const Vector3& axis, real_t angle)
{
#ifdef __WIN32__
    D3DXMatrixRotationAxis(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXVECTOR3*>(&axis),
        angle);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::setRotateQuaternion(const Quaternion& quaternion)
{
#ifdef __WIN32__
    D3DXMatrixRotationQuaternion(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXQUATERNION*>(&quaternion));
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::setRotateX(real_t x)
{
#ifdef __WIN32__
    D3DXMatrixRotationX(reinterpret_cast<D3DXMATRIX*>(this), x);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::setRotateY(real_t y)
{
#ifdef __WIN32__
    D3DXMatrixRotationY(reinterpret_cast<D3DXMATRIX*>(this), y);
#else
#endif
}


//---------------------------------------------------------------------------
void Matrix44::setRotateZ(real_t z)
{
#ifdef __WIN32__
    D3DXMatrixRotationZ(reinterpret_cast<D3DXMATRIX*>(this), z);
#else
#endif
}


//-----------------------------------------------------------------------------
void Matrix44::setRotateYawRollPitch(real_t yaw, real_t roll, real_t pitch)
{
#ifdef __WIN32__
    D3DXMatrixRotationYawPitchRoll(
        reinterpret_cast<D3DXMATRIX*>(this), yaw, pitch, roll);
#else
#endif
}


//-----------------------------------------------------------------------------
Matrix44 Matrix44::operator * (const Matrix44& lhs) const
{
    Matrix44 m(*this);
#ifdef __WIN32__
    D3DXMatrixMultiply(
        reinterpret_cast<D3DXMATRIX*>(&m),
        reinterpret_cast<CONST D3DXMATRIX*>(&m),
        reinterpret_cast<CONST D3DXMATRIX*>(&lhs));
#else
#endif
    return m;
}


//-----------------------------------------------------------------------------
void Matrix44::operator *= (const Matrix44& lhs)
{
#ifdef __WIN32__
    D3DXMatrixMultiply(
        reinterpret_cast<D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(this),
        reinterpret_cast<CONST D3DXMATRIX*>(&lhs));
#else
#endif
}


//-----------------------------------------------------------------------------
Vector3 Matrix44::operator * (const Vector3& lhs) const
{
    Vector4 out;
#ifdef __WIN32__
    D3DXVec3Transform(
        reinterpret_cast<D3DXVECTOR4*>(&out),
        reinterpret_cast<CONST D3DXVECTOR3*>(&lhs),
        reinterpret_cast<CONST D3DXMATRIX*>(this));
#else
#endif
    return Vector3(out.x_, out.y_, out.z_);
}


//-----------------------------------------------------------------------------
Vector4 Matrix44::operator * (const Vector4& lhs) const
{
    Vector4 out;
#ifdef __WIN32__
    D3DXVec4Transform(
        reinterpret_cast<D3DXVECTOR4*>(&out),
        reinterpret_cast<CONST D3DXVECTOR4*>(&lhs),
        reinterpret_cast<CONST D3DXMATRIX*>(this));
#else
#endif
    return out;
}


//-----------------------------------------------------------------------------
Plane Matrix44::operator * (const Plane& lhs) const
{
    Plane out;
#ifdef __WIN32__
    D3DXPlaneTransform(
        reinterpret_cast<D3DXPLANE*>(&out),
        reinterpret_cast<CONST D3DXPLANE*>(&lhs),
        reinterpret_cast<CONST D3DXMATRIX*>(this));
#else
#endif
    return out;
}
