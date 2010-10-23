#ifndef TOD_CORE_SERIALIZER_XMLSERIALIZER_H
#define TOD_CORE_SERIALIZER_XMLSERIALIZER_H
/**
    @ingroup TodCoreSerializer
    @class tod::XmlSerializer
    @brief
*/

#include "tod/core/define.h"
#include "tod/core/serializer.h"

class TiXmlNode;

namespace tod
{
    class Object;
    class XmlSerializer : public Serializer
    {
    public:
        XmlSerializer();

        override bool serialize(const Uri& uri, Object* object);
        override Object* deserialize(Node* parent, const Uri& uri, const char_t* name);

    private:
        Object* deserialize_node(TiXmlNode* node, const char_t* name);
        bool serialize_class_hierarchy(Object* object, String& data);
        void begin_tag(Object* object, String& data, bool has_child);
        void end_tag(Object* object, String& data, bool has_child);
        void serialize_properties(Object* object, String& data);
        void insert_tab(int depth, String& data);

    private:
        int depth_;
        Object* desObj_;
    };
}

#endif // TOD_CORE_SERIALIZER_XMLSERIALIZER_H
