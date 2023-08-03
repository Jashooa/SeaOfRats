#pragma once

#include <vector>

#include "include/SDK/SDK.h"

namespace Utilities
{
    namespace Unreal
    {
        std::vector<SDK::AActor*> GetActorComponentsByClass(SDK::AActor* actor, SDK::UClass* actorClass);
        SDK::AActor* ClosestRelativeActorToBearing(const SDK::FVector& origin, const std::vector<SDK::AActor*>& actors, const std::string& bearing);
    }
}