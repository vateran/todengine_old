#ifndef TOD_ENGINE_RESOURE_RESOURCEHOLDER_H
#define TOD_ENGINE_RESOURE_RESOURCEHOLDER_H
/**
    @ingroup TodEngineResource
    @class tod::engine::ResourceHolder
    @brief 
*/

#include <map>
#include "tod/core/assert.h"
#include "tod/core/uri.h"
#include "tod/engine/resource.h"
#include "tod/engine/resourceref.h"

namespace tod
{
namespace engine
{
    class ResourceHolderBase
    {
    public:
        virtual~ResourceHolderBase() {}
    };

    template <typename T>
    class ResourceHolder : public ResourceHolderBase
    {
    public:
        typedef ResourceRef<T> RefType;
        typedef std::map<Uri, RefType> NamedResources;

    public:
        bool empty() const;
        size_t size() const;
        void clear();

        void add(Resource* r);
        void remove(const Uri& uri);
        T* find(const Uri& uri);

        void onLostDevice();
        void onRestoreDevice();

        typename NamedResources::iterator begin();
        typename NamedResources::iterator end();
        typename NamedResources::const_iterator begin() const;
        typename NamedResources::const_iterator end() const;

    private:
        NamedResources namedResources_;
    };

#include "tod/engine/resourceholder.inl"

}
}


#endif // TOD_ENGINE_RESOURE_RESOURCEHOLDER_H
