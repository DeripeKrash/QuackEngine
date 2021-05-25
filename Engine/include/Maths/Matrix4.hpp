#ifndef QUACKENGINE_MATRIX4_HPP
#define QUACKENGINE_MATRIX4_HPP

#include "Maths/Vector4.hpp"
#include <iostream>

namespace Maths
{
    struct Matrix4
    {
        union
        {
            float e[16]{0};
            Vector4f v[4];
        };

        static Matrix4 Identity();
        static Matrix4 Scale(float s);
        static Matrix4 Scale(const Vector3f &v);
        static Matrix4 Translate(const Vector3f &v);
        static Matrix4 RotateX(float angle);
        static Matrix4 RotateY(float angle);
        static Matrix4 RotateZ(float angle);
        static Matrix4 Rotation(const Vector3f &rotation);
        static Matrix4 AxisRotation(float angle, const Vector3f &axis);
        static Matrix4 Perspective(const int &width,
                                   const int &height,
                                   float near,
                                   float far,
                                   float fov);
        static Matrix4 OrthoMatrix(const int &width,
                                   const int &height,
                                   float near,
                                   float far);

        static Matrix4 ViewportMatrix(const int &x,
                                      const int &y,
                                      const int &width,
                                      const int &height);

        static Matrix4 LookAtMatrix(const Vector3f& eye, const Vector3f& target, const Vector3f& angleZ);
        static Matrix4 LookAtMatrixCamera(const Vector3f& eye, const Vector3f& target, const Vector3f& angleZ);

        Matrix4 GetTranspose() const;
        float GetDeterminant() const;
        Matrix4 GetInvert() const;

        Matrix4 operator*(const Matrix4 &m);
        Matrix4 &operator*=(const Matrix4 &m);
        Matrix4 operator*(float f);
        Vector4f operator*(const Vector4f &v) const;
        Matrix4 operator+(const Matrix4 &m2);
    };
#include "Maths/Matrix4.inl"
}


#endif // QUACKENGINE_MATRIX4_HPP