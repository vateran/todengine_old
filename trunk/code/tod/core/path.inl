//-----------------------------------------------------------------------------
inline bool Path::isAbsolute() const
{
    if (empty())
        return false;
    return at(0) == '/';
}

//-----------------------------------------------------------------------------
inline bool Path::isRelative() const
{
    return !isAbsolute();
}


//-----------------------------------------------------------------------------
inline Path::iterator Path::begin()
{
    tokenizer_.assign(String::begin(), String::end(), s_seperator);
    return tokenizer_.begin();
}


//-----------------------------------------------------------------------------
inline Path::iterator Path::end()
{
    return tokenizer_.end();
}


//-----------------------------------------------------------------------------
inline Path::const_iterator Path::begin() const
{
    tokenizer_.assign(String::begin(), String::end(), s_seperator);
    return tokenizer_.begin();
}


//-----------------------------------------------------------------------------
inline Path::const_iterator Path::end() const
{
    return tokenizer_.end();
}
