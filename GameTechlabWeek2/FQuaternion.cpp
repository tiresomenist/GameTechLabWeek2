#include "FQuaternion.h"

FQuaternion FQuaternion::FromAxisAngle(const FVector& Axis, float Radian)
{
    const double Length = std::hypot(double(Axis.X), double(Axis.Y), double(Axis.Z));
    if (!std::isfinite(Length) || Length == 0.0 || !std::isfinite(Radian))
        return {};

    const double HalfAngle = double(Radian) * 0.5;
    const double Scale = std::sin(HalfAngle) / Length;
    return { float(Axis.X * Scale), float(Axis.Y * Scale),
        float(Axis.Z * Scale), float(std::cos(HalfAngle)) };
}
 
FQuaternion FQuaternion::FromEuler(const FVector& EulerRadians)
{
    if (!std::isfinite(EulerRadians.X) || !std::isfinite(EulerRadians.Y)
        || !std::isfinite(EulerRadians.Z))
        return {};

    const FQuaternion QX = FromAxisAngle(FVector(1, 0, 0), EulerRadians.X);
    const FQuaternion QY = FromAxisAngle(FVector(0, 1, 0), EulerRadians.Y);
    const FQuaternion QZ = FromAxisAngle(FVector(0, 0, 1), EulerRadians.Z);
    // Hamilton multiplication reverses the order of the row-vector matrices.
    FQuaternion Result = QX * QY * QZ;
    Result.Normalize();
    return Result;
}

FQuaternion FQuaternion::operator*(const FQuaternion& Other) const
{
    return {
        W * Other.X + X * Other.W + Y * Other.Z - Z * Other.Y,
        W * Other.Y - X * Other.Z + Y * Other.W + Z * Other.X,
        W * Other.Z + X * Other.Y - Y * Other.X + Z * Other.W,
        W * Other.W - X * Other.X - Y * Other.Y - Z * Other.Z
    };
}

void FQuaternion::Normalize()
{
    // Double intermediates avoid overflow/underflow for finite float components.
    const double Length = std::sqrt(double(X) * X + double(Y) * Y
        + double(Z) * Z + double(W) * W);
    if (!std::isfinite(Length) || Length == 0.0)
    {
        *this = FQuaternion{};
        return;
    }
    X = float(X / Length);
    Y = float(Y / Length);
    Z = float(Z / Length);
    W = float(W / Length);
}

FMatrix FQuaternion::ToRotationMatrix() const
{
    FQuaternion Q = *this;
    Q.Normalize();
    const float XX = Q.X * Q.X, YY = Q.Y * Q.Y, ZZ = Q.Z * Q.Z;
    const float XY = Q.X * Q.Y, XZ = Q.X * Q.Z, YZ = Q.Y * Q.Z;
    const float XW = Q.X * Q.W, YW = Q.Y * Q.W, ZW = Q.Z * Q.W;
    return FMatrix(
        1.0f - 2.0f * (YY + ZZ), 2.0f * (XY + ZW), 2.0f * (XZ - YW), 0.0f,
        2.0f * (XY - ZW), 1.0f - 2.0f * (XX + ZZ), 2.0f * (YZ + XW), 0.0f,
        2.0f * (XZ + YW), 2.0f * (YZ - XW), 1.0f - 2.0f * (XX + YY), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
}
