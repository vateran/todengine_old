//-----------------------------------------------------------------------------
template <typename T>
core::SimpleVariable<T>* ShaderParams::addShaderParam(const core::Name& name)
{   
    typedef SimpleVariable<T> VariableType;
    VariableType* v = new VariableType();
    params_.insert(Params::value_type(name, v));
    return v;
}
