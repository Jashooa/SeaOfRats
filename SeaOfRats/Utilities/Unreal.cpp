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

            auto components = actor->GetComponentsByClass(UChildActorComponent::StaticClass());
            for (int i = 0; i < components.Num(); ++i)
            {
                if (const auto component = reinterpret_cast<UChildActorComponent*>(components[i]))
                {
                    if (const auto childActor = component->ChildActor)
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

            const FVector2D originPosition(origin.X, origin.Y);

            AActor* closest = nullptr;
            float closestAngle = FLT_MAX;

            if (bearings.find(bearing) == bearings.end())
            {
                return closest;
            }

            for (size_t i = 0; i < actors.size(); ++i)
            {
                auto actorLocation = actors[i]->K2_GetActorLocation();
                FVector2D actorPosition(actorLocation.X, actorLocation.Y);

                FVector2D normalisedDifference = (actorPosition - originPosition).GetSafeNormal();

                auto dotProduct = FVector2D::DotProduct(normalisedDifference, bearings.at(bearing));

                auto angle = std::acosf(dotProduct);

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