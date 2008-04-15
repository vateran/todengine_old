//-----------------------------------------------------------------------------
inline void Property::setName(const name_t* name)
{
    name_ = name;
}


//-----------------------------------------------------------------------------
inline const Name& Property::getName() const
{
    return name_;
}


//-----------------------------------------------------------------------------
inline type_id Property::getType() const
{
    return TypeId<void>::id();
}
