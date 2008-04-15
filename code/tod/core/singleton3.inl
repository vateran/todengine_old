//-----------------------------------------------------------------------------
template <typename T>
Singleton3<T>::Singleton3()
{
    // empty
}


//-----------------------------------------------------------------------------
template <typename T>
Singleton3<T>::~Singleton3()
{
    // empty
}


//-----------------------------------------------------------------------------
template <typename T>
void Singleton3<T>::setSingletonPath(const Path& path)
{
    s_path = path;
}


//-----------------------------------------------------------------------------
template <typename T>
T* Singleton3<T>::instance()
{
    tod_assert(s_path.size());
    if (s_instance)
        return s_instance;
    s_instance = dynamic_cast<T*>(
        Kernel::instance()->create(T::TYPE.getName().c_str(), s_path));
    return s_instance;
}


//-----------------------------------------------------------------------------
template <typename T>
bool Singleton3<T>::isInitialized()
{
    return s_instance ? true:false;
}


//-----------------------------------------------------------------------------
template <typename T>
T* Singleton3<T>::s_instance;


//-----------------------------------------------------------------------------
template <typename T>
Path Singleton3<T>::s_path;
