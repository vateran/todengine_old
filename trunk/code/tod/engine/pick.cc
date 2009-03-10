#include "tod/engine/pick.h"

using namespace tod;
using namespace tod::engine;

//-----------------------------------------------------------------------------
bool Pick::pickObjects
(Node* root, const Vector3& origin, const Vector3& dir)
{
    result_.clear();



    return true;
}


//-----------------------------------------------------------------------------
const Pick::Result& Pick::getResult() const
{
    return result_;
}


//-----------------------------------------------------------------------------
Pick::Record* Pick::Result::get(uint32_t index)
{
    uint32_t count = 0;
    for (Records::iterator i = records_.begin();
         i != records_.end(); ++i, ++count)
    {
        if (count == index)
            return &*i;
    }
    return 0;
}

//-----------------------------------------------------------------------------
void Pick::Result::clear()
{
    records_.clear();
}


//-----------------------------------------------------------------------------
void Pick::Result::sort()
{
}
