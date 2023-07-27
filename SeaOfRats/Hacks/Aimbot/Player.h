#pragma once

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace Aimbot
    {
        void InitAimPlayer(SDK::UWorld* world);
        void CalculateAimPlayer(SDK::UWorld* world, SDK::AActor* actor);
        void AimPlayer(SDK::UWorld* world);
    }
}
