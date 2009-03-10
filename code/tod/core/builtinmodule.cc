#include "tod/core/builtinmodule.h"

#include "tod/core/node.h"
#include "tod/core/linknode.h"
#include "tod/core/resourcemanager.h"
#include "tod/core/resourcestorage.h"
#include "tod/core/resourceentry.h"

using namespace tod;

//-----------------------------------------------------------------------------
BuiltinModule::BuiltinModule(Kernel* kernel, const char_t* name):
Module(name, 0, 0)
{
    addType(kernel, "Object", &Object::TYPE);
    addType(kernel, "Node", &Node::TYPE);
    addType(kernel, "LinkNode", &LinkNode::TYPE);
    addType(kernel, "ResourceManager", &ResourceManager::TYPE);
    addType(kernel, "ResourceStorage", &ResourceStorage::TYPE);
    addType(kernel, "ResourceEntry", &ResourceEntry::TYPE);
}

//-----------------------------------------------------------------------------
BuiltinModule::~BuiltinModule()
{
}
