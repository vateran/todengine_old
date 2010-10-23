//-----------------------------------------------------------------------------
inline void TransformNode::setTranslation(const Vector3& t)
{
    transform_.setTranslation(t);
}


//-----------------------------------------------------------------------------
inline void TransformNode::setEulerRotation(const Vector3& r)
{
    transform_.setEulerRotation(r);
}


//-----------------------------------------------------------------------------
inline void TransformNode::setQuaternionRotation(const Quaternion& q)
{
    transform_.setRotation(q);
}


//-----------------------------------------------------------------------------
inline void TransformNode::setScaling(const Vector3& s)
{
    transform_.setScaling(s);
}


//-----------------------------------------------------------------------------
inline void TransformNode::setTransform(const Matrix44& m)
{
    transform_.setMatrix(m);
    transform_.setLock(true);
}


//-----------------------------------------------------------------------------
inline const Matrix44& TransformNode::getTransform() const
{
    return transform_.getMatrix();
}


//-----------------------------------------------------------------------------
inline void TransformNode::setEulerRx(float x)
{
    transform_.setEulerRx(x);
}


//-----------------------------------------------------------------------------
inline void TransformNode::setEulerRy(float y)
{
    transform_.setEulerRy(y);
}


//-----------------------------------------------------------------------------
inline void TransformNode::setEulerRz(float z)
{
    transform_.setEulerRz(z);
}


//-----------------------------------------------------------------------------
inline const Vector3& TransformNode::getTranslation() const
{
    return transform_.getTranslation();
}


//-----------------------------------------------------------------------------
inline const Vector3& TransformNode::getEulerRotation() const
{
    return transform_.getEulerRotation();
}


//-----------------------------------------------------------------------------
inline const Quaternion& TransformNode::getRotation() const
{
    return transform_.getRotation();
}


//-----------------------------------------------------------------------------
inline const Vector3& TransformNode::getScaling() const
{
    return transform_.getScaling();
}


//-----------------------------------------------------------------------------
inline float TransformNode::getEulerRx() const
{
    return transform_.getEulerRx();
}


//-----------------------------------------------------------------------------
inline float TransformNode::getEulerRy() const
{
    return transform_.getEulerRy();
}


//-----------------------------------------------------------------------------
inline float TransformNode::getEulerRz() const
{
    return transform_.getEulerRz();
}
