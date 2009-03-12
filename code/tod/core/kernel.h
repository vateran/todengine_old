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
        typedef std::map<Name, Module*> Types;
        typedef std::map<Name, Module*> Modules;

    public:
        Kernel();
        ~Kernel();

        Object* create(const String& type_name);
        Node* create(const String& type_name, const Path& path);
        Node* lookup(const Path& path);

        void pushCwn(Node* object);
        Node* popCwn();
        Node* getCwn();

        void addModule(Module* module);
        Module* findModule(const String& name);
        Modules::iterator firstModule();
        Modules::iterator lastModule();
        Modules::const_iterator firstModule() const;
        Modules::const_iterator lastModule() const;
        size_t getNumModules() const;

        void addType(const String& type_name, Module* module);

        Node* getRoot();

    private:        
        typedef std::stack<Node::RefNode> Cwn;

    private:
        Node* create_node(const String& type_name, const String& name);

    private:
        Node::RefNode root_;
        Types types_;
        Modules modules_;
        Cwn cwn_;
    };

#include "tod/core/kernel.inl"

}

#endif // TOD_CORE_KERNEL_KERNEL_H
