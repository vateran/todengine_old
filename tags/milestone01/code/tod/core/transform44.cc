#include "tod/core/transform44.h"

using namespace tod;

//-----------------------------------------------------------------------------
Transform44::Transform44()
{
    matrix_.identity();
    scaling_.set(1, 1, 1);
}


//-----------------------------------------------------------------------------
const Matrix44& Transform44::getMatrix() const
{
    if (flags_[FLAG_LOCKED])
    {
        return matrix_;
    }
    else if (flags_[FLAG_DIRTY])
    {
        matrix_.identity();
        if (flags_[FLAG_HASSCALEPIVOT])
            matrix_.translate(-scalePivot_);
        matrix_.scale(scaling_);
        if (flags_[FLAG_HASSCALEPIVOT])
            matrix_.translate(scalePivot_);
        if (flags_[FLAG_HASROTATEPIVOT])
            matrix_.translate(-rotatePivot_);
        if (flags_[FLAG_USEEULER])        
            matrix_.eulerRotate(
                eulerRotation_.y_, eulerRotation_.z_, eulerRotation_.x_);
        else
            matrix_.rotateQuaternion(quaternion_);
        if (flags_[FLAG_HASROTATEPIVOT])
            matrix_.translate(rotatePivot_);
        matrix_.translate(translation_);

        flags_[FLAG_DIRTY] = false;
    }
    return matrix_;
}
