//-----------------------------------------------------------------------------
inline const Name& Module::getName() const
{
    return name_;
}


//-----------------------------------------------------------------------------
inline Module::Types::iterator Module::firstType()
{
    return types_.begin();
}


//-----------------------------------------------------------------------------
inline Module::Types::iterator Module::lastType()
{
    return types_.end();
}


//-----------------------------------------------------------------------------
inline Module::Types::const_iterator Module::firstType() const
{
    return types_.begin();
}


//-----------------------------------------------------------------------------
inline Module::Types::const_iterator Module::lastType() const
{
    return types_.end();
}
