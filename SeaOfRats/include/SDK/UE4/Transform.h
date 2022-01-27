#pragma once

#include "Matrix.h"
#include "Quat.h"
#include "Rotator.h"
#include "Vector.h"

namespace SDK
{
    // ScriptStruct CoreUObject.Transform
    // 0x0030
    struct alignas(16) FTransform
    {
        FQuat Rotation; // 0x0000(0x0010)
        FVector Translation; // 0x0010(0x000C)
        unsigned char UnknownData00[0x4]; // 0x001C(0x0004)
        FVector Scale3D; // 0x0020(0x000C)
        unsigned char UnknownData01[0x4]; // 0x002C(0x0004)

        inline FTransform() : Rotation(0.f, 0.f, 0.f, 1.f), Translation(0.f), Scale3D(1.f)
        {}

        inline FTransform(const FVector& InTranslation) : Rotation(FQuat::Identity), Translation(InTranslation), Scale3D(FVector(1.f))
        {}

        inline FTransform(const FQuat& InRotation) : Rotation(InRotation), Translation(FVector::ZeroVector), Scale3D(FVector(1.f))
        {}

        inline FTransform(const FRotator& InRotation) : Rotation(InRotation), Translation(FVector::ZeroVector), Scale3D(FVector(1.f))
        {}

        inline FTransform(const FQuat& InRotation, const FVector& InTranslation, const FVector& InScale3D = FVector(1.f)) : Rotation(InRotation), Translation(InTranslation), Scale3D(InScale3D)
        {}

        inline FTransform(const FRotator& InRotation, const FVector& InTranslation, const FVector& InScale3D = FVector(1.f)) : Rotation(InRotation), Translation(InTranslation), Scale3D(InScale3D)
        {}

        inline FTransform(const FTransform& InTransform) : Rotation(InTransform.Rotation), Translation(InTransform.Translation), Scale3D(InTransform.Scale3D)
        {}

        inline FVector TransformPosition(const FVector& V) const
        {
            return Rotation.RotateVector(Scale3D * V) + Translation;
        }

        inline FMatrix ToMatrixWithScale() const
        {
            FMatrix OutMatrix;

            OutMatrix.M[3][0] = Translation.X;
            OutMatrix.M[3][1] = Translation.Y;
            OutMatrix.M[3][2] = Translation.Z;

            const float x2 = Rotation.X + Rotation.X;
            const float y2 = Rotation.Y + Rotation.Y;
            const float z2 = Rotation.Z + Rotation.Z;
            {
                const float xx2 = Rotation.X * x2;
                const float yy2 = Rotation.Y * y2;
                const float zz2 = Rotation.Z * z2;

                OutMatrix.M[0][0] = (1.0f - (yy2 + zz2)) * Scale3D.X;
                OutMatrix.M[1][1] = (1.0f - (xx2 + zz2)) * Scale3D.Y;
                OutMatrix.M[2][2] = (1.0f - (xx2 + yy2)) * Scale3D.Z;
            }
            {
                const float yz2 = Rotation.Y * z2;
                const float wx2 = Rotation.W * x2;

                OutMatrix.M[2][1] = (yz2 - wx2) * Scale3D.Z;
                OutMatrix.M[1][2] = (yz2 + wx2) * Scale3D.Y;
            }
            {
                const float xy2 = Rotation.X * y2;
                const float wz2 = Rotation.W * z2;

                OutMatrix.M[1][0] = (xy2 - wz2) * Scale3D.Y;
                OutMatrix.M[0][1] = (xy2 + wz2) * Scale3D.X;
            }
            {
                const float xz2 = Rotation.X * z2;
                const float wy2 = Rotation.W * y2;

                OutMatrix.M[2][0] = (xz2 + wy2) * Scale3D.Z;
                OutMatrix.M[0][2] = (xz2 - wy2) * Scale3D.X;
            }

            OutMatrix.M[0][3] = 0.0f;
            OutMatrix.M[1][3] = 0.0f;
            OutMatrix.M[2][3] = 0.0f;
            OutMatrix.M[3][3] = 1.0f;

            return OutMatrix;
        }
    };
}
