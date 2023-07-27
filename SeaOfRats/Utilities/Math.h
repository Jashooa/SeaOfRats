#pragma once

#include <complex>
#include <vector>

#include "include/SDK/SDK.h"

namespace Utilities
{
    bool PointInCircle(const SDK::FVector2D point, const SDK::FVector2D circle, const float radius);
    SDK::AActor* ClosestRelativeActorToBearing(const SDK::FVector origin, std::vector<SDK::AActor*> actors, std::string bearing);
    void SolveQuartic(const std::complex<float> coefficients[5], std::complex<float> roots[4]);
}
