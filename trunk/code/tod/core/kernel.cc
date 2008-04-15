#include "tod/core/kernel.h"

#include "tod/core/assert.h"
#include "tod/core/module.h"
#include "tod/core/builtinmodule.h"

using namespace tod::core;

//-----------------------------------------------------------------------------
Kernel::Kernel()
{
    addModule(new BuiltinModule(STRING("Builtin")));
    root_ = create_node(STRING("Node"), STRING(""));
    pushCwn(root_);    
}


//-----------------------------------------------------------------------------
Kernel::~Kernel()
{
    while (cwn_.size())
        popCwn();
    Module* module = findModule(STRING("Builtin"));
    tod_assert(module);
    delete module;
}


//-----------------------------------------------------------------------------
Object* Kernel::create(const typename_t* type_name)
{
    Types::iterator find_iter = types_.find(type_name);
    if (types_.end() == find_iter)
        return 0;
    return find_iter->second->create(type_name);
}


//-----------------------------------------------------------------------------
Node* Kernel::create(const typename_t* type_name, const Path& path)
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
                new_node = create_node(STRING("Node"), *token);
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
    if (path == STRING("/"))
        return root_;
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
    
    module->initialize();
    modules_.insert(Modules::value_type(module->getName(), module));

    // insert type names in module to Kernel::types_ for Object creation
    for (Module::Types::iterator iter = module->firstType();
         iter != module->lastType(); ++iter)    
        types_.insert(Types::value_type(iter->first, module));
}


//-----------------------------------------------------------------------------
Module* Kernel::findModule(const name_t* name)
{
    Modules::iterator find_iter = modules_.find(name);
    if (modules_.end() == find_iter)
        return 0;
    return find_iter->second;
}


//-----------------------------------------------------------------------------
Node* Kernel::create_node(const Name& type_name, const Name& name)
{
    Types::iterator find_iter = types_.find(type_name);
    if (types_.end() == find_iter)
        return 0;
    Node* new_node = static_cast<Node*>(
        find_iter->second->create(type_name));
    if (0 == new_node)
        return 0;
    new_node->setName(name);
    new_node->refCount_ = 0;
    return new_node;
}
