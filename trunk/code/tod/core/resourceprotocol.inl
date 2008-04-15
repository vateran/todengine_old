//-----------------------------------------------------------------------------
inline void ResourceProtocol::setBasePath(const path_t* path)
{
    basePath_ = path;
}


//-----------------------------------------------------------------------------
inline const String& ResourceProtocol::getBasePath() const
{
    return basePath_;
}