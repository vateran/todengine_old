#include "tod/core/uri.h"

#include <list>
#include <direct.h>
#include "tod/core/define.h"
#include "tod/core/assert.h"
#include "tod/core/resourcemanager.h"

using namespace tod;

//-----------------------------------------------------------------------------
Uri::Uri()
{
    // empty
}


//-----------------------------------------------------------------------------
Uri::Uri(const char_t* uri)
{
    set(uri);
}


//-----------------------------------------------------------------------------
Uri::Uri(const String& uri)
{
    set(uri.c_str());
}


//-----------------------------------------------------------------------------
void Uri::clear()
{
    uri_.clear();
    protocol_.clear();
    managed_.clear();
    ip_.clear();
    port_.clear();
    path_.clear();
}


//-----------------------------------------------------------------------------
bool Uri::empty() const
{
    return uri_.empty();
}


//-----------------------------------------------------------------------------
size_t Uri::size() const
{
    return uri_.size();
}


//-----------------------------------------------------------------------------
void Uri::set(const char_t* uri)
{
    protocol_.clear();
    ip_.clear();
    port_.clear();
    managed_.clear();
    path_.clear();

    uri_ = uri;

    size_t s = 0;
    // find protocol type
    size_t e = uri_.find(STRING("://"));
    // not found protocol
    if (-1 == e)
        return;
    protocol_.assign(uri_, 0, e);
    s = e + 3;

    if (protocol_ == STRING("managed"))
    {
        // find managed name(split by '#')
        e = uri_.find(STRING("#"), s);
        managed_.assign(uri_, s, e - s);
        // if found managed name then assign path
        if (-1 != e)
        {
            s = e + 1;
            if (s < uri_.size())
                path_.assign(uri_, s, -1);
        }
    }
    else if (protocol_ == STRING("file"))
    {
        path_.assign(uri_, s, -1);
    }
    else if (protocol_ == STRING("http"))
    {
        // find port
        e = uri_.find(STRING(":"), s);
        if (-1 == e)
        {
            // ip only
            e = uri_.find(STRING("/"), s);
            ip_.assign(uri_, s, e - s);
        }
        else
        {
            // ip + port
            ip_.assign(uri_, s, e - s);
            s = e + 1;
            e = uri_.find(STRING("/"), s);
            port_.assign(uri_, s, e - s);
        }

        if (-1 != e)
            path_.assign(uri_, e + 1, -1);
    }
    else
    {
        // no available protocol
        return;
    }
}


//-----------------------------------------------------------------------------
String Uri::extractPath() const
{
    size_t s = path_.rfind(STRING("/"));
    if (-1 == s)
        return String();
    return String(path_, 0, s);
}

//-----------------------------------------------------------------------------
String Uri::extractFile() const
{
    size_t s = path_.rfind(STRING("/"));
    // 찾지 못했다면 path 가 File
    if (-1 == s)
        return path_;
    return String(path_, s + 1, -1);
}


//-----------------------------------------------------------------------------
String Uri::extractFileName() const
{
    size_t e = path_.rfind(STRING("."));
    size_t s = path_.rfind(STRING("/"), e);
    return String(path_, s + 1, e - s - 1);
}


//-----------------------------------------------------------------------------
String Uri::extractExtension() const
{
    size_t s = path_.rfind(STRING("."));
    return String(path_, s + 1, -1);
}


//-----------------------------------------------------------------------------
void Uri::setProtocol(const char_t* protocol)
{
    protocol_ = protocol;
}


//-----------------------------------------------------------------------------
void Uri::setPackage(const char_t* managed)
{
    managed_ = managed;
}


//-----------------------------------------------------------------------------
void Uri::setIp(const char_t* ip)
{
    ip_ = ip;
}


//-----------------------------------------------------------------------------
void Uri::setPort(const char_t* port)
{
    port_ = port;
}


//-----------------------------------------------------------------------------
void Uri::setPath(const char_t* path)
{
    path_ = path;
}


//-----------------------------------------------------------------------------
String Uri::makePhysicalAbsolutePath() const
{
    String apath;
#ifdef _WIN32

    char_t cwd[MAX_PATH];
    apath += tod_getcwd(cwd, 256);
    apath += STRING("/") + ResourceManager::instance()->getBasePath();

    apath += STRING("/") + managed_;
    make_absolutepath(&apath);
    apath += STRING("/") + path_;

#endif

    return apath;
}


//-----------------------------------------------------------------------------
void Uri::make_absolutepath(String* path) const
{
	size_t nbegin = 0;
	std::list<String> pathes;
	for (size_t i = 0; i < path->size(); ++i)
	{
		if (path->at(i) == STRING('/') ||
            path->at(i) == STRING('\\') &&
            nbegin != i)
		{
            String name(path->substr(nbegin, i - nbegin));
            nbegin = i + 1;
            if (name == STRING("."))
                continue;
            else if (name == STRING(".."))
                pathes.pop_back();
            else
			    pathes.push_back(name);
		}
	}
    pathes.push_back(path->substr(nbegin, -1));

	*path = "";
    while (pathes.size())
    {
        *path += pathes.front();
        pathes.pop_front();
		if (pathes.size() > 0)
			*path += STRING("/");
	}
}