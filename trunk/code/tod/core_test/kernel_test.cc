#include "tod/core_test/kernel_test.h"

#include "tod/core/path.h"
#include "tod/core/kernel.h"
#include "tod/core/object.h"
#include "tod/core/type.h"
#include "tod/core/module.h"
#include "tod/core/cwnguard.h"

using namespace tod;

//-----------------------------------------------------------------------------
class Sorceress : public Node
{
public:
    Sorceress()
    {
        CwnGuard guard(this);
    }
    DECLARE_CLASS(Sorceress, Node);
};
IMPLEMENT_CLASS(Sorceress, Node);
void initialize_module(Module* module)
{
    module->addType(Kernel::instance(), "Sorceress", &Sorceress::TYPE);
}
Module TestModule("TestModule", initialize_module, 0);

//-----------------------------------------------------------------------------
void KernelTestCase::test_Path()
{
    Path path("/test");
    TODUNIT_ASSERT(path.isAbsolute());
    TODUNIT_ASSERT(!path.isRelative());
    path = "test";
    TODUNIT_ASSERT(!path.isAbsolute());
    TODUNIT_ASSERT(path.isRelative());

    path = "/test1/test2/test3/test4";
    Path::iterator iter = path.begin();
    TODUNIT_ASSERT(*iter == "test1");
    ++iter;
    TODUNIT_ASSERT(*iter == "test2");
    ++iter;
    TODUNIT_ASSERT(*iter == "test3");
    ++iter;
    TODUNIT_ASSERT(*iter == "test4");
    ++iter;
}


//-----------------------------------------------------------------------------
void KernelTestCase::test_CreateObject()
{
    Kernel::instance()->addModule(&TestModule);

    Sorceress* sorceress = DOWN_CAST<Sorceress*>
        (TestModule.create("Sorceress"));
    TODUNIT_ASSERT(sorceress);
    delete sorceress;
    sorceress = 0;

    // creation
    sorceress = DOWN_CAST<Sorceress*>(
        Kernel::instance()->create("Sorceress",
            "/usr/scene/sorceress"));
    TODUNIT_ASSERT(sorceress);
    TODUNIT_ASSERT(sorceress->getAbsolutePath() == "/usr/scene/sorceress");
    TODUNIT_ASSERT(sorceress->getName() == "sorceress");

    // repeat creation
    Sorceress* sorceress1 = DOWN_CAST<Sorceress*>(
        Kernel::instance()->create("Sorceress",
        "/usr/scene/sorceress"));
    TODUNIT_ASSERT(sorceress == sorceress1);

    sorceress->detach();
}


//-----------------------------------------------------------------------------
void KernelTestCase::test_Lookup()
{
    Sorceress* sorceress = DOWN_CAST<Sorceress*>(
        Kernel::instance()->create("Sorceress",
            "/usr/scene/sorceress"));
    TODUNIT_ASSERT(sorceress);
    TODUNIT_ASSERT(sorceress == Kernel::instance()->lookup("/usr/scene/sorceress"));
    TODUNIT_ASSERT(Kernel::instance()->lookup("/usr/scene/sorceress") ==
        Kernel::instance()->lookup("usr/scene/sorceress"));
    TODUNIT_ASSERT(sorceress->getParent() == Kernel::instance()->lookup("/usr/scene"));
    TODUNIT_ASSERT(sorceress->getParent() == Kernel::instance()->lookup("usr/scene"));
    TODUNIT_ASSERT(Kernel::instance()->getRoot() == Kernel::instance()->lookup("/"));

    // current working node
    Node* scene = Kernel::instance()->lookup("usr/scene");
    Kernel::instance()->pushCwn(scene);
    TODUNIT_ASSERT(sorceress == Kernel::instance()->lookup("sorceress"));
    TODUNIT_ASSERT(Kernel::instance()->getRoot() == Kernel::instance()->lookup("/"));
    TODUNIT_ASSERT(Kernel::instance()->popCwn() == scene);

    TODUNIT_ASSERT(sorceress->getParent() == sorceress->relativeNode(".."));
    TODUNIT_ASSERT(sorceress == Kernel::instance()->getRoot()->relativeNode("usr/scene/sorceress"));

    sorceress->detach();    
}
