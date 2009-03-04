#ifndef TOD_CORE_RESOURCE_FSRESOURCEPROTOCOL_H
#define TOD_CORE_RESOURCE_FSRESOURCEPROTOCOL_H
/**
    @ingroup TodCoreResource
    @class tod::FsResourceProtocol
    @brief
*/

#include "tod/core/resourceprotocol.h"

namespace tod
{
    class ResourceImplementator;
    class FsResourceProtocol : public ResourceProtocol
    {
    public:
		FsResourceProtocol();
        virtual~FsResourceProtocol();

        override ResourceImplementator* create(const Uri& uri);
        override bool destroy(const Uri& uri);

        override bool findStorages(ResourceStorages* rs);
        override bool findEntries(ResourceEntries* re, const String& path, bool file);

    private:
        template <typename T>
        struct ConvertCharacterFunctor
        {
            ConvertCharacterFunctor(const T& src, const T& dst):
            src_(src), dst_(dst) {}
            T operator () (const T& ch) const
            {
                if (ch == src_)
                    return dst_;
                return ch;
            }
            T src_;
            T dst_;
        };

    private:
        void make_path(const Uri& uri);
        void filetime_to_unixtime(const FILETIME& ft, time_t* t);
		void push_cwd();
		void pop_cwd();

	private:
		String baseAbsPath_;
		String curAbsPath_;
    };
}

#endif // TOD_CORE_RESOURCE_FSRESOURCEPROTOCOL_H