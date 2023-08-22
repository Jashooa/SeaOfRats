#include "Aim.h"

#include <limits>

#include "Utilities/Drawing.h"
#include "Utilities/Math.h"

using namespace SDK;

namespace Hacks
{
    namespace Aimbot
    {
        float time_func(float t, float K, float L, float M, float N, float r, float w, float theta, float S2)
        {
            const float K2 = K * K;
            const float L2 = L * L;
            const float M2 = M * M;
            const float N2 = N * N;
            const float r2 = r * r;
            return N2 * t * t * t * t + ((2 * M * N) - S2) * t * t - 2 * r * (K * std::cos(theta + (w * t)) + L * std::sin(theta + (w * t))) + K2 + L2 + M2 + r2;
        }

        float time_derivFunc(float t, float K, float L, float M, float N, float r, float w, float theta, float S2)
        {
            const float N2 = N * N;
            return 4 * N2 * t * t * t + 2 * ((2 * M * N) - S2) * t + 2 * r * w * (K * std::sin(theta + (w * t) - L * std::cos(theta + (w * t))));
        }

        float NewtonRaphson(float t, float K, float L, float M, float N, float r, float w, float theta, float S2)
        {
            float h = time_func(t, K, L, M, N, r, w, theta, S2) / time_derivFunc(t, K, L, M, N, r, w, theta, S2);
            int counter = 0;
            while (std::abs(h) >= 0.01f)
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

        float CalculateTime(const FVector& targetLocation, const FVector& sourceLocation, float projectileSpeed, float projectileGravityScalar)
        {
            const auto gravity = 981.f * projectileGravityScalar;
            const auto relativeLocation = targetLocation - sourceLocation;
            const auto relativeLocationXY = FVector{ relativeLocation.X, relativeLocation.Y, 0.f };

            const auto s2 = projectileSpeed * projectileSpeed;
            const auto y = relativeLocation.Z;
            const auto x = relativeLocationXY.Size();
            const auto gX = gravity * x;

            // Calculate the discriminant of the quadratic equation
            const auto discriminantSquared = (s2 * s2) - (gravity * ((gX * x) + (2 * s2 * y)));

            // If discriminant is negative, no real solutions exist
            if (discriminantSquared < 0)
            {
                return 0;
            }

            // Calculate square root of the discriminant to find the roots
            const auto root = std::sqrt(discriminantSquared);

            // Calculate low angle
            const auto lowAngle = FMath::Atan2(s2 - root, gX);

            // Calculate time to hit
            const auto t = x / (projectileSpeed * std::cos(lowAngle));

            return t;
        }

        int GetAimAngles(UWorld* world, const FVector& targetLocation, const FVector& sourceLocation, float projectileSpeed, float projectileGravityScalar, FRotator& outLow, FRotator& outHigh)
        {
            const auto gravity = 981.f * projectileGravityScalar;
            const auto relativeLocation = targetLocation - sourceLocation;
            const auto relativeLocationXY = FVector{ relativeLocation.X, relativeLocation.Y, 0.f };

            const auto s2 = projectileSpeed * projectileSpeed;
            const auto y = relativeLocation.Z;
            const auto x = relativeLocationXY.Size();
            const auto gX = gravity * x;

            // Calculate the discriminant of the quadratic equation
            const auto discriminantSquared = (s2 * s2) - (gravity * ((gX * x) + (2 * y * s2)));

            // If discriminant is negative, no real solutions exist
            if (discriminantSquared < 0)
            {
                return 0;
            }

            // Calculate square root of the discriminant to find the roots
            const auto root = std::sqrt(discriminantSquared);

            // Calculate low and high angles of elevation
            const auto lowAngle = FMath::Atan2(s2 - root, gX);
            const auto highAngle = FMath::Atan2(s2 + root, gX);

            // Determine number of valid solutions
            const auto numSolutions = lowAngle != highAngle ? 2 : 1;

            // Calculate normalised direction vector
            const auto groundDirection = relativeLocationXY.GetSafeNormal();

            // Calculate the low angle rotation vector
            outLow = (groundDirection * std::cos(lowAngle) * projectileSpeed + FVector::UpVector * std::sin(lowAngle) * projectileSpeed).Rotation();

            // If there are 2 solutions then calculate the high angle rotation vector
            if (numSolutions == 2)
            {
                outHigh = (groundDirection * std::cos(highAngle) * projectileSpeed + FVector::UpVector * std::sin(highAngle) * projectileSpeed).Rotation();
            }

            auto position = FVector2D{};
            if (world->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(targetLocation, &position))
            {
                Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::Yellow);
            }

            return numSolutions;
        }

        int AimAtMovingTarget(UWorld* world, const FVector& targetLocation, const FVector& targetVelocity, const FVector& sourceLocation, const FVector& sourceVelocity, float projectileSpeed, float projectileGravityScalar, FRotator& outLow, FRotator& outHigh)
        {
            const auto gravity = 981.f * projectileGravityScalar;
            const auto relativeLocation = targetLocation - sourceLocation;
            const auto relativeVelocity = FVector(targetVelocity.X, targetVelocity.Y, 0.f) - sourceVelocity;
            const auto gravityVector = FVector::DownVector * gravity;

            // Calculate coefficients for the quartic equation
            const auto c4 = gravityVector | gravityVector * 0.25f;
            const auto c3 = relativeVelocity | gravityVector;
            const auto c2 = (relativeLocation | gravityVector) + (relativeVelocity | relativeVelocity) - (projectileSpeed * projectileSpeed);
            const auto c1 = 2.f * (relativeLocation | relativeVelocity);
            const auto c0 = relativeLocation | relativeLocation;

            // Solve the quartic equation
            std::complex<float> outRoots[4];
            const std::complex<float> inCoeffs[5] = { c0, c1, c2, c3, c4 };
            Utilities::Math::SolveQuartic(inCoeffs, outRoots);

            // Find the smallest positive real root
            auto bestRoot = FLT_MAX;
            for (int i = 0; i < 4; ++i)
            {
                if (outRoots[i].real() > 0.f && std::abs(outRoots[i].imag()) < 0.0001f && outRoots[i].real() < bestRoot)
                {
                    bestRoot = outRoots[i].real();
                }
            }

            // No valid solution
            if (bestRoot == FLT_MAX)
            {
                return 0;
            }

            // Calculate the aim location
            const auto aimAt = targetLocation + (relativeVelocity * bestRoot);

            // Aim at the target
            return GetAimAngles(world, aimAt, sourceLocation, projectileSpeed, projectileGravityScalar, outLow, outHigh);
        }

        int AimAtShip(UWorld* world, const FVector& targetLocation, const FVector& targetVelocity, const FVector& targetAngularVelocity, const FVector& sourceLocation, const FVector& sourceVelocity, float projectileSpeed, float projectileGravityScalar, FRotator& outLow, FRotator& outHigh)
        {
            const auto angularVelocity = targetAngularVelocity.Z;
            const auto targetBoatVelocity = FVector{ targetVelocity.X, targetVelocity.Y, 0.f }.Size();

            if ((angularVelocity > -5.f && angularVelocity < 5.f) || targetBoatVelocity < 300.f)
            {
                return AimAtMovingTarget(world, targetLocation, targetVelocity, sourceLocation, sourceVelocity, projectileSpeed, projectileGravityScalar, outLow, outHigh);
            }

            const auto relativeLocation = targetLocation - sourceLocation;
            const auto angularVelocityRad = FMath::DegreesToRadians(angularVelocity);

            const auto turnRadius = (targetBoatVelocity / angularVelocityRad) * 0.98f;

            auto theta = FMath::Atan2(targetVelocity.Y, targetVelocity.X) + PI / 2;
            theta = std::fmod(theta, 2.f * PI);

            const auto k = relativeLocation.X + (turnRadius * std::cos(theta));
            const auto l = relativeLocation.Y + (turnRadius * std::sin(theta));

            /*auto position = FVector2D{};
            if (world->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen({ targetLocation.X + (turnRadius * std::cos(theta)), targetLocation.Y + (turnRadius * std::sin(theta)), 5.f * 100.f }, &position))
            {
                Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::White);
            }*/

            const auto m = relativeLocation.Z;
            const auto n = (981.f * projectileGravityScalar) / 2.f;
            const auto s2 = projectileSpeed * projectileSpeed;

            const auto distanceXY = FVector{ relativeLocation.X, relativeLocation.Y, 0.f }.Size();

            auto init = CalculateTime(targetLocation, sourceLocation, projectileSpeed, projectileGravityScalar);

            if (init == 0)
            {
                if (distanceXY < 10000.f)
                {
                    init = 2.f;
                }
                else if (distanceXY < 25000.f)
                {
                    init = 4.f;
                }
                else if (distanceXY < 40000.f)
                {
                    init = 6.f;
                }
                else
                {
                    init = 8.f;
                }
            }

            const auto best = NewtonRaphson(init, k, l, m, n, turnRadius, angularVelocityRad, theta, s2);

            /*float x = 1200.f;
            float y = 200.f;
            Utilities::Drawing::DrawString("angularVelocity: " + std::to_string(angularVelocity), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("targetVelocity.X: " + std::to_string(targetVelocity.X), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("targetVelocity.Y: " + std::to_string(targetVelocity.Y), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("turnRadius: " + std::to_string(turnRadius), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("angularVelocityRad: " + std::to_string(angularVelocityRad), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("theta: " + std::to_string(theta), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            float thetaDeg = FMath::RadiansToDegrees(theta);
            Utilities::Drawing::DrawString("thetaDeg: " + std::to_string(thetaDeg), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("k: " + std::to_string(k), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("l: " + std::to_string(l), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("m: " + std::to_string(m), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("n: " + std::to_string(n), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("s2: " + std::to_string(s2), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("distanceXY: " + std::to_string(distanceXY), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("init: " + std::to_string(init), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("best: " + std::to_string(best), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);*/

            if (best < 0.f)
            {
                return AimAtMovingTarget(world, targetLocation, targetVelocity, sourceLocation, sourceVelocity, projectileSpeed, projectileGravityScalar, outLow, outHigh);
            }

            const auto aT = targetLocation.X + (turnRadius * std::cos(theta)) - (turnRadius * std::cos(theta + (angularVelocityRad * best)));
            const auto bT = targetLocation.Y + (turnRadius * std::sin(theta)) - (turnRadius * std::sin(theta + (angularVelocityRad * best)));
            const auto aimAt = FVector{ aT, bT, targetLocation.Z };
            // const auto aimAt = FVector{ aT, bT, 0.f };

            auto position = FVector2D{};
            if (world->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(aimAt, &position))
            {
                Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::Orange);
            }

            // return GetAimAngles(world, aimAt, sourceLocation, projectileSpeed, projectileGravityScalar, outLow, outHigh);
            return AimAtMovingTarget(world, aimAt, FVector::ZeroVector, sourceLocation, sourceVelocity, projectileSpeed, projectileGravityScalar, outLow, outHigh);
        }
    }
}
