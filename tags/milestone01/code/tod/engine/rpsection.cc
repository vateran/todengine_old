#include "tod/engine/rpsection.h"

#include "tod/engine/rppass.h"

using namespace tod;
using namespace tod::engine;

IMPLEMENT_CLASS(RpSection, RpBase);

//-----------------------------------------------------------------------------
RpSection::RpSection()
{
    // empty
}


//-----------------------------------------------------------------------------
RpSection::~RpSection()
{
    // empty
}


//-----------------------------------------------------------------------------
void RpSection::addPass(RpPass* pass)
{
    passes_.push_back(pass);
}


//-----------------------------------------------------------------------------
void RpSection::removePass(RpPass* pass)
{
    passes_.erase(std::find(passes_.begin(), passes_.end(), pass));
}


//-----------------------------------------------------------------------------
RpPass* RpSection::getPass(index_t index)
{
    return passes_[index];
}


//-----------------------------------------------------------------------------
uint32_t RpSection::getNumPass() const
{
    return passes_.size();
}


//-----------------------------------------------------------------------------
RpSection::RpPasses::iterator RpSection::firstPass()
{
    return passes_.begin();
}


//-----------------------------------------------------------------------------
RpSection::RpPasses::iterator RpSection::lastPass()
{
    return passes_.end();
}


//-----------------------------------------------------------------------------
RpSection::RpPasses::const_iterator RpSection::firstPass() const
{
    return passes_.begin();
}


//-----------------------------------------------------------------------------
RpSection::RpPasses::const_iterator RpSection::lastPass() const
{
    return passes_.end();
}


//-----------------------------------------------------------------------------
void RpSection::onAddNode(Node* node)
{
    RpPass* pass = dynamic_cast<RpPass*>(node);
    if (pass)
        addPass(pass);
}


//-----------------------------------------------------------------------------
void RpSection::onRemoveNode(Node* node)
{
    RpPass* pass = dynamic_cast<RpPass*>(node);
    if (pass)
        removePass(pass);
}
