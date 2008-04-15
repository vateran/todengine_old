//-----------------------------------------------------------------------------
template <typename T>
bool ResourceHolder<T>::empty() const
{
    return resources_.empty();
}


//-----------------------------------------------------------------------------
template <typename T>
size_t ResourceHolder<T>::size() const
{
    return resources_.size();
}


//-----------------------------------------------------------------------------
template <typename T>
void ResourceHolder<T>::clear()
{
    resources_.clear();
}


//-----------------------------------------------------------------------------
template <typename T>
void ResourceHolder<T>::add(Resource* r)
{
    tod_assert(r);
    resources_.insert(Resources::value_type(r->getUri(), r));
}


//-----------------------------------------------------------------------------
template <typename T>
void ResourceHolder<T>::remove(const core::Uri& uri)
{
    resources_.erase(uri);
}


//-----------------------------------------------------------------------------
template <typename T>
T* ResourceHolder<T>::find(const core::Uri& uri)
{
    Resources::iterator find_iter = resources_.find(uri);
    if (resources_.end() == find_iter)
        return 0;
    return find_iter->second;
}
