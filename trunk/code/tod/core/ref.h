#ifndef TOD_CORE_UTILITY_REF_H
#define TOD_CORE_UTILITY_REF_H
/**
    @ingroup TodCoreUtility
    @class tod::Ref
    @brief 
*/

#include "tod/core/define.h"

namespace tod
{
    class Node;
    template <typename T>
    class Ref
    {
    public:
        typedef Ref<T> type;

    public:
        Ref();
        Ref(const type& ref);
        Ref(Node* instance);
        ~Ref();

        void initialize(Node* instance);
        void release();

        bool valid() const;
        bool invalid() const;

        template <typename DERIVED>
        DERIVED get();
        template <typename DERIVED>
        DERIVED get() const;
        template <typename DERIVED>
        operator DERIVED ();
        template <typename DERIVED>
        operator DERIVED () const;

        operator T* ();
        T* operator -> ();

        T* operator * ()
        {
            return instance_;
        }
        T* operator * () const
        {
            return instance_;
        }

        type& operator = (Node* instance);

        bool operator == (Node* instance) const;
        bool operator != (Node* instance) const;

        bool operator == (const type& rhs) const;
        bool operator != (const type& rhs) const;
        bool operator < (const type& rhs) const;
        bool operator > (const type& rhs) const;

    private:
        union
        {
            T* instance_;   // real type
            Node* node_;    // abstract type
        };
    };

#include "tod/core/ref.inl"

}

#endif // TOD_CORE_UTILITY_REF_H
