//-----------------------------------------------------------------------------
template <typename T>
void Variables::add(const T& v)
{
    static SimpleVariable<T> variable;
    variable = v;
    array_.push_back(variable.clone());
}


//-----------------------------------------------------------------------------
template <typename T>
SimpleVariable<T>& Variables::get(index_t index)
{
    return static_cast<SimpleVariable<T>&>(*array_.at(index));
}


//-----------------------------------------------------------------------------
inline Variable* Variables::get(index_t index)
{
    return array_.at(index);
}


//-----------------------------------------------------------------------------
inline void Variables::setForceList(bool enable)
{
    forceList_ = enable;
}


//-----------------------------------------------------------------------------
inline bool Variables::isForceList() const
{
    return forceList_;
}
