#ifndef TOD_CORE_NODE_LINKNODE_H
#define TOD_CORE_NODE_LINKNODE_H
/**
    @ingroup TodCoreObject
    @class tod::LinkNode
    @brief
*/

#include <map>
#include "tod/core/node.h"

namespace tod
{
    class UpdatePropertyBase;
    class LinkNode : public Node
    {
    public:
        LinkNode();
        virtual~LinkNode();
        DECLARE_CLASS(LinkNode, Node);

        void connect(
            Node* from, Property* from_prop,
            Node* to, Property* to_prop);
        void connect(const String& from, const String& to);

        void setFromByStr(const String& from);
        void setToByStr(const String& to);
        const String& getFromStr() const;
        const String& getToStr() const;

        override bool trigger();

        static void bindMethod();
        static void bindProperty();

    private:
        /**
            @brief parse ups(universal property string)
            path:property_name
            ex) /usr/scene:name
        */
        bool parse_ups(const String& ups, Node** node, Property** prop);

    private:
        Ref<Node> from_;
        Property* fromProperty_;
        Ref<Node> to_;
        Property* toProperty_;
        UpdatePropertyBase* updateProperty_;
        String fromStr_;
        String toStr_;

    };
}

#endif // TOD_CORE_NODE_LINKNODE_H
