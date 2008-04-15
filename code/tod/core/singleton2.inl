//-----------------------------------------------------------------------------
template <typename T>
Singleton2<T>::Singleton2()
{
    if (0 == s_instance)
        s_instance = dynamic_cast<T*>(this);
}


//-----------------------------------------------------------------------------
template <typename T>
Singleton2<T>::~Singleton2()
{
    if (s_instance == this)
        s_instance = 0;
}


//-----------------------------------------------------------------------------
template <typename T>
T* Singleton2<T>::instance()
{
    return s_instance;
}


//-----------------------------------------------------------------------------
template <typename T>
bool Singleton2<T>::isInitialized()
{
    return s_instance ? true:false;
}


//-----------------------------------------------------------------------------
template <typename T>
T* Singleton2<T>::s_instance;
