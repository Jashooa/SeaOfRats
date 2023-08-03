#pragma once

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace ESP
    {
        class Kraken
        {
        public:
            static void Draw(SDK::UWorld* world, SDK::AActor* actor);
            static void DrawTentacle(SDK::UWorld* world, SDK::AActor* actor);
        };
    }
}
