#ifndef TOD_ENGINE_RESOURE_RESOURCEREF_H
#define TOD_ENGINE_RESOURE_RESOURCEREF_H
/**
    @ingroup TodEngineResource
    @class tod::engine::ResourceRef
    @brief 
*/

#include "tod/core/uri.h"
#include "tod/engine/resource.h"

namespace tod
{
namespace engine
{
    template <typename T>
    class ResourceRef
    {
    public:
        typedef ResourceRef<T> type;

    public:
        ResourceRef();
        ResourceRef(const type& ref);
        ResourceRef(Resource* r);
        virtual~ResourceRef();

        void initialize(Resource* r);
        void release();

        bool valid() const;
        bool invalid() const;

        template <typename DERIVED>
        DERIVED get();
        template <typename DERIVED>
        operator DERIVED ();

        operator T* ();
        operator const T* () const;

        T* operator -> ();
        const T* operator -> () const;

        type& operator = (T* r);
        bool operator == (const type& rhs) const;
        bool operator != (const type& rhs) const;
        bool operator < (const type& rhs) const;
        bool operator > (const type& rhs) const;

    private:
        union
        {
            Resource* resource_;
            T* ptr_;
        };
    };

#include "tod/engine/resourceref.inl"

}
}


#endif // TOD_ENGINE_RESOURE_RESOURCEREF_H
