#pragma once

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace ESP
    {
        class Ship
        {
        public:
            static void Draw(SDK::UWorld* world, SDK::AActor* actor);
            static void DrawFar(SDK::UWorld* world, SDK::AActor* actor);
        };
    }
}
