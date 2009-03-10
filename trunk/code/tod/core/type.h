#ifndef TOD_CORE_OBJECT_TYPE_H
#define TOD_CORE_OBJECT_TYPE_H
/**
    @ingroup TodCoreObject
    @class tod::Type
    @brief
*/
/**
    @ingroup TodCoreObject
    @class tod::ConcreteType
    @brief
*/

#include <bitset>
#include "tod/core/define.h"
#include "tod/core/properties.h"
#include "tod/core/methods.h"

namespace tod
{
    class Object;    
    class Type
    {
    public:
        enum Flag
        {
            FLAG_BINDEDMETHOD,
            FLAG_BINDEDPROPERTY,

            FLAG_MAX,
        };

    public:
        Type(const char_t* name, Type* base);

        virtual Object* create() const=0;
        virtual void bindMethod()=0;
        virtual void bindProperty()=0;
        virtual bool isAbstract() const=0;

        Type* findTypeInGenerations(const String& name);
        Type* findTypeInGenerations(const char_t* name);

        Type* getBase();
        const String& getName() const;
        bool equal(const Type* type) const;
        bool isKindOf(const char_t* name) const;
        bool isKindOf(const Type* type) const;

        bool addMethod(Method* method);
        void removeMethod(const char_t* name);
        Method* findMethod(const String& name);
        Method* findMethod(const char_t* name);
        size_t computeMethodSize() const;
        Methods::iterator firstMethod();
        Methods::iterator lastMethod();
        Methods::const_iterator firstMethod() const;
        Methods::const_iterator lastMethod() const;        
        bool hasBindedMethod() const;

        bool addProperty(Property* property);
        void removeProperty(const char_t* name);
        Property* findProperty(const String& name);
        Property* findProperty(const char_t* name);
        size_t computePropertySize() const;
        Properties::iterator firstProperty();
        Properties::iterator lastProperty();
        Properties::const_iterator firstProperty() const;
        Properties::const_iterator lastProperty() const;
        bool hasBindedProperty() const;
        
        void setFlag(Flag index, bool enable);

    private:
        String name_;
        Type* base_;
        Properties properties_;
        Methods methods_;
        std::bitset<FLAG_MAX> flags_;
    };

    template <typename T>
    class AbstractConcreteType : public Type
    {
    public:
        AbstractConcreteType(const char_t* name, Type* base);
        override Object* create() const;
        override void bindMethod();
        override void bindProperty();
        override bool isAbstract() const;
    };

    template <typename T>
    class ConcreteType : public AbstractConcreteType<T>
    {
    public:
        ConcreteType(const char_t* name, Type* base);
        override Object* create() const;
        override bool isAbstract() const;
    };

#include "tod/core/type.inl"

/// declare ClassBase macro
#define DECLARE_CLASSBASE(cls) public:\
    typedef cls type;\
    virtual const tod::char_t* toString() const { return #cls; }
    /// declare AbstractClass macro
#define DECLARE_SUPERABSTRACTCLASS(cls) \
    DECLARE_CLASSBASE(cls)\
    virtual tod::Type* getType() { return &TYPE; }\
    static tod::AbstractConcreteType<cls> TYPE;
/// declare AbstractClass macro
#define DECLARE_ABSTRACTCLASS(cls, base_cls) \
    typedef base_cls super;\
    DECLARE_SUPERABSTRACTCLASS(cls)
/// declare SuperClass macro
#define DECLARE_SUPERCLASS(cls) \
    DECLARE_CLASSBASE(cls)\
    virtual tod::Type* getType() { return &TYPE; }\
    static tod::ConcreteType<cls> TYPE;
/// declare Class macro
#define DECLARE_CLASS(cls, base_cls) public:\
    typedef base_cls super;\
    DECLARE_SUPERCLASS(cls)

/// impletemt SuperAbstractClass macro
#define IMPLEMENT_SUPERABSTRACTCLASS(cls) \
    tod::AbstractConcreteType<cls> cls::TYPE(#cls, 0);
/// impletemt AbstractClass macro
#define IMPLEMENT_ABSTRACTCLASS(cls, base_cls) \
    tod::AbstractConcreteType<cls> cls::TYPE(#cls, &base_cls::TYPE);
/// impletemt SuperClass macro
#define IMPLEMENT_SUPERCLASS(cls) \
    tod::ConcreteType<cls> cls::TYPE(#cls, 0);
/// impletemt Class macro
#define IMPLEMENT_CLASS(cls, base_cls) \
    tod::ConcreteType<cls> cls::TYPE(#cls, &base_cls::TYPE);

}

#endif // TOD_CORE_OBJECT_TYPE_H
