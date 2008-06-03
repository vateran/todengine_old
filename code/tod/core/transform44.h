#ifndef TOD_CORE_TYPE_TRANSFORM44_H
#define TOD_CORE_TYPE_TRANSFORM44_H
/**
    @ingroup TodCoreType
    @class tod::Transform44
    @brief Information of 4x4 Transformation
*/

#include <bitset>
#include "tod/core/matrix44.h"

namespace tod
{
    class Transform44
    {
    public:
        enum Flag
        {
            FLAG_DIRTY                      = (1<<0),
            FLAG_USEEULER                   = (1<<1),
            FLAG_HASROTATEPIVOT             = (1<<2),
            FLAG_HASROTATEPIVOTTRANSLATION  = (1<<3),
            FLAG_HASSCALEPIVOT              = (1<<4),
            FLAG_LOCKED                     = (1<<5),

            FLAG_MAX,
        };

    public:
        Transform44();

        /**
            @brief setter
        */
        //@{
        void setTranslation(const Vector3& translation);
        void setTranslation(real_t x, real_t y, real_t z);
        void setEulerRotation(const Vector3& rotation);
        void setEulerRotation(real_t x, real_t y, real_t z);
        void setRotation(const Quaternion& q);
        void setScaling(const Vector3& scaling);
        void setScaling(real_t x, real_t y, real_t z);

        void translate(const Vector3& translation);
        void translate(real_t x, real_t y, real_t z);
        void rotate(const Vector3& r);
        void rotate(real_t x, real_t y, real_t z);
        void scale(const Vector3& scaling);
        void scale(real_t x, real_t y, real_t z);

        void translateX(real_t x);
        void translateY(real_t y);
        void translateZ(real_t z);
        void eulerRotateX(real_t x);
        void eulerRotateY(real_t y);
        void eulerRotateZ(real_t z);

        void setRotatePivot(const Vector3& p);
        void setRotatePivot(real_t x, real_t y, real_t z);
        void setRotatePivotTranlsation(const Vector3& p);
        void setRotatePivotTranlsation(real_t x, real_t y, real_t z);
        void setScalePivot(const Vector3& p);
        void setScalePivot(real_t x, real_t y, real_t z);

        void setMatrix(const Matrix44& m);

        void setTx(real_t x);
        void setTy(real_t y);
        void setTz(real_t z);
        void setEulerRx(real_t x);
        void setEulerRy(real_t y);
        void setEulerRz(real_t z);
        void setSx(real_t x);
        void setSy(real_t y);
        void setSz(real_t z);

        void setLock(bool b);
        //@}

        /**
            @brief getter
        */
        //@{
        const Vector3& getTranslation() const;
        const Vector3& getEulerRotation() const;
        const Quaternion& getRotation() const;
        const Vector3& getScaling() const;

        const Vector3& getRotatePivot() const;
        const Vector3& getRotatePivotTranlsation() const;
        const Vector3& getScalePivot() const;

        const Matrix44& getMatrix() const;

        real_t getTx() const;
        real_t getTy() const;
        real_t getTz() const;
        real_t getEulerRx() const;
        real_t getEulerRy() const;
        real_t getEulerRz() const;
        real_t getSx() const;
        real_t getSy() const;
        real_t getSz() const;

        bool isLock() const;
        //@}

    private:
        mutable Vector3 translation_;
        mutable Vector3 eulerRotation_;
        mutable Quaternion quaternion_;
        mutable Vector3 scaling_;
        mutable Vector3 rotatePivot_;
        mutable Vector3 rotatePivotTranslation_;
        mutable Vector3 scalePivot_;
        mutable Matrix44 matrix_;
        mutable std::bitset<FLAG_MAX> flags_;
    };

#include "tod/core/transform44.inl"

}

#endif // TOD_CORE_TYPE_TRANSFORM44_H
