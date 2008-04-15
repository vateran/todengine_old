#ifndef TOD_CORE_TYPE_COLOR_H
#define TOD_CORE_TYPE_COLOR_H
/**
    @ingroup TodCoreType
    @class tod::core::Color
    @brief 
*/

#include "tod/core/primitivetype.h"

namespace tod
{
namespace core
{
    class Color
    {
    public:
        Color();
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        void set(int i, uint8_t v)
        {
            array_[i] = v;
        }
        uint8_t get(int i)
        {
            return array_[i];
        }

        const uint8_t& operator [] (int i) const
        {
            return array_[i];
        }
        uint8_t& operator [] (int i)
        {
            return array_[i];
        }

    public:
        union
        {
            struct
            {   
                uint8_t b_;
                uint8_t g_;
                uint8_t r_;
                uint8_t a_;
            };
            uint8_t array_[4];
            uint32_t data_;
        };
    };
}
}

#endif // TOD_CORE_TYPE_COLOR_H
