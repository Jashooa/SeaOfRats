#pragma once

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace Aimbot
    {
        void InitCannon(SDK::UWorld* world);
        void CalculateAimCannon(SDK::UWorld* world, SDK::AActor* actor);
        void AimCannon(SDK::UWorld* world);
        void CannonTrace(SDK::UWorld* world);
    }
}
