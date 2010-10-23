#include "tod/core/builtinmodule.h"

#include "tod/core/node.h"
#include "tod/core/linknode.h"
#include "tod/core/timenode.h"
#include "tod/core/triggerserver.h"
#include "tod/core/timeserver.h"
#include "tod/core/resourcemanager.h"
#include "tod/core/resourcestorage.h"
#include "tod/core/resourceentry.h"

using namespace tod;

//-----------------------------------------------------------------------------
BuiltinModule::BuiltinModule(Kernel* kernel, const String& name):
Module(name, 0, 0)
{
    addType(kernel, "Object", &Object::TYPE);
    addType(kernel, "Node", &Node::TYPE);
    addType(kernel, "LinkNode", &LinkNode::TYPE);
    addType(kernel, "TimeNode", &TimeNode::TYPE);
    addType(kernel, "ResourceManager", &ResourceManager::TYPE);
    addType(kernel, "ResourceStorage", &ResourceStorage::TYPE);
    addType(kernel, "ResourceEntry", &ResourceEntry::TYPE);
    addType(kernel, "TimeServer", &TimeServer::TYPE);
    addType(kernel, "TriggerServer", &TriggerServer::TYPE);

    TimeServer::setSingletonPath("/sys/server/time", false);
	TriggerServer::setSingletonPath("/sys/server/trigger", false);
}

//-----------------------------------------------------------------------------
BuiltinModule::~BuiltinModule()
{
}
