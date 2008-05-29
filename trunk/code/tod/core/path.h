#ifndef TOD_CORE_TYPE_PATH_H
#define TOD_CORE_TYPE_PATH_H
/**
    @ingroup TodCoreType
    @class tod::core::Path
    @brief Node of Hierarchy Path

    @section Path
        - AbsolutePath
          - /usr/scene/fighter
        - RelativePath
          - fighter/weapon
*/

#include <wchar.h>
#include "boost/tokenizer.hpp"
#include "tod/core/define.h"
#include "tod/core/string.h"

namespace tod
{
namespace core
{
    class Path : public String
    {
    public:
        typedef boost::tokenizer<
            boost::char_separator<char_t>,
            Path::const_iterator, Path> Tokenizer;
        typedef Tokenizer::iterator iterator;
        typedef Tokenizer::const_iterator const_iterator;

    public:
        Path();
        Path(const char_t* path);
        Path(const Path& path);
        Path(const String& path);

        bool isAbsolute() const;
        bool isRelative() const;

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

    private:
        mutable Tokenizer tokenizer_;

    private:
        static boost::char_separator<char_t> s_seperator;
    };

#include "tod/core/path.inl"

}
}

#endif // TOD_CORE_TYPE_PATH_H
