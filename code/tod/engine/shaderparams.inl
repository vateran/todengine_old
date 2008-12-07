//-----------------------------------------------------------------------------
template <typename T>
T* ShaderParams::getShaderParam(const Name& name)
{   
    Params::iterator f = params_.find(name);
    T* v = 0;
    if (params_.end() == f)
    {
        v = new T();
        params_.insert(Params::value_type(name, v));
    }
    else
        v = dynamic_cast<T*>(f->second);
    return v;
}
