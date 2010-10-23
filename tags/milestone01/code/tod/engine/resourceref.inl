//-----------------------------------------------------------------------------
template <typename T>
ResourceRef<T>::ResourceRef():
ptr_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
template <typename T>
ResourceRef<T>::ResourceRef(const type& ref):
ptr_(0)
{
    initialize(ref.ptr_);
}


//-----------------------------------------------------------------------------
template <typename T>
ResourceRef<T>::ResourceRef(Resource* r):
ptr_(0)
{
    initialize(r);
}


//-----------------------------------------------------------------------------
template <typename T>
ResourceRef<T>::~ResourceRef()
{
    release();
}


//-----------------------------------------------------------------------------
template <typename T>
void ResourceRef<T>::initialize(Resource* r)
{
    if (resource_)
        resource_->release();
    resource_ = r;
    if (resource_)
        resource_->addRef();
}


//-----------------------------------------------------------------------------
template <typename T>
void ResourceRef<T>::release()
{
    if (resource_)
        resource_->release();
    ptr_ = 0;
}


//-----------------------------------------------------------------------------
template <typename T>
bool ResourceRef<T>::valid() const
{
    return ptr_ ? true:false;
}


//-----------------------------------------------------------------------------
template <typename T>
bool ResourceRef<T>::invalid() const
{
    return !valid();
}


//-----------------------------------------------------------------------------
template <typename T>
template <typename DERIVED>
DERIVED ResourceRef<T>::get()
{
    return dynamic_cast<DERIVED>(ptr_);
}


//-----------------------------------------------------------------------------
template <typename T>
template <typename DERIVED>
ResourceRef<T>::operator DERIVED ()
{
    return get<DERIVED>();
}


//-----------------------------------------------------------------------------
template <typename T>
ResourceRef<T>::operator T* ()
{
    return ptr_;
}


//-----------------------------------------------------------------------------
template <typename T>
ResourceRef<T>::operator const T* () const
{
    return ptr_;
}


//-----------------------------------------------------------------------------
template <typename T>
T* ResourceRef<T>::operator -> ()
{
    return ptr_;
}


//-----------------------------------------------------------------------------
template <typename T>
const T* ResourceRef<T>::operator -> () const
{
    return ptr_;
}


//-----------------------------------------------------------------------------
template <typename T>
typename ResourceRef<T>::type& ResourceRef<T>::operator = (T* r)
{
    initialize(r);
    return *this;
}


//-----------------------------------------------------------------------------
template <typename T>
bool ResourceRef<T>::operator == (const type& rhs) const
{
    return ptr_ == rhs.ptr_;
}


//-----------------------------------------------------------------------------
template <typename T>
bool ResourceRef<T>::operator != (const type& rhs) const
{
    return !(*this == rhs);
}


//-----------------------------------------------------------------------------
template <typename T>
bool ResourceRef<T>::operator < (const type& rhs) const
{
    return ptr_ < rhs.ptr_;
}


//-----------------------------------------------------------------------------
template <typename T>
bool ResourceRef<T>::operator > (const type& rhs) const
{
    return ptr_ > rhs.ptr_;
}
