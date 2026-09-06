#include "FQuaternion.h"
#include <cassert>
#include <cmath>
#include <cstdio>

static void Same(const FMatrix& A, const FMatrix& B, float Tolerance = 3e-5f)
{
    for (int I = 0; I < 4; ++I)
        for (int J = 0; J < 4; ++J)
            assert(std::isfinite(A.M[I][J]) && std::fabs(A.M[I][J] - B.M[I][J]) < Tolerance);
}

int main()
{
    constexpr float Pi = 3.14159265358979323846f;
    for (int I = -100; I <= 100; ++I)
    {
        const float Angle = I * .13f, C = std::cos(Angle), S = std::sin(Angle);
        Same(FQuaternion::FromAxisAngle({1,0,0}, Angle).ToRotationMatrix(),
            FMatrix(1,0,0,0, 0,C,S,0, 0,-S,C,0, 0,0,0,1));
        Same(FQuaternion::FromAxisAngle({0,1,0}, Angle).ToRotationMatrix(),
            FMatrix(C,0,-S,0, 0,1,0,0, S,0,C,0, 0,0,0,1));
        Same(FQuaternion::FromAxisAngle({0,0,1}, Angle).ToRotationMatrix(),
            FMatrix(C,S,0,0, -S,C,0,0, 0,0,1,0, 0,0,0,1));
        const auto A = FQuaternion::FromAxisAngle({1,2,3}, Angle);
        const auto B = FQuaternion::FromAxisAngle({-2,1,4}, Angle * .7f);
        Same((A * B).ToRotationMatrix(), B.ToRotationMatrix() * A.ToRotationMatrix());
        Same(A.ToRotationMatrix() * A.ToRotationMatrix().Transpose(), FMatrix::Identity);
        Same(FQuaternion{-A.X,-A.Y,-A.Z,-A.W}.ToRotationMatrix(), A.ToRotationMatrix());
    }

    const FVector Directions[] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1},{1,2,3},{-2,4,-1}};
    for (const auto& From : Directions)
        for (const auto& To : Directions)
        {
            const auto Q = FQuaternion::FromToRotation(From, To);
            const FVector Result(FVector4(From.GetNormalized(), 0) * Q.ToRotationMatrix());
            assert((Result - To.GetNormalized()).Length() < 2e-5f);
        }

    // Local mouse directions remain screen-relative even upside down.
    for (float Pitch : {0.0f, Pi/2, Pi, -Pi/2, 2*Pi})
    {
        const auto Q = FQuaternion::FromAxisAngle({0,1,0}, Pitch);
        const auto R = Q.ToRotationMatrix();
        const FVector Right(FVector4(0,1,0,0) * R), Up(FVector4(0,0,1,0) * R);
        const auto Yaw = FQuaternion::FromAxisAngle({0,0,1}, .01f);
        const auto TiltUp = FQuaternion::FromAxisAngle({0,1,0}, -.01f);
        const FVector Turned(FVector4(1,0,0,0) * (Q * Yaw).ToRotationMatrix());
        const FVector Raised(FVector4(1,0,0,0) * (Q * TiltUp).ToRotationMatrix());
        assert(Turned.Dot(Right) > 0 && Raised.Dot(Up) > 0);
        Same((Q * Yaw).ToRotationMatrix(),
            (FQuaternion::FromAxisAngle(Up, .01f) * Q).ToRotationMatrix());
    }

    FQuaternion Accumulated;
    const auto Step = FQuaternion::FromAxisAngle({0,0,1}, 2*Pi/10000);
    for (int I = 0; I < 10000; ++I) { Accumulated = Accumulated * Step; Accumulated.Normalize(); }
    Same(Accumulated.ToRotationMatrix(), FMatrix::Identity, 1e-4f);
    const auto Q = FQuaternion::FromAxisAngle({1,2,3}, 1.2f);
    const FVector Position(2,3,4);
    const auto World = FMatrix::MakeModelMatrix(Position, Q, FVector(1,1,1));
    const auto View = FMatrix::MakeTranslationMatrix(Position * -1) * Q.ToRotationMatrix().Transpose();
    Same(World * View, FMatrix::Identity);
    std::puts("PASS: axis convention, composition, 64 LookAt directions, inverted controls, 10000 rotations, view inverse.");
}
