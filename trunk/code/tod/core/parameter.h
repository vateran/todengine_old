#ifndef TOD_CORE_OBJECT_PARAMETER_H
#define TOD_CORE_OBJECT_PARAMETER_H
/**
    @ingroup TodCoreObject
    @class tod::Parameter
    @brief
*/

#include "tod/core/variables.h"

namespace tod
{
    class Parameter
    {
    public:
        void clear();

        Variables* in();
        Variables* out();

    private:
        Variables in_;
        Variables out_;
    };

#include "tod/core/parameter.inl"

}

#endif // TOD_CORE_OBJECT_PARAMETER_H
