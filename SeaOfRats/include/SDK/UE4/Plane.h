#pragma once

#include "Vector.h"

namespace SDK
{
    // ScriptStruct CoreUObject.Plane
    // 0x0004 (0x0010 - 0x000C)
    struct alignas(16) FPlane : public FVector
    {
        float W; // 0x000C(0x0004)

        inline FPlane()
        {
        }

        inline FPlane(const FPlane& P) : FVector(P), W(P.W)
        {
        }

        inline FPlane(float InX, float InY, float InZ, float InW) : FVector(InX, InY, InZ), W(InW)
        {
        }
    };
}
