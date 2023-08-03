#pragma once

#include "Rotator.h"
#include "Vector.h"

namespace SDK
{
    // ScriptStruct CoreUObject.Quat
    // 0x0010
    struct alignas(16) FQuat
    {
        float X; // 0x0000(0x0004)
        float Y; // 0x0004(0x0004)
        float Z; // 0x0008(0x0004)
        float W; // 0x000C(0x0004)

        static const FQuat Identity;

        inline FQuat() : X(0.f), Y(0.f), Z(0.f), W(0.f)
        {
        }

        inline FQuat(float InX, float InY, float InZ, float InW) : X(InX), Y(InY), Z(InZ), W(InW)
        {
        }

        inline FQuat(const struct FRotator& R)
        {
            *this = R.Quaternion();
        }

        inline struct FVector RotateVector(struct FVector V) const
        {
            const FVector Q(X, Y, Z);
            const FVector T = (Q ^ V) * 2.f;
            const FVector Result = V + (T * W) + (Q ^ T);
            return Result;
        }
    };
}
