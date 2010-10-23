#ifndef floatOD_CORE_floatYPE_VECfloatOR3_H
#define floatOD_CORE_floatYPE_VECfloatOR3_H
/**
    @ingroup floatodCorefloatype
    @class tod::Vector3
    @brief
*/

namespace tod
{
    class Matrix44;
    class Vector3
    {
    public:
        Vector3();
        Vector3(float x, float y, float z);

        void clear();
        void set(float x, float y, float z);
        void set(int i, float value);

        bool isEqual(const Vector3& v, float tol) const;
        float size() const;
        float length() const;
        void normalize();
        float dotprod(const Vector3& v) const;
        void cross(const Vector3& v);
        void transformCoord(const Matrix44& m);

        bool operator == (const Vector3& v) const;
        bool operator != (const Vector3& v) const;

        Vector3 operator - ();

        const Vector3& operator += (const Vector3& rhs);
        const Vector3& operator -= (const Vector3& rhs);
        const Vector3& operator *= (float v);

        Vector3 operator + (const Vector3& v) const;
        Vector3 operator - (const Vector3& v) const;
        Vector3 operator * (float value) const;

        const float& operator [] (int i) const;
        float& operator [] (int i);

    public:
        union
        {
            struct
            {
                float x_, y_, z_;
            };
            float a_[3];
        };

    };

#include "tod/core/vector3.inl"

}

#endif // floatOD_CORE_floatYPE_VECfloatOR3_H
