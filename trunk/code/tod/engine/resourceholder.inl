//-----------------------------------------------------------------------------
template <typename T>
bool ResourceHolder<T>::empty() const
{
    return namedResources_.empty();
}


//-----------------------------------------------------------------------------
template <typename T>
size_t ResourceHolder<T>::size() const
{
    return namedResources_.size();
}


//-----------------------------------------------------------------------------
template <typename T>
void ResourceHolder<T>::clear()
{
    namedResources_.clear();
}


//-----------------------------------------------------------------------------
template <typename T>
void ResourceHolder<T>::add(Resource* r)
{
    tod_assert(r);
    if (r->getUri().empty())
        return;
    namedResources_.insert(NamedResources::value_type(r->getUri(), r));
}


//-----------------------------------------------------------------------------
template <typename T>
void ResourceHolder<T>::remove(const Uri& uri)
{
    namedResources_.erase(uri);
}


//-----------------------------------------------------------------------------
template <typename T>
T* ResourceHolder<T>::find(const Uri& uri)
{
    NamedResources::iterator find_iter = namedResources_.find(uri);
    if (namedResources_.end() == find_iter)
        return 0;
    return find_iter->second;
}


//-----------------------------------------------------------------------------
template <typename T>
typename ResourceHolder<T>::NamedResources::iterator
ResourceHolder<T>::begin()
{
    return namedResources_.begin();
}


//-----------------------------------------------------------------------------
template <typename T>
typename ResourceHolder<T>::NamedResources::iterator ResourceHolder<T>::end()
{
    return namedResources_.end();
}


//-----------------------------------------------------------------------------
template <typename T>
typename ResourceHolder<T>::NamedResources::const_iterator
ResourceHolder<T>::begin() const
{
    return namedResources_.begin();
}


//-----------------------------------------------------------------------------
template <typename T>
typename ResourceHolder<T>::NamedResources::const_iterator
ResourceHolder<T>::end() const
{
    return namedResources_.end();
}
