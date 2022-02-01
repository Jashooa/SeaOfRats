#pragma once

#include "include/SDK/SDK.h"

using namespace SDK;

namespace Hacks
{
    namespace Aimbot
    {
        void InitCannon(UWorld* world);
        void CalculateAimCannon(UWorld* world, AActor* actor);
        void AimCannon(UWorld* world);
        void CannonTrace(UWorld* world);
    }
}
