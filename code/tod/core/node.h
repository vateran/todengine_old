#ifndef TOD_CORE_OBJECT_NODE_H
#define TOD_CORE_OBJECT_NODE_H
/**
    @ingroup TodCoreObject
    @class tod::core::Node
    @brief
*/

#include <map>
#include <stack>
#include "tod/core/type.h"
#include "tod/core/object.h"
#include "tod/core/path.h"
#include "tod/core/ref.h"

namespace tod
{
namespace core
{
    class Node : public Object
    {
    public:
        DECLARE_CLASS(Node, Object);

    public:
        typedef Ref<Node> RefNode;
        typedef std::map<Name, RefNode> Nodes;
        typedef Nodes::iterator NodeIterator;
        typedef Nodes::const_iterator ConstNodeIterator;

    public:
        Node();
        virtual~Node();

        int addRef();
        int release();
        int getRef() const;

        void setName(const name_t* name);
        void setName(const Name& name);
        const Name& getName() const;
        Path getAbsolutePath();

        Node* getParent();
        void attach(Node* child);
        NodeIterator detach();
        template <typename DERIVED>
        void clearChildren();
        Node* findChild(const name_t* name);
        Node* findChild(const String& name);
        Node* relativeNode(const Path& path);

        size_t getNumChildren() const;
        NodeIterator firstChildNode();
        NodeIterator lastChildNode();
        ConstNodeIterator firstChildNode() const;
        ConstNodeIterator lastChildNode() const;

        virtual void onAddNode(Node* node);
        virtual void onRemoveNode(Node* node);

        virtual bool trigger();

    public:
        static void bindMethod();
        static void bindProperty();

    private:
        int refCount_;
        Node* parent_;
        Name name_;
        Nodes children_;

    private:
        friend class Kernel;
    };

#include "tod/core/node.inl"

}
}

#endif // TOD_CORE_OBJECT_NODE_H
