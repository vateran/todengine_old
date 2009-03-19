#ifndef TOD_CORE_PROPERTY_ENUMPROPERTY_H
#define TOD_CORE_PROPERTY_ENUMPROPERTY_H
/**
    @ingroup TodCoreObject
    @class tod::EnumProperty
    @brief
*/

#include <hash_map>
#include "tod/core/property.h"

namespace tod
{
    template <typename PROPERTY_TYPE>
    class EnumProperty : public Property
    {
    public:
        typedef PROPERTY_TYPE Value;
        typedef std::map<String, Value> StringMap;
        typedef stdext::hash_map<Value, String> ValueMap;
        typedef typename ValueMap::iterator iterator;
        typedef typename ValueMap::const_iterator const_iterator;

    public:
        virtual void set(Object* object, const String& name)=0;
        virtual void set(Object* object, const PROPERTY_TYPE& value)=0;
        virtual const PROPERTY_TYPE& get(Object* object) const=0;

        void add(const String& name, const Value& value);
        const String& getName(const Value& value);
        const Value& getValue(const String& name);

        iterator firstEnumerator();
        iterator lastEnumerator();
        const_iterator firstEnumerator() const;
        const_iterator lastEnumerator() const;

        override type_id getType() const;

    protected:
        StringMap stringMap_;
        ValueMap valueMap_;
    };

#include "tod/core/enumproperty.inl"

}


#endif // TOD_CORE_PROPERTY_ENUMPROPERTY_H
