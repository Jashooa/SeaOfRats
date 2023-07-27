#pragma once

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace Aimbot
    {
        int AimAtStaticTarget(const SDK::FVector& sourcePos, const SDK::FVector& targetPos, float projectileSpeed, float projectileGravityScalar, SDK::FRotator& outLow, SDK::FRotator& outHigh);
        int AimAtMovingTarget(const SDK::FVector& sourcePos, const SDK::FVector& sourceVelocity, const SDK::FVector& targetPos, const SDK::FVector& targetVelocity, float projectileSpeed, float projectileGravityScalar, SDK::FRotator& outLow, SDK::FRotator& outHigh);
    }
}
