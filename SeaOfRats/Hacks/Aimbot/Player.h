#pragma once

#include "include/SDK/SDK.h"

using namespace SDK;

namespace Hacks
{
    namespace Aimbot
    {
        void InitPlayer(UWorld* world);
        void CalculateAimPlayer(UWorld* world, AActor* actor);
        void AimPlayer(UWorld* world);
    }
}