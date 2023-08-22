#pragma once

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace ESP
    {
        class Island
        {
        public:
            static void Draw(SDK::UWorld* world);

        private:
            static void drawIsland(SDK::UWorld* world, SDK::UIslandDataAssetEntry* island);
        };
    }
}
