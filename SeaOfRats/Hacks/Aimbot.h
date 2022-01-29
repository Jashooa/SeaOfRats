#pragma once

#include "include/SDK/SDK.h"

using namespace SDK;

namespace Hacks
{
    namespace Aimbot
    {
        void Init(UWorld* world);
        void CalculateAim(UWorld* world, AActor* actor);
        void Aim(UWorld* world);
    }
}