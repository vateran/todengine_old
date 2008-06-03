#ifndef TOD_CORE_KERNEL_KERNEL_H
#define TOD_CORE_KERNEL_KERNEL_H
/**
    @ingroup TodCoreKernel
    @class tod::Kernel
    @brief 
*/

#include <map>
#include <stack>
#include "tod/core/name.h"
#include "tod/core/node.h"
#include "tod/core/path.h"
#include "tod/core/primitivetype.h"
#include "tod/core/singleton.h"

namespace tod
{
    class Object;
    class Module;
    class Kernel : public Singleton<Kernel>
    {
    public:
        Kernel();
        ~Kernel();

        Object* create(const typename_t* type_name);
        Node* create(const typename_t* type_name, const Path& path);
        Node* lookup(const Path& path);

        void pushCwn(Node* object);
        Node* popCwn();
        Node* getCwn();

        void addModule(Module* module);
        Module* findModule(const name_t* name);

        Node* getRoot();

    private:
        typedef std::map<Name, Module*> Types;
        typedef std::map<Name, Module*> Modules;
        typedef std::stack<Node::RefNode> Cwn;

    private:
        Node* create_node(const Name& type_name, const Name& name);

    private:
        Node::RefNode root_;
        Types types_;
        Modules modules_;
        Cwn cwn_;
    };

#include "tod/core/kernel.inl"

}

#endif // TOD_CORE_KERNEL_KERNEL_H
