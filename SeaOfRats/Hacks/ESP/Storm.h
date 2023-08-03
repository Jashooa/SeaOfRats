#pragma once

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace ESP
    {
        class Storm
        {
        public:
            static void Draw(SDK::UWorld* world);

        private:
            static void drawStorm(SDK::UWorld* world, SDK::AActor* actor);
        };
    }
}
