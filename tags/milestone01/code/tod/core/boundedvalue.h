#ifndef TOD_CORE_TYPE_BOUNDEDVALUE_H
#define TOD_CORE_TYPE_BOUNDEDVALUE_H
/**
    @ingroup TodCoreType
    @class tod::BoundedValue
    @brief 
*/

namespace tod
{
    template <typename T>
    class BoundedValue
    {
    public:        

    private:
        T value_;
        T min_;
        T max_;
    };
}

#endif // TOD_CORE_TYPE_BOUNDEDVALUE_H
