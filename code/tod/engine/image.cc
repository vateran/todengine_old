#include "tod/engine/image.h"

#include "boost/algorithm/string.hpp"
#include "tod/core/resource.h"

using namespace tod::core;
using namespace tod::engine::graphics;

//-----------------------------------------------------------------------------
Image::Image(const Uri& uri):
uri_(uri), id_(IL_INVALID_VALUE), width_(0), height_(0)
{
    id_ = ilGenImage();
}


//-----------------------------------------------------------------------------
Image::~Image()
{
    destroy();
}


//-----------------------------------------------------------------------------
bool Image::create(int width, int height)
{
    return true;
}


//-----------------------------------------------------------------------------
void Image::destroy()
{
    if (id_ != IL_INVALID_VALUE)
        ilDeleteImage(id_);
    id_ = IL_INVALID_VALUE;
}


//-----------------------------------------------------------------------------
#include <windows.h>
bool Image::preload()
{
    // load resource
    tod::core::Resource resource(getUri());
    if (!resource.open(
        tod::core::Resource::OPEN_READ |
        tod::core::Resource::OPEN_BINARY))
        return false;
    dynamic_buffer_t buffer;
    resource.read(buffer);

    // figure out file format from file extension
    ILenum file_format;
    String ext = getUri().extractExtension();
    boost::to_lower(ext);
    if (ext == STRING("bmp"))
        file_format = IL_BMP;
    else if (ext == STRING("tga"))
        file_format = IL_TGA;
    else if (ext == STRING("png"))
        file_format = IL_PNG;
    else if (ext == STRING("jpg"))
        file_format = IL_JPG;
    else if (ext == STRING("dds"))
        file_format = IL_DDS;
    else if (ext == STRING("tif"))
        file_format = IL_TIF;
    else if (ext == STRING("tga"))
        file_format = IL_TGA;
    
    ilBindImage(id_);
    ilLoadL(file_format, &buffer[0], buffer.size());

    width_ = ilGetInteger(IL_IMAGE_WIDTH);
    height_ = ilGetInteger(IL_IMAGE_HEIGHT);

    ilConvertImage(IL_RGBA, IL_BYTE);

    data_ = reinterpret_cast<Color*>(ilGetData());
    return true;
}


//-----------------------------------------------------------------------------
int Image::width() const
{
    return width_;
}


//-----------------------------------------------------------------------------
int Image::height() const
{
    return height_;
}


//-----------------------------------------------------------------------------
const Uri& Image::getUri() const
{
    return uri_;
}

//-----------------------------------------------------------------------------
Color Image::getPixel(int x, int y) const
{
    if (x < 0 || y < 0 || x >= width_ || y >= height_)
        return Color();
    return *(data_ + y * width_ + x);
}
