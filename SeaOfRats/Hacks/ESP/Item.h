#pragma once

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace ESP
    {
        class Item
        {
        public:
            static void Draw(SDK::UWorld* world, SDK::AActor* actor);
            static void GetPrices(SDK::UWorld* world);
        };
    }
}
