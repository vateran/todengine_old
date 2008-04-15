//-----------------------------------------------------------------------------
inline void Transform44::setTranslation(const Vector3& translation)
{
    translation_ = translation;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setTranslation(real_t x, real_t y, real_t z)
{
    translation_.x_ = x;
    translation_.y_ = y;
    translation_.z_ = z;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setEulerRotation(const Vector3& rotation)
{
    eulerRotation_ = rotation;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_USEEULER] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setEulerRotation(real_t x, real_t y, real_t z)
{
    eulerRotation_.x_ = x;
    eulerRotation_.y_ = y;
    eulerRotation_.z_ = z;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_USEEULER] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setRotation(const Quaternion& q)
{
    quaternion_ = q;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_USEEULER] = false;
}


//-----------------------------------------------------------------------------
inline void Transform44::setScaling(const Vector3& scaling)
{
    scaling_ = scaling;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setScaling(real_t x, real_t y, real_t z)
{
    scaling_.x_ = x;
    scaling_.y_ = y;
    scaling_.z_ = z;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::translate(const Vector3& translation)
{
    translation_ += translation;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::translate(real_t x, real_t y, real_t z)
{
    translation_.x_ += x;
    translation_.y_ += y;
    translation_.z_ += z;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::rotate(const Vector3& r)
{
    eulerRotation_ += r;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_USEEULER] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::rotate(real_t x, real_t y, real_t z)
{
    eulerRotation_.x_ += x;
    eulerRotation_.y_ += y;
    eulerRotation_.z_ += z;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_USEEULER] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::scale(const Vector3& scaling)
{
    scaling_ += scaling;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::scale(real_t x, real_t y, real_t z)
{
    scaling_.x_ += x;
    scaling_.y_ += y;
    scaling_.z_ += z;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::translateX(real_t x)
{
    translation_.x_ += x;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::translateY(real_t y)
{
    translation_.y_ += y;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::translateZ(real_t z)
{
    translation_.z_ += z;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::eulerRotateX(real_t x)
{
    eulerRotation_.x_ += x;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_USEEULER] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::eulerRotateY(real_t y)
{
    eulerRotation_.y_ += y;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_USEEULER] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::eulerRotateZ(real_t z)
{
    eulerRotation_.z_ += z;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_USEEULER] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setRotatePivot(const Vector3& p)
{
    rotatePivot_ = p;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_HASROTATEPIVOT] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setRotatePivot(real_t x, real_t y, real_t z)
{
    rotatePivot_.x_ = x;
    rotatePivot_.y_ = y;
    rotatePivot_.z_ = z;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_HASROTATEPIVOT] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setRotatePivotTranlsation(const Vector3& p)
{
    rotatePivotTranslation_ = p;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setRotatePivotTranlsation(real_t x, real_t y, real_t z)
{
    rotatePivotTranslation_.x_ = x;
    rotatePivotTranslation_.y_ = y;
    rotatePivotTranslation_.z_ = z;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setScalePivot(const Vector3& p)
{
    scalePivot_ = p;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_HASSCALEPIVOT] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setScalePivot(real_t x, real_t y, real_t z)
{
    scalePivot_.x_ = x;
    scalePivot_.y_ = y;
    scalePivot_.z_ = z;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_HASSCALEPIVOT] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setMatrix(const Matrix44& m)
{
    matrix_ = m;
    flags_[FLAG_DIRTY] = false;
}


//-----------------------------------------------------------------------------
inline void Transform44::setTx(real_t x)
{
    translation_.x_ = x;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setTy(real_t y)
{
    translation_.y_ = y;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setTz(real_t z)
{
    translation_.z_ = z;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setEulerRx(real_t x)
{
    eulerRotation_.x_ = x;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_USEEULER] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setEulerRy(real_t y)
{
    eulerRotation_.y_ = y;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_USEEULER] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setEulerRz(real_t z)
{
    eulerRotation_.z_ = z;
    flags_[FLAG_DIRTY] = true;
    flags_[FLAG_USEEULER] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setSx(real_t x)
{
    scaling_.x_ = x;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setSy(real_t y)
{
    scaling_.y_ = y;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline void Transform44::setSz(real_t z)
{
    scaling_.z_ = z;
    flags_[FLAG_DIRTY] = true;
}


//-----------------------------------------------------------------------------
inline const Vector3& Transform44::getTranslation() const
{
    return translation_;
}


//-----------------------------------------------------------------------------
inline const Vector3& Transform44::getEulerRotation() const
{
    return eulerRotation_;
}


//-----------------------------------------------------------------------------
inline const Quaternion& Transform44::getRotation() const
{
    return quaternion_;
}


//-----------------------------------------------------------------------------
inline const Vector3& Transform44::getScaling() const
{
    return scaling_;
}


//-----------------------------------------------------------------------------
inline const Vector3& Transform44::getRotatePivot() const
{
    return rotatePivot_;
}


//-----------------------------------------------------------------------------
inline const Vector3& Transform44::getRotatePivotTranlsation() const
{
    return rotatePivotTranslation_;
}


//-----------------------------------------------------------------------------
inline const Vector3& Transform44::getScalePivot() const
{
    return scalePivot_;
}


//-----------------------------------------------------------------------------
inline real_t Transform44::getTx() const
{
    return translation_.x_;
}


//-----------------------------------------------------------------------------
inline real_t Transform44::getTy() const
{
    return translation_.y_;
}


//-----------------------------------------------------------------------------
inline real_t Transform44::getTz() const
{
    return translation_.z_;
}


//-----------------------------------------------------------------------------
inline real_t Transform44::getEulerRx() const
{
    return eulerRotation_.x_;
}


//-----------------------------------------------------------------------------
inline real_t Transform44::getEulerRy() const
{
    return eulerRotation_.y_;
}


//-----------------------------------------------------------------------------
inline real_t Transform44::getEulerRz() const
{
    return eulerRotation_.z_;
}


//-----------------------------------------------------------------------------
inline real_t Transform44::getSx() const
{
    return scaling_.x_;
}


//-----------------------------------------------------------------------------
inline real_t Transform44::getSy() const
{
    return scaling_.y_;
}


//-----------------------------------------------------------------------------
inline real_t Transform44::getSz() const
{
    return scaling_.z_;
}


//-----------------------------------------------------------------------------
inline void Transform44::setLock(bool b)
{
    flags_[FLAG_LOCKED] = b;
}


//-----------------------------------------------------------------------------
inline bool Transform44::isLock() const
{
    return flags_[FLAG_LOCKED];
}

