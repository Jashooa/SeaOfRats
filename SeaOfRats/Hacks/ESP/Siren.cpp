#include "Siren.h"

#include "Utilities/Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Siren::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto siren = reinterpret_cast<ASirenPawn*>(actor);

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 1500.f)
            {
                return;
            }

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Get bounds
            auto origin = FVector{};
            auto extent = FVector{};
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topPosition = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z + extent.Z }, &topPosition))
            {
                return;
            }

            // Get bottom coordinates
            auto bottomPosition = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z - extent.Z }, &bottomPosition))
            {
                return;
            }

            // Colour
            const auto colour = Utilities::Drawing::Colour::Orange;

            // Draw box
            Utilities::Drawing::DrawBoundingRect(world, actor, colour);

            // Draw health bar
            if (const auto healthComponent = siren->HealthComponent)
            {
                const auto healthCurrent = healthComponent->GetCurrentHealth();
                const auto healthMax = healthComponent->GetMaxHealth();
                Utilities::Drawing::DrawHealthBar({ topPosition.X, topPosition.Y -= 15.f }, healthCurrent, healthMax);
            }

            // Get name
            auto name = std::string{ "Siren" };
            const auto actorName = actor->GetName();
            if (actorName.find("Leader") != std::string::npos)
            {
                name += " Leader";
            }

            name += " " + actorName;
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);

            // Draw item info
            if (const auto wieldedItemComponent = siren->WieldedItemComponent)
            {
                if (const auto wieldedItem = reinterpret_cast<AWieldableItem*>(wieldedItemComponent->CurrentlyWieldedItem))
                {
                    if (const auto itemInfo = wieldedItem->ItemInfo)
                    {
                        if (const auto itemDesc = itemInfo->Desc)
                        {
                            const auto itemName = itemDesc->Title.DisplayString->ToString();
                            Utilities::Drawing::DrawString(itemName, { bottomPosition.X, bottomPosition.Y += 15.f }, Utilities::Drawing::Colour::White);
                        }
                    }
                }
            }
        }
    }
}
