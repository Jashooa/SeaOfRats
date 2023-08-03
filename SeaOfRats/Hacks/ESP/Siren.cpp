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
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            FVector2D topPosition;
            if (!playerController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z + extent.Z }, &topPosition))
            {
                return;
            }

            // Get bottom coordinates
            FVector2D bottomPosition;
            if (!playerController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z - extent.Z }, &bottomPosition))
            {
                return;
            }

            // Colour
            const ImU32 colour = Utilities::Drawing::Colour::Orange;

            // Draw box
            Utilities::Drawing::DrawBoundingRect(world, actor, colour);

            // Draw health bar
            if (const auto healthComponent = siren->HealthComponent)
            {
                const float healthCurrent = healthComponent->GetCurrentHealth();
                const float healthMax = healthComponent->GetMaxHealth();
                Utilities::Drawing::DrawHealthBar({ topPosition.X, topPosition.Y -= 15.f }, healthCurrent, healthMax);
            }

            // Get name
            std::string name = "Siren";
            const std::string actorName = actor->GetName();
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
                            const std::string itemName = itemDesc->Title.DisplayString->ToString();
                            Utilities::Drawing::DrawString(itemName, { bottomPosition.X, bottomPosition.Y += 15.f }, Utilities::Drawing::Colour::White);
                        }
                    }
                }
            }
        }
    }
}
