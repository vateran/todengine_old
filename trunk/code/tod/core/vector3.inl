//-----------------------------------------------------------------------------
inline Vector3::Vector3():
x_(0), y_(0), z_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
inline Vector3::Vector3(float x, float y, float z):
x_(x), y_(y), z_(z)
{
    // empty
}


//-----------------------------------------------------------------------------
inline void Vector3::clear()
{
    x_ = y_ = z_ = 0;
}


//-----------------------------------------------------------------------------
inline void Vector3::set(float x, float y, float z)
{
    x_ = x;
    y_ = y;
    z_ = z;
}


//-----------------------------------------------------------------------------
inline void Vector3::set(int i, float value)
{
    a_[i] = value;
}


//-----------------------------------------------------------------------------
inline bool Vector3::isEqual(const Vector3& v, float tol) const
{
    for (int i = 0; i < 3; ++i)
        if (a_[i] - tol >= v.a_[i] || v.a_[i] <= a_[i] + tol)
            return false;
    return true;
}


//-----------------------------------------------------------------------------
inline float Vector3::length() const
{
    return size();
}


//-----------------------------------------------------------------------------
inline void Vector3::normalize()
{
    float l = length();
    if (l == 0)
        return;
    x_ /= l;
    y_ /= l;
    z_ /= l;
}


//-----------------------------------------------------------------------------
inline float Vector3::dotprod(const Vector3& v) const
{
    return (x_ * v.x_ + y_ * v.y_ + z_ * v.z_);
}


//-----------------------------------------------------------------------------
inline Vector3 Vector3::operator - ()
{
    return Vector3(-x_, -y_, -z_);
}


//-----------------------------------------------------------------------------
inline const Vector3& Vector3::operator += (const Vector3& rhs)
{
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
    return *this;
}


//-----------------------------------------------------------------------------
inline const Vector3& Vector3::operator -= (const Vector3& rhs)
{
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
    return *this;
}


//-----------------------------------------------------------------------------
inline const Vector3& Vector3::operator *= (float v)
{
    x_ *= v;
    y_ *= v;
    z_ *= v;
    return *this;
}


//-----------------------------------------------------------------------------
inline Vector3 Vector3::operator + (const Vector3& v) const
{   
    return Vector3(x_ + v.x_, y_ + v.y_, z_ + v.z_);
}


//-----------------------------------------------------------------------------
inline Vector3 Vector3::operator - (const Vector3& v) const
{
    return Vector3(x_ - v.x_, y_ - v.y_, z_ - v.z_);
}


//-----------------------------------------------------------------------------
inline Vector3 Vector3::operator * (float value) const
{
    return Vector3(x_ * value, y_ * value, z_ * value);
}


//-----------------------------------------------------------------------------
inline const float& Vector3::operator [] (int i) const
{
    return a_[i];
}


//-----------------------------------------------------------------------------
inline float& Vector3::operator [] (int i)
{
    return a_[i];
}
