#include "Siren.h"

#include "Drawing.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawSiren(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto siren = reinterpret_cast<ASirenPawn*>(actor);

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
            ImU32 colour = Drawing::Colour::Orange;

            // Draw box
            Drawing::DrawBoundingRect(world, actor, colour);

            // Get name
            std::string name = "Siren";
            const std::string actorName = actor->GetName();
            name += " " + actorName;

            // Get distance
            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            Drawing::DrawString(name, { topPosition.X, topPosition.Y - 30.f }, colour);

            // Draw health bar
            if (const auto healthComponent = siren->HealthComponent)
            {
                const float healthCurrent = healthComponent->GetCurrentHealth();
                const float healthMax = healthComponent->GetMaxHealth();
                Drawing::DrawHealthBar({ topPosition.X, topPosition.Y - 15.f }, healthCurrent, healthMax);
            }

            // Draw item info
            if (const auto wieldedItemComponent = siren->WieldedItemComponent)
            {
                if (const auto wieldedItem = reinterpret_cast<AWieldableItem*>(wieldedItemComponent->CurrentlyWieldedItem))
                {
                    if (const auto itemInfo = wieldedItem->ItemInfo)
                    {
                        if (const auto itemDesc = itemInfo->Desc)
                        {
                            const std::string itemName = UKismetTextLibrary::Conv_TextToString(itemDesc->Title).ToString();
                            Drawing::DrawString(itemName, { bottomPosition.X, bottomPosition.Y + 15.f }, Drawing::Colour::White);
                        }
                    }
                }
            }
        }
    }
}
