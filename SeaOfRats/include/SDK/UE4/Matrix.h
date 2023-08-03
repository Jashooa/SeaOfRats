#pragma once

#include "Axis.h"
#include "SSE.h"
#include "Vector.h"

namespace SDK
{
    // ScriptStruct CoreUObject.Matrix
    struct FMatrix
    {
        union
        {
            __declspec(align(16)) float M[4][4];
        };

        alignas(16) static const FMatrix Identity;

        inline FMatrix()
        {
        }

        inline FMatrix(const FVector& InX, const FVector& InY, const FVector& InZ, const FVector& InW)
        {
            M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = 0.0f;
            M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = 0.0f;
            M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = 0.0f;
            M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = 1.0f;
        }

        inline void SetIdentity()
        {
            M[0][0] = 1.f; M[0][1] = 0.f;  M[0][2] = 0.f;  M[0][3] = 0.f;
            M[1][0] = 0.f; M[1][1] = 1.f;  M[1][2] = 0.f;  M[1][3] = 0.f;
            M[2][0] = 0.f; M[2][1] = 0.f;  M[2][2] = 1.f;  M[2][3] = 0.f;
            M[3][0] = 0.f; M[3][1] = 0.f;  M[3][2] = 0.f;  M[3][3] = 1.f;
        }

        inline void operator*=(const FMatrix& Other)
        {
            VectorMatrixMultiply(this, this, &Other);
        }

        inline FMatrix operator*(const FMatrix& Other) const
        {
            FMatrix Result;
            VectorMatrixMultiply(&Result, this, &Other);
            return Result;
        }

        inline FVector GetOrigin() const
        {
            return FVector(M[3][0], M[3][1], M[3][2]);
        }

        inline FVector GetScaledAxis(EAxis::Type InAxis) const
        {
            switch (InAxis)
            {
            case EAxis::X:
                return FVector(M[0][0], M[0][1], M[0][2]);

            case EAxis::Y:
                return FVector(M[1][0], M[1][1], M[1][2]);

            case EAxis::Z:
                return FVector(M[2][0], M[2][1], M[2][2]);

            default:
                return FVector::ZeroVector;
            }
        }

        static FMatrix MakeFromX(FVector const& XAxis)
        {
            FVector const NewX = XAxis.GetSafeNormal();

            FVector const UpVector = (FMath::Abs(NewX.Z) < (1.f - KINDA_SMALL_NUMBER)) ? FVector(0.f, 0.f, 1.f) : FVector(1.f, 0.f, 0.f);

            const FVector NewY = (UpVector ^ NewX).GetSafeNormal();
            const FVector NewZ = NewX ^ NewY;

            return FMatrix(NewX, NewY, NewZ, FVector::ZeroVector);
        }

        struct FRotator Rotator() const;
    };
}
