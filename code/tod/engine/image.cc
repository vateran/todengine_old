#include "tod/engine/image.h"

#include "boost/algorithm/string.hpp"
#include "tod/core/resource.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
Image::Image():
id_(IL_INVALID_VALUE), width_(0), height_(0)
{
    id_ = ilGenImage();
}


//-----------------------------------------------------------------------------
Image::Image(const Uri& uri):
uri_(uri), id_(IL_INVALID_VALUE), width_(0), height_(0)
{
    id_ = ilGenImage();
}


//-----------------------------------------------------------------------------
Image::~Image()
{
    if (id_ != IL_INVALID_VALUE)
        ilDeleteImage(id_);
    id_ = IL_INVALID_VALUE;
}


//-----------------------------------------------------------------------------
bool Image::create(int width, int height)
{
    return true;
}


//-----------------------------------------------------------------------------
void Image::destroy()
{   
}


//-----------------------------------------------------------------------------
bool Image::preload()
{
    // load resource
    tod::Resource resource(getUri());
    if (!resource.open(
        tod::Resource::OPEN_READ |
        tod::Resource::OPEN_BINARY))
        return false;
    dynamic_buffer_t buffer;
    resource.read(&buffer);

    // figure out file format from file extension
    ILenum file_format;
    String ext = getUri().extractExtension();
    boost::to_lower(ext);
    if (ext == "bmp")
        file_format = IL_BMP;
    else if (ext == "tga")
        file_format = IL_TGA;
    else if (ext == "png")
        file_format = IL_PNG;
    else if (ext == "jpg")
        file_format = IL_JPG;
    else if (ext == "dds")
        file_format = IL_DDS;
    else if (ext == "tif")
        file_format = IL_TIF;
    else if (ext == "tga")
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
void Image::setUri(const Uri& uri)
{
    uri_ = uri;
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
