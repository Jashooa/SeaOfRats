#pragma once

#include <complex>

#include "include/SDK/SDK.h"

namespace Utilities
{
    namespace Math
    {
        bool PointInCircle(const SDK::FVector2D& point, const SDK::FVector2D& circle, float radius);
        void SolveQuartic(const std::complex<float> coefficients[5], std::complex<float> roots[4]);
        float NewtonRaphson(float t, float K, float L, float M, float N, float r, float w, float theta, float S2);
    }
}
