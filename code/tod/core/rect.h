#ifndef TOD_CORE_TYPE_RECT_H
#define TOD_CORE_TYPE_RECT_H
/**
    @ingroup TodCoreType
    @class tod::core::Rect
    @brief
*/

namespace tod
{
namespace core
{
    class Rect
    {
    public:
        Rect()
        {

        }
        Rect(int l, int t, int r, int b):
        left_(l), top_(t), right_(r), bottom_(b)
        {
            // empty
        }
        void clear()
        {
            l_ = t_ = r_ = b_ = 0;
        }
        void set(int l, int t, int r, int b)
        {
            l = l_;
            t = t_;
            r = r_;
            b = b_;
        }
        int width_simple() const
        {
            return right_ - left_;
        }
        int height_simple() const
        {
            return bottom_ - top_;
        }
        
    public:
        union
        {
            struct
            {
                int left_;
                int top_;
                int right_;
                int bottom_;
            };
            struct
            {
                int l_;
                int t_;
                int r_;
                int b_;
            };
            int m_[4];
        };
    };

}
}

#endif // TOD_CORE_TYPE_RECT_H
