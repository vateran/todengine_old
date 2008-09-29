//-----------------------------------------------------------------------------
template <typename T>
SimpleVariable<T>* ShaderParams::addShaderParam(const Name& name)
{   
    typedef SimpleVariable<T> VariableType;
    Params::iterator f = params_.find(name);
    VariableType* v = 0;
    if (params_.end() == f)
    {
        v = new VariableType();
        params_.insert(Params::value_type(name, v));
    }
    else
        v = dynamic_cast<VariableType*>(f->second);
    return v;
}
