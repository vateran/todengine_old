//-----------------------------------------------------------------------------
template <typename T>
bool ResourceHolder<T>::empty() const
{
    return namedResources_.empty() && unnamedResources_.empty();
}


//-----------------------------------------------------------------------------
template <typename T>
size_t ResourceHolder<T>::size() const
{
    return namedResources_.size() + unnamedResources_.size();
}


//-----------------------------------------------------------------------------
template <typename T>
void ResourceHolder<T>::clear()
{
    namedResources_.clear();
    unnamedResources_.clear();
}


//-----------------------------------------------------------------------------
template <typename T>
void ResourceHolder<T>::add(Resource* r)
{
    tod_assert(r);
    if (r->getUri().empty())
        unnamedResources_.push_back(r);
    else
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
