#pragma once

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace ESP
    {
        class EnchantedCompass
        {
        public:
            static void Draw(SDK::UWorld* world, SDK::AActor* actor);
            static void DrawMultiTarget(SDK::UWorld* world, SDK::AActor* actor);
        };
    }
}
