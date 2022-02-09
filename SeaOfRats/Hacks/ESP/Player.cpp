#include "Player.h"

#include "Drawing.h"
#include "Hacks/Bones.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawPlayer(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto player = reinterpret_cast<AAthenaPlayerCharacter*>(actor);

            // Check if me
            if (player == localPlayer)
            {
                return;
            }

            // Check if dead
            if (player->IsDead())
            {
                return;
            }

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
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
            ImU32 colour = Drawing::Colour::Red;

            // Check friendly
            if (UCrewFunctions::AreCharactersInSameCrew(reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer), player))
            {
                colour = Drawing::Colour::Green;
            }

            // Draw box
            Drawing::DrawBoundingRect(world, actor, colour);
            DrawBones(world, actor);

            // Get distance
            const float worldDistance = localPlayer->GetDistanceTo(actor);

            /*auto namePlate = reinterpret_cast<UPlayerNameplateComponent*>(player->GetComponentByClass(UPlayerNameplateComponent::StaticClass()));
            bool isNameplateShown = (worldDistance < namePlate->VisibleUntilWorldDistanceNonCrew) && playerController->LineOfSightTo(actor, FVector(0.f, 0.f, 0.f), false);

            if (!isNameplateShown)
            {
                // Get name
                std::wstring name = player->PlayerState->PlayerName.c_str();
                int32_t distance = static_cast<int32_t>(worldDistance * 0.01f);
                name += L" [" + std::to_wstring(distance) + L"m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topPosition.X, topPosition.Y - 10.f);
                Drawing::DrawString(hud, name, nameScreen, colour);
            }*/

            if (const auto playerState = player->PlayerState)
            {
                // Get name
                std::string name = playerState->PlayerName.ToString();
                const int32_t distance = static_cast<int32_t>(worldDistance * 0.01f);
                name += " [" + std::to_string(distance) + "m]";

                // Draw name
                Drawing::DrawString(name, { topPosition.X, topPosition.Y - 30.f }, colour);
            }

            // Draw health bar
            if (const auto healthComponent = player->HealthComponent)
            {
                const float healthCurrent = healthComponent->GetCurrentHealth();
                const float healthMax = healthComponent->GetMaxHealth();
                Drawing::DrawHealthBar({ topPosition.X, topPosition.Y - 15.f }, healthCurrent, healthMax);
            }

            // Draw item info
            if (const auto wieldedItemComponent = player->WieldedItemComponent)
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
