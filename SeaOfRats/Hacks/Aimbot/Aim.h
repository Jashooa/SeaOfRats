#pragma once

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace Aimbot
    {
        int AimAtStaticTarget(SDK::UWorld* world, const SDK::FVector& targetPos, const SDK::FVector& sourcePos, float projectileSpeed, float projectileGravityScalar, SDK::FRotator& outLow, SDK::FRotator& outHigh);
        int AimAtMovingTarget(SDK::UWorld* world, const SDK::FVector& targetPos, const SDK::FVector& targetVelocity, const SDK::FVector& sourcePos, const SDK::FVector& sourceVelocity, float projectileSpeed, float projectileGravityScalar, SDK::FRotator& outLow, SDK::FRotator& outHigh);
        int AimAtShip(SDK::UWorld* world, const SDK::FVector& targetPos, const SDK::FVector& targetVelocity, const SDK::FVector& targetAngularVelocity, const SDK::FVector& sourcePos, const SDK::FVector& sourceVelocity, float projectileSpeed, float projectileGravityScalar, SDK::FRotator& outLow, SDK::FRotator& outHigh);
    }
}
