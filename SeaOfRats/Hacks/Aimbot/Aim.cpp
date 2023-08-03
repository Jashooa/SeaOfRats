#include "Aim.h"

#include <limits>

#include "Utilities/Math.h"

using namespace SDK;

namespace Hacks
{
    namespace Aimbot
    {
        int AimAtStaticTarget(const FVector& targetLocation, const FVector& sourceLocation, float projectileSpeed, float projectileGravityScalar, FRotator& outLow, FRotator& outHigh)
        {
            const float gravity = 981.f * projectileGravityScalar;
            const FVector relativeLocation = targetLocation - sourceLocation;
            const FVector relativeLocationXY = FVector(relativeLocation.X, relativeLocation.Y, 0.f);

            const float s2 = projectileSpeed * projectileSpeed;
            const float y = relativeLocation.Z;
            const float x = relativeLocationXY.Size();
            const float gX = gravity * x;

            // Calculate the discriminant of the quadratic equation
            const float discriminantSquared = (s2 * s2) - (gravity * ((gX * x) + (2 * y * s2)));

            // If discriminant is negative, no real solutions exist
            if (discriminantSquared < 0)
            {
                return 0;
            }

            // Calculate square root of the discriminant to find the roots
            const float root = std::sqrtf(discriminantSquared);

            // Calculate low and high angles of elevation
            const float lowAngle = FMath::Atan2(s2 - root, gX);
            const float highAngle = FMath::Atan2(s2 + root, gX);

            // Determine number of valid solutions
            const int numSolutions = lowAngle != highAngle ? 2 : 1;

            // Calculate normalised direction vector
            const FVector groundDirection = relativeLocationXY.GetSafeNormal();

            // Calculate the low angle rotation vector
            outLow = (groundDirection * std::cosf(lowAngle) * projectileSpeed + FVector::UpVector * std::sinf(lowAngle) * projectileSpeed).Rotation();

            // If there are 2 solutions then calculate the high angle rotation vector
            if (numSolutions == 2)
            {
                outHigh = (groundDirection * std::cosf(highAngle) * projectileSpeed + FVector::UpVector * std::sinf(highAngle) * projectileSpeed).Rotation();
            }

            return numSolutions;
        }

        int AimAtMovingTarget(const FVector& targetLocation, const FVector& targetVelocity, const FVector& sourceLocation, const FVector& sourceVelocity, float projectileSpeed, float projectileGravityScalar, FRotator& outLow, FRotator& outHigh)
        {
            const float gravity = 981.f * projectileGravityScalar;
            const FVector relativeLocation = targetLocation - sourceLocation;
            const FVector relativeVelocity = targetVelocity - sourceVelocity;
            const FVector gravityVector = FVector::DownVector * gravity;

            // Calculate coefficients for the quartic equation
            const float c4 = gravityVector | gravityVector * 0.25f;
            const float c3 = relativeVelocity | gravityVector;
            const float c2 = (relativeLocation | gravityVector) + (relativeVelocity | relativeVelocity) - (projectileSpeed * projectileSpeed);
            const float c1 = 2.f * (relativeLocation | relativeVelocity);
            const float c0 = relativeLocation | relativeLocation;

            // Solve the quartic equation
            std::complex<float> outRoots[4];
            const std::complex<float> inCoeffs[5] = { c0, c1, c2, c3, c4 };
            Utilities::Math::SolveQuartic(inCoeffs, outRoots);

            // Find the smallest positive real root
            float bestRoot = FLT_MAX;
            for (int i = 0; i < 4; ++i)
            {
                if (outRoots[i].real() > 0.f && FMath::Abs(outRoots[i].imag()) < 0.0001f && outRoots[i].real() < bestRoot)
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
            const FVector aimAt = targetLocation + (relativeVelocity * bestRoot);

            // Aim at the target
            return AimAtStaticTarget(aimAt, sourceLocation, projectileSpeed, projectileGravityScalar, outLow, outHigh);
        }

        int AimAtShip(const FVector& targetLocation, const FVector& targetVelocity, const FVector& targetAngularVelocity, const FVector& sourceLocation, const FVector& sourceVelocity, float projectileSpeed, float projectileGravityScalar, FRotator& outLow, FRotator& outHigh)
        {
            const float w = targetAngularVelocity.Z;

            if (w > -1.f && w < 1.f)
            {
                return AimAtMovingTarget(targetLocation, targetVelocity, sourceLocation, sourceVelocity, projectileSpeed, projectileGravityScalar, outLow, outHigh);
            }

            const FVector relativeLocation = targetLocation - sourceLocation;
            const auto wRad = FMath::DegreesToRadians(w);

            const float targetBoatVelocity = FVector(targetVelocity.X, targetVelocity.Y, 0.f).Size();
            const float radius = (targetBoatVelocity / wRad) * 0.98f;

            float thetaRad{};
            if (w < 0.f)
            {
                if (targetVelocity.X < 0.f)
                {
                    thetaRad = FMath::Atan2((-1.f * targetVelocity.X), targetVelocity.Y);
                }
                else if (targetVelocity.X > 0.f)
                {
                    thetaRad = FMath::Atan2((-1.f * targetVelocity.X), targetVelocity.Y) + 2 * PI;
                }
            }
            else if (w > 0.f)
            {
                thetaRad = FMath::Atan2((-1 * targetVelocity.X), targetVelocity.Y) + PI;
            }

            const float k = relativeLocation.X - (radius * std::cosf(thetaRad));
            const float l = relativeLocation.Y - (radius * std::sinf(thetaRad));
            const float m = relativeLocation.Z;
            const float n = (981.f * projectileGravityScalar) / 2;
            const float s2 = projectileSpeed * projectileSpeed;

            const FVector relativeLocationXY = FVector(relativeLocation.X, relativeLocation.Y, 0.f);
            const float groundDistance = relativeLocationXY.Size();

            float init{};
            if (groundDistance < 10000.f)
            {
                init = 4;
            }
            else if (groundDistance < 25000.f)
            {
                init = 10;
            }
            else if (groundDistance < 40000.f)
            {
                init = 15;
            }
            else
            {
                init = 20;
            }

            const float best = Utilities::Math::NewtonRaphson(init, k, l, m, n, radius, wRad, thetaRad, s2);

            if (best < 0.f)
            {
                return 0;
            }

            const float aT = targetLocation.X - radius * std::cosf(thetaRad) + radius * std::cosf(thetaRad + (wRad * best));
            const float bT = targetLocation.Y - radius * std::sinf(thetaRad) + radius * std::sinf(thetaRad + (wRad * best));
            const FVector aimAt = FVector(aT, bT, targetLocation.Z);

            return AimAtStaticTarget(aimAt, sourceLocation, projectileSpeed, projectileGravityScalar, outLow, outHigh);
        }
    }
}
