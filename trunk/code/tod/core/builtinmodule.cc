#include "tod/core/builtinmodule.h"

#include "tod/core/node.h"
#include "tod/core/linknode.h"

using namespace tod::core;

//-----------------------------------------------------------------------------
BuiltinModule::BuiltinModule(const name_t* name):
Module(name, 0, 0)
{
    addType(STRING("Object"), &Object::TYPE);
    addType(STRING("Node"), &Node::TYPE);
    addType(STRING("LinkNode"), &LinkNode::TYPE);
}

//-----------------------------------------------------------------------------
BuiltinModule::~BuiltinModule()
{
}
