#include "tod/core/builtinmodule.h"

#include "tod/core/node.h"
#include "tod/core/linknode.h"
#include "tod/core/resourcemanager.h"
#include "tod/core/resourcestorage.h"
#include "tod/core/resourceentry.h"

using namespace tod;

//-----------------------------------------------------------------------------
BuiltinModule::BuiltinModule(Kernel* kernel, const name_t* name):
Module(name, 0, 0)
{
    addType(kernel, STRING("Object"), &Object::TYPE);
    addType(kernel, STRING("Node"), &Node::TYPE);
    addType(kernel, STRING("LinkNode"), &LinkNode::TYPE);
    addType(kernel, STRING("ResourceManager"), &ResourceManager::TYPE);
    addType(kernel, STRING("ResourceStorage"), &ResourceStorage::TYPE);
    addType(kernel, STRING("ResourceEntry"), &ResourceEntry::TYPE);
}

//-----------------------------------------------------------------------------
BuiltinModule::~BuiltinModule()
{
}
