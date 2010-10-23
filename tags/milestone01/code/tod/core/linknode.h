#ifndef TOD_CORE_OBJECT_LINKNODE_H
#define TOD_CORE_OBJECT_LINKNODE_H
/**
    @ingroup TodCoreObject
    @class tod::LinkNode
    @brief
*/

#include <map>
#include "tod/core/node.h"

namespace tod
{
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

        void update();

    private:
        struct UpdatePropertyBase
        {
            virtual void update(
                Object* from, Property* from_p,
                Object* to, Property* to_p)=0;
        };
        template <typename T>
        struct UpdatePropertyEqualType : public UpdatePropertyBase
        {
            override void update(
                Object* from, Property* from_p,
                Object* to, Property* to_p);
        };
        template <typename FROM, typename TO>
        struct UpdateProperty : public UpdatePropertyBase
        {
            override void update(
                Object* from, Property* from_p,
                Object* to, Property* to_p);
        };
        class PropertyTypeId
        {
        public:
            PropertyTypeId(type_id from, type_id to);
            bool operator < (const PropertyTypeId& rhs) const;
            type_id from_;
            type_id to_;
        };
        struct UpdatePropertyServer
        {
        public:
            UpdatePropertyServer();
            ~UpdatePropertyServer();
            UpdatePropertyBase* find(type_id from, type_id to);
            typedef std::map
                <PropertyTypeId, UpdatePropertyBase*> UpdateProperties;
            UpdateProperties updateProperties_;
        };

    private:
        Ref<Node> from_;
        Property* fromProperty_;
        Ref<Node> to_;
        Property* toProperty_;
        UpdatePropertyBase* updateProperty_;

    private:
        static UpdatePropertyServer s_updatePropertyServer_;
    };
}

#endif // TOD_CORE_OBJECT_LINKNODE_H
