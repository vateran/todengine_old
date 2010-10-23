#include "tod/engine/format.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
Format::Format():
value_(UNKNOWN)
{
    // empty
}


//-----------------------------------------------------------------------------
Format::Format(const char_t* str):
value_(UNKNOWN)
{
    fromString(str);
}


//-----------------------------------------------------------------------------
Format::Format(const String& str):
value_(UNKNOWN)
{
    fromString(str);
}


//-----------------------------------------------------------------------------
Format::Format(const Value& value):
value_(value)
{
    // empty
}


//-----------------------------------------------------------------------------
Format::Format(const int& value):
value_(static_cast<Value>(value))
{
    // empty
}


//-----------------------------------------------------------------------------
void Format::fromString(const char_t* str)
{
    value_ = from_string(str);
}


//-----------------------------------------------------------------------------
void Format::fromString(const String& str)
{
    value_ = from_string(str.c_str());
}


//-----------------------------------------------------------------------------
bool Format::operator == (const Format& lhs) const
{
    return value_ == lhs.value_;
}


//-----------------------------------------------------------------------------
bool Format::operator != (const Format& lhs) const
{
    return !(*this == lhs);
}


//-----------------------------------------------------------------------------
bool Format::operator == (const Value& lhs) const
{
    return value_ == lhs;
}


//-----------------------------------------------------------------------------
bool Format::operator != (const Value& lhs) const
{
    return !(*this == lhs);
}


//-----------------------------------------------------------------------------
Format::operator Format::Value () const
{
    return value_;
}


//-----------------------------------------------------------------------------
String Format::toString() const
{
    switch (value_)
    {
    case R8G8B8:
        return "R8G8B8";
    case A8R8G8B8:
        return "A8R8G8B8";
    case X8R8G8B8:
        return "X8R8G8B8";
    case R5G6B5:
        return "R5G6B5";
    case X1R5G5B5:
        return "X1R5G5B5";
    case A1R5G5B5:
        return "A1R5G5B5";
    case A4R4G4B4:
        return "A4R4G4B4";
    case R3G3B2:
        return "R3G3B2";
    case A8:
        return "A8";
    case A8R3G3B2:
        return "A8R3G3B2";
    case X4R4G4B4:
        return "X4R4G4B4";
    case A2B10G10R10:
        return "A2B10G10R10";
    case G16R16:
        return "G16R16";
    case A8P8:
        return "A8P8";
    case P8:
        return "P8";
    case L8:
        return "L8";
    case A8L8:
        return "A8L8";
    case A4L4:
        return "A4L4";
    case V8U8:
        return "V8U8";
    case L6V5U5:
        return "L6V5U5";
    case X8L8V8U8:
        return "X8L8V8U8";
    case Q8W8V8U8:
        return "Q8W8V8U8";
    case V16U16:
        return "V16U16";
    case W11V11U10:
        return "W11V11U10";
    case A2W10V10U10:
        return "A2W10V10U10";
    case UYVY:
        return "UYVY";
    case YUY2:
        return "YUY2";
    case DXT1:
        return "DXT1";
    case DXT2:
        return "DXT2";
    case DXT3:
        return "DXT3";
    case DXT4:
        return "DXT4";
    case DXT5:
        return "DXT5";
    case D16_LOCKABLE:
        return "D16_LOCKABLE";
    case D32:
        return "D32";
    case D15S1:
        return "D15S1";
    case D24S8:
        return "D24S8";
    case D16:
        return "D16";
    case D24X8:
        return "D24X8";
    case D24X4S4:
        return "D24X4S4";
    case VERTEXDATA:
        return "VERTEXDATA";
    case INDEX16:
        return "INDEX16";
    case INDEX32:
        return "INDEX32";
    case D32_LOCKABLE:
        return "D32_LOCKABLE";
    case S8_LOCKABLE:
        return "S8_LOCKABLE";
    case L16:
        return "L16";
    case Q16W16V16U16:
        return "Q16W16V16U16";
    case MULTI2_ARGB8:
        return "MULTI2_ARGB8";
    case R16F:
        return "R16F";
    case G16R16F:
        return "G16R16F";
    case A16B16G16R16F:
        return "A16B16G16R16F";
    case R32F:
        return "R32F";
    case G32R32F:
        return "G32R32F";
    case A32B32G32R32F:
        return "A32B32G32R32F";
    case CxV8U8:
        return "CxV8U8";
    case A1:
        return "A1";
    default:
        return "UNKNOWN";
    }
}

//-----------------------------------------------------------------------------
Format::Value Format::from_string(const char_t* str)
{
    if (tod_stricmp(str, "R8G8B8") == 0)
        return R8G8B8;
    else if (tod_stricmp(str, "A8R8G8B8") == 0)
        return A8R8G8B8;
    else if (tod_stricmp(str, "X8R8G8B8") == 0)
        return X8R8G8B8;
    else if (tod_stricmp(str, "R5G6B5") == 0)
        return R5G6B5;
    else if (tod_stricmp(str, "X1R5G5B5") == 0)
        return X1R5G5B5;
    else if (tod_stricmp(str, "A1R5G5B5") == 0)
        return A1R5G5B5;
    else if (tod_stricmp(str, "A4R4G4B4") == 0)
        return A4R4G4B4;
    else if (tod_stricmp(str, "R3G3B2") == 0)
        return R3G3B2;
    else if (tod_stricmp(str, "A8") == 0)
        return A8;
    else if (tod_stricmp(str, "A8R3G3B2") == 0)
        return A8R3G3B2;
    else if (tod_stricmp(str, "X4R4G4B4") == 0)
        return X4R4G4B4;
    else if (tod_stricmp(str, "A2B10G10R10") == 0)
        return A2B10G10R10;
    else if (tod_stricmp(str, "G16R16") == 0)
        return G16R16;
    else if (tod_stricmp(str, "A8P8") == 0)
        return A8P8;
    else if (tod_stricmp(str, "P8") == 0)
        return P8;
    else if (tod_stricmp(str, "L8") == 0)
        return L8;
    else if (tod_stricmp(str, "A8L8") == 0)
        return A8L8;
    else if (tod_stricmp(str, "A4L4") == 0)
        return A4L4;
    else if (tod_stricmp(str, "V8U8") == 0)
        return V8U8;
    else if (tod_stricmp(str, "L6V5U5") == 0)
        return L6V5U5;
    else if (tod_stricmp(str, "X8L8V8U8") == 0)
        return X8L8V8U8;
    else if (tod_stricmp(str, "Q8W8V8U8") == 0)
        return Q8W8V8U8;
    else if (tod_stricmp(str, "V16U16") == 0)
        return V16U16;
    else if (tod_stricmp(str, "W11V11U10") == 0)
        return W11V11U10;
    else if (tod_stricmp(str, "A2W10V10U10") == 0)
        return A2W10V10U10;
    else if (tod_stricmp(str, "UYVY") == 0)
        return UYVY;
    else if (tod_stricmp(str, "YUY2") == 0)
        return YUY2;
    else if (tod_stricmp(str, "DXT1") == 0)
        return DXT1;
    else if (tod_stricmp(str, "DXT2") == 0)
        return DXT2;
    else if (tod_stricmp(str, "DXT3") == 0)
        return DXT3;
    else if (tod_stricmp(str, "DXT4") == 0)
        return DXT4;
    else if (tod_stricmp(str, "DXT5") == 0)
        return DXT5;
    else if (tod_stricmp(str, "D16_LOCKABLE") == 0)
        return D16_LOCKABLE;
    else if (tod_stricmp(str, "D32") == 0)
        return D32;
    else if (tod_stricmp(str, "D15S1") == 0)
        return D15S1;
    else if (tod_stricmp(str, "D24S8") == 0)
        return D24S8;
    else if (tod_stricmp(str, "D16") == 0)
        return D16;
    else if (tod_stricmp(str, "D24X8") == 0)
        return D24X8;
    else if (tod_stricmp(str, "D24X4S4") == 0)
        return D24X4S4;
    else if (tod_stricmp(str, "VERTEXDATA") == 0)
        return VERTEXDATA;
    else if (tod_stricmp(str, "INDEX16") == 0)
        return INDEX16;
    else if (tod_stricmp(str, "INDEX32") == 0)
        return INDEX32;
    else if (tod_stricmp(str, "D32_LOCKABLE") == 0)
        return D32_LOCKABLE;
    else if (tod_stricmp(str, "S8_LOCKABLE") == 0)
        return S8_LOCKABLE;
    else if (tod_stricmp(str, "L16") == 0)
        return L16;
    else if (tod_stricmp(str, "Q16W16V16U16") == 0)
        return Q16W16V16U16;
    else if (tod_stricmp(str, "MULTI2_ARGB8") == 0)
        return MULTI2_ARGB8;
    else if (tod_stricmp(str, "R16F") == 0)
        return R16F;
    else if (tod_stricmp(str, "G16R16F") == 0)
        return G16R16F;
    else if (tod_stricmp(str, "A16B16G16R16F") == 0)
        return A16B16G16R16F;
    else if (tod_stricmp(str, "R32F") == 0)
        return R32F;
    else if (tod_stricmp(str, "G32R32F") == 0)
        return G32R32F;
    else if (tod_stricmp(str, "A32B32G32R32F") == 0)
        return A32B32G32R32F;
    else if (tod_stricmp(str, "CxV8U8") == 0)
        return CxV8U8;
    else if (tod_stricmp(str, "A1") == 0)
        return A1;
    return UNKNOWN;
}

//-----------------------------------------------------------------------------
int Format::bit() const
{
    switch (value_)
    {
    case A1:
        return 1;
    case DXT1:
        return 4;
    case R3G3B2:
    case A8:
    case P8:
    case L8:
    case A4L4:
    case DXT2:
    case DXT3:
    case DXT4:
    case DXT5:
    case S8_LOCKABLE:
    case MULTI2_ARGB8:
        return 8;
    case R8G8B8:
    case R5G6B5:
    case X1R5G5B5:
    case A1R5G5B5:
    case A4R4G4B4:
    case A8R3G3B2:
    case X4R4G4B4:
    case A8P8:
    case A8L8:
    case V8U8:
    case L6V5U5:
    case UYVY:
    case YUY2:
    case D16_LOCKABLE:
    case D15S1:
    case D16:
    case INDEX16:
    case L16:
    case R16F:
    case CxV8U8:
        return 16;
    case A8R8G8B8:
    case X8R8G8B8:
    case A2B10G10R10:
    case G16R16:
    case X8L8V8U8:
    case Q8W8V8U8:
    case V16U16:
    case W11V11U10:
    case A2W10V10U10:
    case D32:
    case D24S8:
    case D24X8:
    case D24X4S4:
    case INDEX32:
    case D32_LOCKABLE:
    case G16R16F:
    case R32F:
        return 32;
    case Q16W16V16U16:
    case A16B16G16R16F:
    case G32R32F:
        return 64;
    case A32B32G32R32F:
        return 128;
    default:
        return 0;
    }
}


//-----------------------------------------------------------------------------
int Format::sbufBit() const
{
    switch (value_)
    {
    case D24S8:
        return 8;
    case D24X4S4:
        return 4;
    case D32_LOCKABLE:
        return 32;
    default:
        return 0;
    }
}


//-----------------------------------------------------------------------------
int Format::zbufBit() const
{
    switch (value_)
    {
    case S8_LOCKABLE:
        return 8;
    case D15S1:
        return 15;
    case D16_LOCKABLE:
    case D16:
        return 16;
    case D24S8:
    case D24X8:
    case D24X4S4:
        return 24;
    case D32:
        return 32;
    default:
        return 0;
    }
}


//-----------------------------------------------------------------------------
Format::enumerator Format::beginEnum()
{
    return enumerator();
}


//-----------------------------------------------------------------------------
Format::enumerator Format::endEnum()
{
    return enumerator(INVALID);
}

//-----------------------------------------------------------------------------
Format::const_enumerator Format::beginEnum() const
{
    return enumerator();
}


//-----------------------------------------------------------------------------
Format::const_enumerator Format::endEnum() const
{
    return enumerator(INVALID);
}


//-----------------------------------------------------------------------------
Format::enumerator::enumerator():
index_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
Format::enumerator::enumerator(Value value):
index_(value)
{
    // empty
}


//-----------------------------------------------------------------------------
Format Format::enumerator::operator * () const
{
    return Format(s_values[index_]);
}


//-----------------------------------------------------------------------------
void Format::enumerator::operator ++ () const
{
    ++index_;
    if (index_ >= s_size)
        index_ = INVALID;
}


//-----------------------------------------------------------------------------
bool Format::enumerator::operator == (const enumerator& lhs) const
{
    return index_ == lhs.index_;
}

//-----------------------------------------------------------------------------
bool Format::enumerator::operator != (const enumerator& lhs) const
{
    return !(*this == lhs);
}


//-----------------------------------------------------------------------------
Format::Value Format::enumerator::s_values[] =
{
    R8G8B8, A8R8G8B8, X8R8G8B8, R5G6B5, X1R5G5B5, A1R5G5B5,
    A4R4G4B4, R3G3B2, A8, A8R3G3B2, X4R4G4B4, A2B10G10R10,
    G16R16, A8P8, P8, L8, A8L8, A4L4, V8U8, L6V5U5, X8L8V8U8,
    Q8W8V8U8, V16U16, W11V11U10, A2W10V10U10, UYVY, YUY2,
    DXT1, DXT2, DXT3, DXT4, DXT5,
    D16_LOCKABLE, D32, D15S1, D24S8, D16, D24X8, D24X4S4,
    VERTEXDATA, INDEX16, INDEX32,
    D32_LOCKABLE, S8_LOCKABLE, L16, Q16W16V16U16, MULTI2_ARGB8, R16F, G16R16F,
    A16B16G16R16F, R32F, G32R32F, A32B32G32R32F, CxV8U8, A1,
};


//-----------------------------------------------------------------------------
int Format::enumerator::s_size =
sizeof(Format::enumerator::s_values) / sizeof(Value);
