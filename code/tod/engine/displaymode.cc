#include "tod/engine/displaymode.h"

#include "tod/core/define.h"
#include "boost/tokenizer.hpp"

using namespace tod::core;
using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
DisplayMode::DisplayMode():
width_(0), height_(0), format_(Format::UNKNOWN), sbuf_(0), zbuf_(0),
fullscreen_(false), vsync_(false)
{

}


//-----------------------------------------------------------------------------
DisplayMode::DisplayMode(const char_t* mode):
width_(0), height_(0), format_(Format::UNKNOWN), sbuf_(0), zbuf_(0),
fullscreen_(false), vsync_(false)
{
    set(mode);
}


//-----------------------------------------------------------------------------
DisplayMode::DisplayMode(const String& mode):
width_(0), height_(0), format_(Format::UNKNOWN), sbuf_(0), zbuf_(0),
fullscreen_(false), vsync_(false)
{
    set(mode.c_str());
}


//-----------------------------------------------------------------------------
void DisplayMode::set(const char_t* mode)
{
    assign(mode);
    typedef boost::tokenizer<
        boost::char_separator<char_t>,
        DisplayMode::const_iterator, DisplayMode> Tokenizer;
    boost::char_separator<char_t> sep(STRING("[]"));
    Tokenizer tok(begin(), end(), sep);
    for (Tokenizer::iterator iter = tok.begin();
         iter != tok.end(); ++iter)
    {
        if (*iter == STRING("w"))
        {
            ++iter;
            if (iter != tok.end())
                width_ = iter->toInt();
        }
        else if (*iter == STRING("h"))
        {
            ++iter;
            if (iter != tok.end())
                height_ = iter->toInt();
        }
        else if (*iter == STRING("f"))
        {
            ++iter;
            if (iter != tok.end())
                format_ = *iter;
        }
        else if (*iter == STRING("sbuf"))
        {
            ++iter;
            if (iter != tok.end())
                sbuf_ = iter->toInt();
        }
        else if (*iter == STRING("zbuf"))
        {
            ++iter;
            if (iter != tok.end())
                zbuf_ = iter->toInt();
        }
        else if (*iter == STRING("fullscreen"))
        {
            ++iter;
            if (iter != tok.end())
            {
                if (*iter == STRING("true"))
                    fullscreen_ = true;
                else
                    fullscreen_ = false;
            }
        }
        else if (*iter == STRING("vsync"))
        {
            ++iter;
            if (*iter == STRING("true"))
                vsync_ = true;
            else
                vsync_ = false;
        }
        else if (*iter == STRING("title"))
        {
            ++iter;
            if (iter != tok.end())
                title_ = *iter;
        }
    }
}


//-----------------------------------------------------------------------------
const String DisplayMode::getTitle() const
{
    return title_;
}


//-----------------------------------------------------------------------------
int DisplayMode::getWidth() const
{
    return width_;
}


//-----------------------------------------------------------------------------
int DisplayMode::getHeight() const
{
    return height_;
}


//-----------------------------------------------------------------------------
Format DisplayMode::getFormat() const
{
    return format_;
}

//-----------------------------------------------------------------------------
Format DisplayMode::getDepthAndStencilFormat() const
{
    if (depthAndStencilFormat_ != Format::UNKNOWN)
        return depthAndStencilFormat_;

    for (Format::enumerator e = depthAndStencilFormat_.beginEnum();
         e != depthAndStencilFormat_.endEnum(); ++e)
    {
        if ((*e).sbufBit() == sbuf_ &&
            (*e).zbufBit() == zbuf_)
            return e;
    }

    return depthAndStencilFormat_;
}


//-----------------------------------------------------------------------------
bool DisplayMode::isFullscreen() const
{
    return fullscreen_;
}


//-----------------------------------------------------------------------------
bool DisplayMode::isWindowed() const
{
    return !fullscreen_;
}


//-----------------------------------------------------------------------------
bool DisplayMode::isVSync() const
{
    return vsync_;
}


//-----------------------------------------------------------------------------
DisplayMode& DisplayMode::operator = (const char_t* mode)
{   
    set(mode);
    return *this;
}
