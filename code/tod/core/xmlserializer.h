#ifndef TOD_CORE_SERIALIZER_XMLSERIALIZER_H
#define TOD_CORE_SERIALIZER_XMLSERIALIZER_H
/**
    @ingroup TodCoreSerializer
    @class tod::XmlSerializer
    @brief
*/

#include "tod/core/define.h"
#include "tod/core/serializer.h"

namespace tod
{
    class Object;
    class XmlSerializer : public Serializer
    {
    public:
        XmlSerializer();

        override bool serialize(const Uri& uri, Object* object);
        override Object* deserialize(const Uri& uri, const Name& name);

    private:
        bool serialize_class_hierarchy(Object* object, String& data);
        void begin_tag(Object* object, String& data, bool has_child);
        void end_tag(Object* object, String& data, bool has_child);
        void serialize_properties(Object* object, String& data);
        void insert_tab(int depth, String& data);

    private:
        int depth_;
    };
}

#endif // TOD_CORE_SERIALIZER_XMLSERIALIZER_H
