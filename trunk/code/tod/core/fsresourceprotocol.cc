#include "tod/core/fsresourceprotocol.h"

#include "tod/core/define.h"
#include "tod/core/resourcecache.h"
#include "tod/core/fsresourceimplementator.h"

using namespace tod;

//-----------------------------------------------------------------------------
FsResourceProtocol::FsResourceProtocol()
{
#ifdef WIN32
	char_t cpath[MAX_PATH];
	tod_getcwd(cpath, MAX_PATH);
	baseAbsPath_ = cpath;
#endif
}


//-----------------------------------------------------------------------------
FsResourceProtocol::~FsResourceProtocol()
{
	// empty
}


//-----------------------------------------------------------------------------
void FsResourceProtocol::push_cwd()
{
#ifdef WIN32
	char_t path[MAX_PATH];
	tod_getcwd(path, MAX_PATH);
	curAbsPath_ = path;	

	tod_chdir(baseAbsPath_.c_str());
#endif
}


//-----------------------------------------------------------------------------
void FsResourceProtocol::pop_cwd()
{
#ifdef WIN32
	tod_chdir(curAbsPath_.c_str());
#endif
}


//-----------------------------------------------------------------------------
ResourceImplementator* FsResourceProtocol::create(const Uri& uri)
{
    ResourceImplementator* ri = ResourceCache::instance()->find(uri);
    if (0 == ri)
    {
        push_cwd();
        String path(uri.makePhysicalAbsolutePath());
        make_path(uri);
        pop_cwd();
        ri = new FsResourceImplementator(path);

        ResourceCache::instance()->add(uri, ri);
    }
	return ri;
}


//-----------------------------------------------------------------------------
bool FsResourceProtocol::destroy(const Uri& uri)
{
    return true;
}


//-----------------------------------------------------------------------------
bool FsResourceProtocol::findStorages(ResourceStorages* rs)
{
#ifdef WIN32
    WIN32_FIND_DATAA fdata;

    HANDLE h = FindFirstFileA(getBasePath() + "/*", &fdata);
    while (h != INVALID_HANDLE_VALUE)
    {        
        if (fdata.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) {}
        else if (tod_strcmp(fdata.cFileName, ".") == 0 ||
            tod_strcmp(fdata.cFileName, "..") == 0) {}
        else if (fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            rs->push_back(new ResourceStorage(fdata.cFileName, this));
        }
        if (!FindNextFileA(h, &fdata))
            break;
    }

    FindClose(h);
#endif
    return true;
}


//-----------------------------------------------------------------------------
void FsResourceProtocol::filetime_to_unixtime(const FILETIME& ft, time_t* t)
{
    int64_t* tt = (int64_t*)&ft;
#ifdef __WIN32__
    *tt -= 116444736000000000;
#else
	*tt -= 116444736000000000LLU;
#endif
    *tt /= 10000000;
    *t = (time_t)*tt;
}


//-----------------------------------------------------------------------------
bool FsResourceProtocol::findEntries
(ResourceEntries* re, const String& path, bool file)
{
#ifdef WIN32
    WIN32_FIND_DATAA fdata;

    String query(getBasePath() + "/" + path);
    String base_path(query.extractPath());
    HANDLE h = FindFirstFileA(query, &fdata);
    while (h != INVALID_HANDLE_VALUE)
    {
        if (fdata.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) {}
        else if (tod_strcmp(fdata.cFileName, ".") == 0 ||
            tod_strcmp(fdata.cFileName, "..") == 0) {}
        else if (!(fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == file)
        {
            int64_t size = fdata.nFileSizeHigh;
            size <<= 32;
            size |= fdata.nFileSizeLow;
            
            time_t t;
            filetime_to_unixtime(fdata.ftLastWriteTime, &t);

            SHFILEINFOA fi;
            String tpath(base_path + "/" + fdata.cFileName);
            std::transform(tpath.begin(), tpath.end(), tpath.begin(),
                ConvertCharacterFunctor<char_t>('/', '\\'));
            SHGetFileInfoA(tpath, FILE_ATTRIBUTE_NORMAL, &fi, sizeof(fi),
                SHGFI_EXETYPE | SHGFI_ICON | SHGFI_ICONLOCATION | SHGFI_SHELLICONSIZE |
                SHGFI_SMALLICON | SHGFI_TYPENAME);

            re->push_back(
                ResourceEntry(fdata.cFileName, fi.szTypeName,
                    file, false, size, t, this));
        }
        if (!FindNextFileA(h, &fdata))
            break;
    }

    FindClose(h);
#endif
    return true;
}


//-----------------------------------------------------------------------------
void FsResourceProtocol::make_path(const Uri& uri)
{
    tod_chdir(getBasePath().c_str());
    String tpath(uri.getPackage() + "/" + uri.extractPath());

    size_t i = 0;
    while (i < tpath.size())
    {
        i = tpath.find('/', i);
        String dir(tpath, 0, i);
        tod_mkdir(dir.c_str());
        if (-1 == i)
            break;
        ++i;
    }
}
