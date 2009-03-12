#include "tod/core/tostring.h"

#include <strsafe.h>
#include "boost/tokenizer.hpp"
#include "tod/core/define.h"
#include "tod/core/primitivetype.h"
#include "tod/core/string.h"
#include "tod/core/color.h"
#include "tod/core/uri.h"
#include "tod/core/stringconverter.h"
#include "tod/core/property.h"
#include "tod/core/simpleproperty.h"

using namespace tod;

//-----------------------------------------------------------------------------
class BoolStringConverter : public StringConverter
{
public:
    override type_id getTypeId()
    {
        return TypeId<bool>::id();
    }
    override const char_t* getTypeKeyword() const
    {
        return "b";
    }
    override const String& toString(Object* object, Property* property)
    {
        typedef SimpleProperty<bool> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        char_t buf[8];
        tod_snprintf(buf, 8, p->get(object)?"true":"false");
        return str_ = buf;
    }
    override void fromString(Object* object, Property* property, const String& value)
    {
        typedef SimpleProperty<bool> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        
        bool v = false;
        if (value == "true" ||
            value == "t" ||
            value == "o" ||
            value.toInt() > 0)
            v = true;
        p->set(object, v);
    }

private:
    String str_;
};

//-----------------------------------------------------------------------------
class IntStringConverter : public StringConverter
{
public:
    override type_id getTypeId()
    {
        return TypeId<int>::id();
    }
    override const char_t* getTypeKeyword() const
    {
        return "i";
    }
    override const String& toString(Object* object, Property* property)
    {
        typedef SimpleProperty<int> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        char_t buf[16];
        tod_snprintf(buf, 16, "%d", p->get(object));
        return str_ = buf;
    }
    override void fromString(Object* object, Property* property, const String& value)
    {
        typedef SimpleProperty<int> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        p->set(object, value);
    }

private:
    String str_;
};


//-----------------------------------------------------------------------------
class UnsignedIntStringConverter : public StringConverter
{
public:
    override type_id getTypeId()
    {
        return TypeId<unsigned int>::id();
    }
    override const char_t* getTypeKeyword() const
    {
        return "i";
    }
    override const String& toString(Object* object, Property* property)
    {
        typedef SimpleProperty<unsigned int> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        char_t buf[16];
        tod_snprintf(buf, 16, "%d", p->get(object));
        return str_ = buf;
    }
    override void fromString(Object* object, Property* property, const String& value)
    {
        typedef SimpleProperty<unsigned int> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        p->set(object, value);
    }

private:
    String str_;
};

//-----------------------------------------------------------------------------
class Int64StringConverter : public StringConverter
{
public:
    override type_id getTypeId()
    {
        return TypeId<int64_t>::id();
    }
    override const char_t* getTypeKeyword() const
    {
        return "i";
    }
    override const String& toString(Object* object, Property* property)
    {
        typedef SimpleProperty<int64_t> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        char_t buf[32];
        tod_snprintf(buf, 32, "%I64d", p->get(object));
        return str_ = buf;
    }
    override void fromString(Object* object, Property* property, const String& value)
    {
        typedef SimpleProperty<int64_t> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        p->set(object, value);
    }

private:
    String str_;
};

//-----------------------------------------------------------------------------
class UnsignedInt64StringConverter : public StringConverter
{
public:
    override type_id getTypeId()
    {
        return TypeId<uint64_t>::id();
    }
    override const char_t* getTypeKeyword() const
    {
        return "i";
    }
    override const String& toString(Object* object, Property* property)
    {
        typedef SimpleProperty<uint64_t> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        char_t buf[32];
        tod_snprintf(buf, 32, "%I64d", p->get(object));
        return str_ = buf;
    }
    override void fromString(Object* object, Property* property, const String& value)
    {
        typedef SimpleProperty<uint64_t> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        p->set(object, tod_atoi64(value));
    }

private:
    String str_;
};

//-----------------------------------------------------------------------------
class FloatStringConverter : public StringConverter
{
public:
    override type_id getTypeId()
    {
        return TypeId<float>::id();
    }
    override const char_t* getTypeKeyword() const
    {
        return "f";
    }
    override const String& toString(Object* object, Property* property)
    {
        typedef SimpleProperty<float> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        char_t buf[16];
        tod_snprintf(buf, 16, "%.3f", p->get(object));
        return str_ = buf;
    }
    override void fromString(Object* object, Property* property, const String& value)
    {
        typedef SimpleProperty<float> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        p->set(object, value);
    }

private:
    String str_;
};


//-----------------------------------------------------------------------------
class DoubleStringConverter : public StringConverter
{
public:
    override type_id getTypeId()
    {
        return TypeId<double>::id();
    }
    override const char_t* getTypeKeyword() const
    {
        return "d";
    }
    override const String& toString(Object* object, Property* property)
    {
        typedef SimpleProperty<double> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        char_t buf[64];
        tod_snprintf(buf, 32, "%.3f", p->get(object));
        return str_ = buf;
    }
    override void fromString(Object* object, Property* property, const String& value)
    {
        typedef SimpleProperty<double> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        p->set(object, value);
    }

private:
    String str_;
};

//-----------------------------------------------------------------------------
class StringStringConverter : public StringConverter
{
public:
    override type_id getTypeId()
    {
        return TypeId<const String&>::id();
    }
    override const char_t* getTypeKeyword() const
    {
        return "s";
    }
    override const String& toString(Object* object, Property* property)
    {
        typedef SimpleProperty<const String&> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        return p->get(object);
    }
    override void fromString(Object* object, Property* property, const String& value)
    {
        typedef SimpleProperty<const String&> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        p->set(object, value);
    }
};


//-----------------------------------------------------------------------------
class NameStringConverter : public StringStringConverter
{
public:
    override type_id getTypeId()
    {
        return TypeId<const String&>::id();
    }
    override const char_t* getTypeKeyword() const
    {
        return "s";
    }
    override const String& toString(Object* object, Property* property)
    {
        typedef SimpleProperty<const String&> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        return p->get(object);
    }
    override void fromString(Object* object, Property* property, const String& value)
    {
        typedef SimpleProperty<const String&> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        p->set(object, value);
    }
};


//-----------------------------------------------------------------------------
class UriStringConverter : public StringStringConverter
{
public:
    override type_id getTypeId()
    {
        return TypeId<const Uri&>::id();
    }
    override const char_t* getTypeKeyword() const
    {
        return "uri";
    }
    override const String& toString(Object* object, Property* property)
    {
        typedef SimpleProperty<const Uri&> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        return p->get(object).get();
    }
    override void fromString(Object* object, Property* property, const String& value)
    {
        typedef SimpleProperty<const Uri&> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        p->set(object, value);
    }
};


//-----------------------------------------------------------------------------
class Vector3StringConverter : public StringConverter
{
public:
    override type_id getTypeId()
    {
        return TypeId<const Vector3&>::id();
    }
    override const char_t* getTypeKeyword() const
    {
        return "vector3";
    }
    override const String& toString(Object* object, Property* property)
    {
        typedef SimpleProperty<const Vector3&> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        char_t buf[48];
        const Vector3& v = p->get(object);
        tod_snprintf(buf, 48, "%.3f %.3f %.3f", v.x_, v.y_, v.z_);
        return str_ = buf;
    }
    override void fromString(Object* object, Property* property, const String& value)
    {
        typedef SimpleProperty<const Vector3&> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);

        typedef boost::tokenizer<
            boost::char_separator<char_t>,
            String::const_iterator, String> Tokenizer;
        static boost::char_separator<char_t> sep(" ,");
        Tokenizer tok(value, sep);
        Tokenizer::iterator i = tok.begin();
        Vector3 v;
        int c = 0;
        for (Tokenizer::iterator i = tok.begin();
             i != tok.end(); ++i, ++c)
            v.set(c, static_cast<float>(tod_atof(i->c_str())));
        p->set(object, v);
    }

private:
    String str_;
};


//-----------------------------------------------------------------------------
class ColorStringConverter : public StringConverter
{
public:
    override type_id getTypeId()
    {
        return TypeId<const Color&>::id();
    }
    override const char_t* getTypeKeyword() const
    {
        return "color";
    }
    override const String& toString(Object* object, Property* property)
    {
        typedef SimpleProperty<const Color&> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);
        char_t buf[32];
        const Color& v = p->get(object);
        tod_snprintf(buf, 32, "%d %d %d %d", v.r_, v.g_, v.b_, v.a_);
        return str_ = buf;
    }
    override void fromString(Object* object, Property* property, const String& value)
    {
        typedef SimpleProperty<const Color&> AdaptiveProperty;
        AdaptiveProperty* p = static_cast<AdaptiveProperty*>(property);

        typedef boost::tokenizer<
            boost::char_separator<char_t>,
            String::const_iterator, String> Tokenizer;
        static boost::char_separator<char_t> sep(" ,");
        Tokenizer tok(value, sep);
        Tokenizer::iterator i = tok.begin();
        Color v;
        if (i != tok.end())
        {
            v.r_ = tod_atoi((i++)->c_str());
            if (i != tok.end())
            {
                v.g_ = tod_atoi((i++)->c_str());
                if (i != tok.end())
                {
                    v.b_ = tod_atoi((i++)->c_str());
                    if (i != tok.end())
                        v.a_ = tod_atoi((i++)->c_str());
                }
            }
        }
        
        p->set(object, v);
    }

private:
    String str_;
};


//-----------------------------------------------------------------------------
ToString::ToString()
{
    static BoolStringConverter bool_sc;
    addConverter(&bool_sc);

    static IntStringConverter int_sc;
    addConverter(&int_sc);

    static UnsignedIntStringConverter unsignedint_sc;
    addConverter(&unsignedint_sc);

    static Int64StringConverter int64_sc;
    addConverter(&int64_sc);

    static UnsignedInt64StringConverter unsignedint64_sc;
    addConverter(&unsignedint64_sc);

    static FloatStringConverter float_sc;
    addConverter(&float_sc);

    static DoubleStringConverter double_sc;
    addConverter(&double_sc);

    static StringStringConverter string_sc;
    addConverter(&string_sc);

    static NameStringConverter name_sc;
    addConverter(&name_sc);

    static UriStringConverter uri_sc;
    addConverter(&uri_sc);

    static Vector3StringConverter vector3_sc;
    addConverter(&vector3_sc);

    static ColorStringConverter color_sc;
    addConverter(&color_sc);
}


//-----------------------------------------------------------------------------
ToString::~ToString()
{
    // empty
}


//-----------------------------------------------------------------------------
void ToString::addConverter(StringConverter* sc)
{
    converters_[sc->getTypeId()] = sc;
}


//-----------------------------------------------------------------------------
const char_t* ToString::getTypeKeyword(const Property* property) const
{
    StringConverters::const_iterator find_iter =
        converters_.find(property->getType());
    if (converters_.end() == find_iter)
        return "";
    return find_iter->second->getTypeKeyword();
}


//-----------------------------------------------------------------------------
const String& ToString::toString(Object* object, Property* property)
{
    StringConverters::iterator find_iter =
        converters_.find(property->getType());
    if (converters_.end() == find_iter)
    {
        static String empty;
        return empty;
    }
    return find_iter->second->toString(object, property);
}


//-----------------------------------------------------------------------------
void ToString::fromString
(Object* object, Property* property, const String& value)
{
    StringConverters::iterator find_iter =
        converters_.find(property->getType());
    if (converters_.end() == find_iter)
        return;
    return find_iter->second->fromString(object, property, value);
}
