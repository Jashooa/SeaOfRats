#pragma once

#include <unordered_map>
#include <vector>

#include "include/SDK/SDK.h"

using namespace SDK;

namespace Utilities
{
    static inline bool PointInCircle(const FVector2D point, const FVector2D circle, const float radius)
    {
        const float distSquared = FVector2D::DistSquared(point, circle);
        const float radiusSquared = radius * radius;

        return distSquared <= radiusSquared;
    }

    static inline AActor* ClosestRelativeActorToBearing(const FVector origin, std::vector<AActor*> actors, std::string bearing)
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
}
