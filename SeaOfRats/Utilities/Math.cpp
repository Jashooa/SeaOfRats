#include "Math.h"

#include <cmath>

using namespace SDK;

namespace Utilities
{
    namespace Math
    {
        bool PointInCircle(const FVector2D& point, const FVector2D& circle, float radius)
        {
            const float distSquared = FVector2D::DistSquared(point, circle);
            const float radiusSquared = radius * radius;

            return distSquared <= radiusSquared;
        }

        void SolveQuartic(const std::complex<float> coefficients[5], std::complex<float> roots[4]) {
            const std::complex<float> a = coefficients[4];
            const std::complex<float> b = coefficients[3] / a;
            const std::complex<float> c = coefficients[2] / a;
            const std::complex<float> d = coefficients[1] / a;
            const std::complex<float> e = coefficients[0] / a;
            const std::complex<float> Q1 = c * c - 3.f * b * d + 12.f * e;
            const std::complex<float> Q2 = 2.f * c * c * c - 9.f * b * c * d + 27.f * d * d + 27.f * b * b * e - 72.f * c * e;
            const std::complex<float> Q3 = 8.f * b * c - 16.f * d - 2.f * b * b * b;
            const std::complex<float> Q4 = 3.f * b * b - 8.f * c;
            const std::complex<float> Q5 = std::pow(Q2 / 2.f + std::sqrt(Q2 * Q2 / 4.f - Q1 * Q1 * Q1), 1.f / 3.f);
            const std::complex<float> Q6 = (Q1 / Q5 + Q5) / 3.f;
            const std::complex<float> Q7 = 2.f * std::sqrt(Q4 / 12.f + Q6);
            roots[0] = (-b - Q7 - std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 - Q3 / Q7)) / 4.f;
            roots[1] = (-b - Q7 + std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 - Q3 / Q7)) / 4.f;
            roots[2] = (-b + Q7 - std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 + Q3 / Q7)) / 4.f;
            roots[3] = (-b + Q7 + std::sqrt(4.f * Q4 / 6.f - 4.f * Q6 + Q3 / Q7)) / 4.f;
        }

        float time_func(float t, float K, float L, float M, float N, float r, float w, float theta, float S2)
        {
            const float K2 = K * K;
            const float L2 = L * L;
            const float M2 = M * M;
            const float N2 = N * N;
            const float r2 = r * r;
            return N2 * t * t * t * t + ((2 * M * N) - S2) * t * t + 2 * r * (K * std::cos(theta + (w * t)) + L * std::sin(theta + (w * t))) + K2 + L2 + M2 + r2;
        }

        float time_derivFunc(float t, float K, float L, float M, float N, float r, float w, float theta, float S2)
        {
            const float N2 = N * N;
            return 4 * N2 * t * t * t * t + 2 * ((2 * M * N) - S2) * t + 2 * r * w * (L * std::cos(theta + (w * t)) - K * std::sin(theta + (w + t)));
        }

        float NewtonRaphson(float t, float K, float L, float M, float N, float r, float w, float theta, float S2)
        {
            float h = time_func(t, K, L, M, N, r, w, theta, S2) / time_derivFunc(t, K, L, M, N, r, w, theta, S2);
            int counter = 0;
            while (std::abs(h) >= 0.01)
            {
                if (counter > 200)
                {
                    break;
                }
                h = time_func(t, K, L, M, N, r, w, theta, S2) / time_derivFunc(t, K, L, M, N, r, w, theta, S2);
                t = t - h;
                counter++;
            }
            return t;
        }
    }
}
