//-----------------------------------------------------------------------------
inline void CameraNode::setFOV(float fov)
{
    fov_ = fov;
}


//-----------------------------------------------------------------------------
inline float CameraNode::getFOV() const
{
    return fov_;
}


//-----------------------------------------------------------------------------
inline void CameraNode::setAspectRatio(float aspect)
{
    aspectRatio_ = aspect;
}


//-----------------------------------------------------------------------------
inline float CameraNode::getAspectRatio() const
{
    return aspectRatio_;
}


//-----------------------------------------------------------------------------
inline void CameraNode::setNear(float z)
{
    near_ = z;
}


//-----------------------------------------------------------------------------
inline float CameraNode::getNear() const
{
    return near_;
}


//-----------------------------------------------------------------------------
inline void CameraNode::setFar(float z)
{
    far_ = z;
}


//-----------------------------------------------------------------------------
inline float CameraNode::getFar() const
{
    return far_;
}
