#include "tod/core/xmlserializer.h"

#include "tinyxml/tinyxml.h"
#include "tod/core/exception.h"
#include "tod/core/node.h"
#include "tod/core/resource.h"
#include "tod/core/kernel.h"

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
    data = "<?xml version=\"1.0\" encoding=\"euc-kr\" ?>\n";
    if (!serialize_class_hierarchy(object, data))
        return false;
    
    tod::Resource resource(uri);
    if (!resource.open(
        tod::Resource::OPEN_WRITE |
        tod::Resource::OPEN_BINARY))
        return false;

    resource.write(data, data.size());
    return true;
}


//-----------------------------------------------------------------------------
Object* XmlSerializer::deserialize
(Node* parent, const Uri& uri, const char_t* name)
{
    tod::Resource resource(uri);
    if (!resource.open(
        tod::Resource::OPEN_READ |
        tod::Resource::OPEN_BINARY))
        return false;

    dynamic_buffer_t buffer;
    buffer.resize(resource.size() + 1);
    resource.read(&buffer[0], buffer.size());

    TiXmlDocument doc;
    doc.Parse(&buffer[0]);
    if (doc.Error())
    {
        TOD_THROW_EXCEPTION(0, String("uri[%s]:(%d/%d)\nDescription: %s",
            uri.c_str(),
            doc.ErrorRow(), doc.ErrorCol(), doc.ErrorDesc()));
        return 0;
    }

    if (parent)
        Kernel::instance()->pushCwn(parent);

    desObj_ = 0;
    deserialize_node(doc.FirstChild(), name);

    if (parent)
        Kernel::instance()->popCwn();
    
    return desObj_;
}


//-----------------------------------------------------------------------------
Object* XmlSerializer::deserialize_node(TiXmlNode* node, const char_t* name)
{
    Node* new_node = 0;
    const char_t* change_name = name;
    if (node->Type() == TiXmlNode::ELEMENT)
    {
        TiXmlElement* element = node->ToElement();
        const char* type_name = element->Value();
        const char* node_name = element->Attribute("name");
        if (change_name)
        {
            new_node = Kernel::instance()->
                create(String(type_name).c_str(), change_name);
            change_name = 0;
        }
        else
        {
            new_node = Kernel::instance()->
                create(String(type_name).c_str(), String(node_name));
        }
        
        if (0 == new_node)
        {
            TOD_THROW_EXCEPTION(0,
                String("could not create node(%s,%s)",
                    type_name, node_name));
            return 0;
        }
        if (0 == desObj_)
            desObj_ = new_node;

        Type* type = new_node->getType();
        while (type)
        {
            for (Properties::iterator pi = type->firstProperty();
                 pi != type->lastProperty(); ++pi)
            {
                Property* prop = pi->second;
                if (prop->isReadOnly())
                    continue;
                if (pi->first == "name")
                    continue;
                const char* value =
                    element->Attribute(prop->getName());
                if (value)
                    prop->fromString(new_node, String(value).c_str());
            }
            type = type->getBase();
        }
    }

    if (node->NextSibling() != 0)
        if (0 == deserialize_node(node->NextSibling(), change_name))
            return 0;

    if (new_node)
        Kernel::instance()->pushCwn(new_node);

    if (node->FirstChild() != 0)
        if (0 == deserialize_node(node->FirstChild(), change_name))
            return 0;

    if (new_node)
        Kernel::instance()->popCwn();
    return new_node;
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

    data += "<";
    data += object->getType()->getName();
    serialize_properties(object, data);
    if (has_child)
        data += ">\n";
    else
        data += " />\n";
}


//-----------------------------------------------------------------------------
void XmlSerializer::end_tag(Object* object, String& data, bool has_child)
{
    --depth_;
    if (!has_child)
        return;
    insert_tab(depth_, data);
    data += "</";
    data += object->getType()->getName();
    data += ">\n";
}


//-----------------------------------------------------------------------------
void XmlSerializer::serialize_properties(Object* object, String& data)
{
    std::stack<Type*> t;

    Type* type = object->getType();
    while (type)
    {
        t.push(type);
        type = type->getBase();
    }

    while (t.size())
    {
        Type* type = t.top();
        t.pop();

        for (Properties::iterator p = type->firstProperty();
            p != type->lastProperty(); ++p)
        {
            Property* prop = p->second;
            if (prop->isReadOnly())
                continue;
            data += " ";
            data += prop->getName();
            data += "=\"";
            data += prop->toString(object);
            data += "\"";
        }
    }
}


//-----------------------------------------------------------------------------
void XmlSerializer::insert_tab(int depth, String& data)
{
    for (int i = 0; i < depth; ++i)
        data += "    ";
}
