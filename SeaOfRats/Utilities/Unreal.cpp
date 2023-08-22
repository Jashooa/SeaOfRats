#include "Unreal.h"

#include <unordered_map>

using namespace SDK;

namespace Utilities
{
	namespace Unreal
	{
        std::vector<AActor*> GetActorComponentsByClass(AActor* actor, UClass* actorClass)
        {
            std::vector<AActor*> results;

            const auto components = actor->GetComponentsByClass(UChildActorComponent::StaticClass());
            for (const auto& component : components)
            {
                if (const auto actorComponent = reinterpret_cast<UChildActorComponent*>(component))
                {
                    if (const auto childActor = actorComponent->ChildActor)
                    {
                        if (childActor->IsA(actorClass))
                        {
                            results.push_back(childActor);
                        }
                    }
                }
            }

            return results;
        }

        AActor* ClosestRelativeActorToBearing(const FVector& origin, const std::vector<AActor*>& actors, const std::string& bearing)
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

            const auto originPosition = FVector2D(origin.X, origin.Y);

            AActor* closest = nullptr;
            auto closestAngle = FLT_MAX;

            if (bearings.find(bearing) == bearings.end())
            {
                return closest;
            }

            for (const auto actor : actors)
            {
                const auto actorLocation = actor->K2_GetActorLocation();
                const auto actorPosition = FVector2D(actorLocation.X, actorLocation.Y);
                const auto normalisedDifference = (actorPosition - originPosition).GetSafeNormal();
                const auto dotProduct = FVector2D::DotProduct(normalisedDifference, bearings.at(bearing));
                const auto angle = std::acos(dotProduct);

                if (angle < closestAngle)
                {
                    closestAngle = angle;
                    closest = actor;
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
            for (int i = 0; i < actors.Num(); ++i)
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
}