#include "tod/core/plane.h"

using namespace tod;

//-----------------------------------------------------------------------------
Plane::Plane():
a_(0), b_(0), c_(0), d_(0)
{
    // empty
}


//-----------------------------------------------------------------------------
Plane::Plane(real_t a, real_t b, real_t c, real_t d):
a_(a), b_(b), c_(c), d_(d)
{
    // empty
}
