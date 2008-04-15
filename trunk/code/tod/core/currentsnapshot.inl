//-----------------------------------------------------------------------------
inline CurrentSnapShot::CurrentSnapShot():
line_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
inline CurrentSnapShot::CurrentSnapShot
(const char_t* type, const char_t* date,
 const char_t* time, const char_t* file_name,
 const char_t* func_sig, const char_t* func_name, int line,
 const char_t* expression)
{
    setSemantic(type, date, time, file_name,
        func_sig, func_name, line, expression);
}


//-----------------------------------------------------------------------------
inline void CurrentSnapShot::setSemantic
(const char_t* type, const char_t* date,
 const char_t* time, const char_t* file_name,
 const char_t* func_sig, const char_t* func_name, int line,
 const char_t* expression)
{
    type_ = type;
    date_ = date;
    time_ = time;
    fileName_ = file_name;
    functionSignature_ = func_sig;
    functionName_ = func_name;
    line_ = line;
    expression_ = expression;
}
