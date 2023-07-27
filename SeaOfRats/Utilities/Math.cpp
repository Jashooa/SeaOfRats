#include "Math.h"

#include <unordered_map>

using namespace SDK;

namespace Utilities
{
    bool PointInCircle(const FVector2D point, const FVector2D circle, const float radius)
    {
        const float distSquared = FVector2D::DistSquared(point, circle);
        const float radiusSquared = radius * radius;

        return distSquared <= radiusSquared;
    }

    AActor* ClosestRelativeActorToBearing(const FVector origin, std::vector<AActor*> actors, std::string bearing)
    {
        static const std::unordered_map<std::string, FVector2D> bearings =
        {
            {"North", FVector2D(0.f, -1.f).GetSafeNormal()},
            {"North East", FVector2D(-1.f, -1.f).GetSafeNormal()},
            {"East", FVector2D(-1.f, 0.f).GetSafeNormal()},
            {"South East", FVector2D(-1.f, 1.f).GetSafeNormal()},
            {"South", FVector2D(0.f, 1.f).GetSafeNormal()},
            {"South West", FVector2D(1.f, 1.f).GetSafeNormal()},
            {"West", FVector2D(1.f, 0.f).GetSafeNormal()},
            {"North West", FVector2D(1.f, -1.f).GetSafeNormal()}
        };

        const FVector2D originPosition(origin.X, origin.Y);

        AActor* closest = nullptr;
        float closestAngle = FLT_MAX;

        if (bearings.find(bearing) == bearings.end())
        {
            return closest;
        }

        for (auto i = 0; i < actors.size(); ++i)
        {
            auto actorLocation = actors[i]->K2_GetActorLocation();
            FVector2D actorPosition(actorLocation.X, actorLocation.Y);

            FVector2D normalisedDifference = (actorPosition - originPosition).GetSafeNormal();

            auto dotProduct = FVector2D::DotProduct(normalisedDifference, bearings.at(bearing));

            auto angle = acosf(dotProduct);

            if (angle < closestAngle)
            {
                closestAngle = angle;
                closest = actors[i];
            }
        }

        return closest;
    }

    /*static inline FVector ClosestRelativeActorToBearing(const FVector origin, TArray<FVector> actors, std::string bearing)
    {
        const FVector2D originPosition(origin.X, origin.Y);

        //AActor* closest = nullptr;
        FVector closest(0.f, 0.f, 0.f);
        float closestAngle = FLT_MAX;

        if (bearings.find(bearing) == bearings.end())
        {
            return closest;
        }
        spdlog::info("Start");
        for (auto i = 0; i < actors.Num(); ++i)
        {
            auto actor = actors[i];
            //auto actorLocation = actor->K2_GetActorLocation();
            auto actorLocation = actor;
            FVector2D actorPosition(actorLocation.X, actorLocation.Y);
            spdlog::info("actorPosition {} {}", actorPosition.X, actorPosition.Y);
            FVector2D normalisedDifference = (actorPosition - originPosition).GetSafeNormal();
            spdlog::info("normalisedDifference {} {}", normalisedDifference.X, normalisedDifference.Y);
            auto dotProduct = FVector2D::DotProduct(normalisedDifference, bearings.at(bearing));
            spdlog::info("bearing {} {}", bearings.at(bearing).X, bearings.at(bearing).Y);
            spdlog::info("dotProduct {}", dotProduct);
            auto angle = acosf(dotProduct);
            spdlog::info("angle {}", angle);
            if (angle < closestAngle)
            {
                closestAngle = angle;
                closest = actor;
            }
        }
        spdlog::info("Finish");
        return closest;
    }*/

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
}
