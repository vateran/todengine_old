#include "tod/core/kernel.h"

#include "tod/core/assert.h"
#include "tod/core/module.h"
#include "tod/core/builtinmodule.h"

using namespace tod;

//-----------------------------------------------------------------------------
Kernel::Kernel()
{
    String::initializeEncoding();

    addModule(new BuiltinModule(this, "Builtin"));
    root_ = create_node("Node", "");
    pushCwn(root_);
}


//-----------------------------------------------------------------------------
Kernel::~Kernel()
{
    while (cwn_.size())
        popCwn();
    root_.release();

    for (Modules::iterator i = modules_.begin();
         i != modules_.end(); ++i)
        i->second->finalize();
    Module* module = findModule("Builtin");
    tod_assert(module);
    delete module;

    modules_.clear();
    types_.clear();

    String::finalizeEncoding();
}


//-----------------------------------------------------------------------------
Object* Kernel::create(const String& type_name)
{
    Types::iterator find_iter = types_.find(type_name);
    if (types_.end() == find_iter)
        return 0;
    Object* new_obj = find_iter->second->create(type_name);
    Node* new_node = dynamic_cast<Node*>(new_obj);
    if (new_node)
        --new_node->refCount_;
    return new_obj;
}


//-----------------------------------------------------------------------------
Node* Kernel::create(const String& type_name, const Path& path)
{
    Node* cur;
    if (path.isAbsolute())
        cur = root_;
    else
        cur = cwn_.top();
    for (Path::iterator token = path.begin(); token != path.end(); ++token)
    {
        Node* child = cur->findChild(*token);
        if (0 == child)
        {
            Node* new_node;
            Path::iterator e = token;
            if (++e == path.end())
                new_node = create_node(type_name, *token);
            else
                new_node = create_node("Node", *token);
            if (0 == new_node)
                return 0;
            cur->attach(new_node);
            cur = new_node;
        }
        else
            cur = child;
    }

    return cur;
}


//-----------------------------------------------------------------------------
Node* Kernel::lookup(const Path& path)
{
    if (path == "/")
        return root_;
    if (path.isAbsolute())
        return root_->relativeNode(path);
    return cwn_.top()->relativeNode(path);
}


//-----------------------------------------------------------------------------
void Kernel::pushCwn(Node* node)
{
    cwn_.push(node);
}


//-----------------------------------------------------------------------------
Node* Kernel::popCwn()
{
    tod_assert(cwn_.size() > 0);
    Node* node = cwn_.top();
    cwn_.pop();
    return node;
}


//-----------------------------------------------------------------------------
Node* Kernel::getCwn()
{
    return cwn_.top();
}


//-----------------------------------------------------------------------------
void Kernel::addModule(Module* module)
{
    if (0 == module)
        return;
    
    modules_.insert(Modules::value_type(module->getName(), module));
    module->initialize();
}


//-----------------------------------------------------------------------------
Module* Kernel::findModule(const String& name)
{
    Modules::iterator find_iter = modules_.find(name);
    if (modules_.end() == find_iter)
        return 0;
    return find_iter->second;
}


//-----------------------------------------------------------------------------
void Kernel::addType(const String&   type_name, Module* module)
{
    // insert type names in module to Kernel::types_ for Object creation
    types_.insert(Types::value_type(type_name, module));
}


//-----------------------------------------------------------------------------
Node* Kernel::create_node(const String& type_name, const String& name)
{
    Types::iterator find_iter = types_.find(type_name);
    if (types_.end() == find_iter)
        return 0;
    Node* new_node = static_cast<Node*>(
        find_iter->second->create(type_name));
    if (0 == new_node)
        return 0;
    new_node->setName(name);
    --new_node->refCount_;
    return new_node;
}
