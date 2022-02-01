#pragma once

#include "Quat.h"

namespace SDK
{
    // ScriptStruct CoreUObject.Rotator
    // 0x000C
    struct FRotator
    {
        float Pitch; // 0x0000(0x0004)
        float Yaw; // 0x0004(0x0004)
        float Roll; // 0x0008(0x0004)

        inline FRotator() : Pitch(0.f), Yaw(0.f), Roll(0.f)
        {}

        inline FRotator(float InPitch, float InYaw, float InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll)
        {}

        inline FRotator operator+=(const FRotator& R)
        {
            Pitch += R.Pitch; Yaw += R.Yaw; Roll += R.Roll;
            return *this;
        }

        struct FQuat Quaternion() const;
    };
}
