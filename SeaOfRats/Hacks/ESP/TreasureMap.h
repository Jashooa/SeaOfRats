#pragma once

#include <string>
#include <vector>

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace ESP
    {
        class TreasureMap
        {
        public:
            static void DrawRiddleMap(SDK::UWorld* world, SDK::AActor* actor);
            static void DrawXMarksTheSpotMap(SDK::UWorld* world, SDK::AActor* actor);
            static void DrawTornMap(SDK::UWorld* world, SDK::AActor* actor);

        private:
            static void getIslandRiddleActorByName(SDK::UWorld* world, std::string islandName, std::string actorName, std::vector<SDK::AActor*>* outActors);
        };
    }
}
