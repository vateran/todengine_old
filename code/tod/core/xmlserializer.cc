#include "tod/core/xmlserializer.h"

#include "tod/core/node.h"
#include "tod/core/resource.h"

using namespace tod;

//-----------------------------------------------------------------------------
XmlSerializer::XmlSerializer():
depth_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
bool XmlSerializer::serialize(const Uri& uri, Object* object)
{
    depth_ = 0;
    String data;
    data.reserve(1024);
    data = STRING("<?xml version=\"1.0\" encoding=\"euc-kr\" ?>\n");
    if (!serialize_class_hierarchy(object, data))
        return false;
    
    tod::Resource resource(uri);
    if (!resource.open(
        tod::Resource::OPEN_WRITE |
        tod::Resource::OPEN_BINARY))
        return false;

    resource.write(data.toAnsiString().c_str(), data.size());
    return true;
}


//-----------------------------------------------------------------------------
Object* XmlSerializer::deserialize(const Uri& uri, const Name& name)
{
    return 0;
}


//-----------------------------------------------------------------------------
bool XmlSerializer::serialize_class_hierarchy(Object* object, String& data)
{
    // inform to object that begin of serializing
    SerializerEvent* event = dynamic_cast<SerializerEvent*>(object);
    if (event)
        event->beginSerialize();

    bool has_child = false;
    Node* node = dynamic_cast<Node*>(object);
    if (node)
        has_child = ((node->getNumChildren()==0)?false:true);

    // begin xml tag
    begin_tag(object, data, has_child);

    if (has_child)
    {
        for (Node::NodeIterator i = node->firstChildNode();
             i != node->lastChildNode(); ++i)
        {
            if (!serialize_class_hierarchy(i->second, data))
                return false;
        }
    }

    // end xml tag
    end_tag(object, data, has_child);

    // inform to object that end of serializing
    if (event)
        event->endSerialize();
    return true;
}


//-----------------------------------------------------------------------------
void XmlSerializer::begin_tag(Object* object, String& data, bool has_child)
{
    insert_tab(depth_, data);
    ++depth_;

    data += STRING("<");
    data += object->getType().getName();
    serialize_properties(object, data);
    if (has_child)
        data += STRING(">\n");
    else
        data += STRING(" />\n");
}


//-----------------------------------------------------------------------------
void XmlSerializer::end_tag(Object* object, String& data, bool has_child)
{
    --depth_;
    if (!has_child)
        return;
    insert_tab(depth_, data);
    data += STRING("</");
    data += object->getType().getName();
    data += STRING(">\n");
}


//-----------------------------------------------------------------------------
void XmlSerializer::serialize_properties(Object* object, String& data)
{
    Type* type = &object->getType();
    while (type)
    {
        for (Properties::iterator p = type->firstProperty();
            p != type->lastProperty(); ++p)
        {
            Property* prop = p->second;
            if (prop->isReadOnly())
                continue;
            data += STRING(" ");
            data += prop->getName();
            data += STRING("=\"");
            data += prop->toString(object);
            data += STRING("\"");
        }

        type = type->getBase();
    }
}


//-----------------------------------------------------------------------------
void XmlSerializer::insert_tab(int depth, String& data)
{
    for (int i = 0; i < depth; ++i)
        data += STRING("    ");
}
