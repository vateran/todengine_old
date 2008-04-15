#include "tod/core/fsresourceprotocol.h"

#include "tod/core/fsresourceimplementator.h"

using namespace tod::core;

//-----------------------------------------------------------------------------
FsResourceProtocol::~FsResourceProtocol()
{
    // empty
}


//-----------------------------------------------------------------------------
ResourceImplementator* FsResourceProtocol::create(const Uri& uri)
{
    make_path(uri);

    String path(combine_path(uri));
    if (!uri.extractFile().empty())
    {
        path += STRING("/");
        path += uri.extractFile();
    }
    return new FsResourceImplementator(path);
}


//-----------------------------------------------------------------------------
bool FsResourceProtocol::destroy(const Uri& uri)
{
    return true;
}


//-----------------------------------------------------------------------------
void FsResourceProtocol::make_path(const Uri& uri)
{
    String path = combine_path(uri);
    size_t i = 0;
    while (i < path.size())
    {
        i = path.find(STRING('/'), i);
        String dir(path, 0, i);
        tod_mkdir(dir.c_str());
        if (-1 == i)
            break;
        ++i;
    }
}


//-----------------------------------------------------------------------------
String FsResourceProtocol::combine_path(const Uri& uri)
{
    String path(getBasePath());
    if (!uri.getPackage().empty())
    {
        path += STRING("/");
        path += uri.getPackage();
    }
    if (!uri.extractPath().empty())
    {
        path += STRING("/");
        path += uri.extractPath();
    }
    return path;
}
