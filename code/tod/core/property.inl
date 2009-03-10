//-----------------------------------------------------------------------------
inline void Property::setName(const char_t* name)
{
    name_ = name;
}


//-----------------------------------------------------------------------------
inline const String& Property::getName() const
{
    return name_;
}


//-----------------------------------------------------------------------------
inline type_id Property::getType() const
{
    return TypeId<void>::id();
}
