#pragma once

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace ESP
    {
        class Trigger
        {
        public:
            static void Draw(SDK::UWorld* world, SDK::AActor* actor);
            static void DrawSwitch(SDK::UWorld* world, SDK::AActor* actor);
            static void DrawPressurePlate(SDK::UWorld* world, SDK::AActor* actor);
            static void DrawTripwire(SDK::UWorld* world, SDK::AActor* actor);
            static void DrawVolume(SDK::UWorld* world, SDK::AActor* actor);
        };
    }
}
