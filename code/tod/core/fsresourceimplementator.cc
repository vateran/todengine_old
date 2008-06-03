#include "tod/core/fsresourceimplementator.h"

#include "tod/core/exception.h"
#include "tod/core/resource.h"

using namespace tod;

//-----------------------------------------------------------------------------
FsResourceImplementator::FsResourceImplementator(const String& path):path_(path)
{
}


//-----------------------------------------------------------------------------
bool FsResourceImplementator::open(int mode)
{
    std::ios_base::openmode om = 0;
    if (mode & Resource::OPEN_WRITE)
        om |= std::ios_base::out;
    if (mode & Resource::OPEN_READ)
        om |= std::ios_base::in;
    if (mode & Resource::OPEN_BINARY)
        om |= std::ios_base::binary;        
    file_.open(path_.c_str(), om);
    if (!file_.good())
    {
        TOD_THROW_EXCEPTION(TODEXCEPTIONCODE_RESOURCEOPEN,
            String(STRING("Could not open resource(%s)\n"), path_.c_str()));
        return false;
    }
    return true;
}


//-----------------------------------------------------------------------------
void FsResourceImplementator::close()
{
    file_.close();
}


//-----------------------------------------------------------------------------
int FsResourceImplementator::write(const buffer_t* buffer, length_t len)
{
    std::ios_base::streampos p = file_.tellp();
    file_.write(buffer, len);
    return file_.tellp() - p;
}


//-----------------------------------------------------------------------------
int FsResourceImplementator::read(buffer_t* buffer, length_t len)
{
    std::ios_base::streampos g = file_.tellg();
    file_.read(buffer, len);
    return file_.tellg() - g;
}


//-----------------------------------------------------------------------------
int FsResourceImplementator::size() const
{
    std::ios_base::streampos g = file_.tellg();
    file_.seekg(0, std::ios_base::end);
    int s = file_.tellg();;
    file_.seekg(g, std::ios_base::beg);
    return s;
}
