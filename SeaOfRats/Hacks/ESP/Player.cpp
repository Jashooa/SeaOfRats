#include "Player.h"

#include "Hacks/Bones.h"
#include "Utilities/Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Player::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto player = reinterpret_cast<AAthenaPlayerCharacter*>(actor);

            // Check if me
            if (player == localPlayer)
            {
                return;
            }

            // Get distance
            const auto worldDistance = localPlayer->GetDistanceTo(actor);
            const auto distance = worldDistance * 0.01f;
            if (distance >= 500.f)
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
            auto colour = Utilities::Drawing::Colour::Red;

            // Check friendly
            if (UCrewFunctions::AreCharactersInSameCrew(reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer), player))
            {
                colour = Utilities::Drawing::Colour::Green;
            }

            // Draw box
            Utilities::Drawing::DrawBoundingRect(world, actor, colour);
            DrawBones(world, actor);

            /*auto namePlate = reinterpret_cast<UPlayerNameplateComponent*>(player->GetComponentByClass(UPlayerNameplateComponent::StaticClass()));
            bool isNameplateShown = (worldDistance < namePlate->VisibleUntilWorldDistanceNonCrew) && playerController->LineOfSightTo(actor, FVector(0.f, 0.f, 0.f), false);

            if (!isNameplateShown)
            {
                // Get name
                std::wstring name = player->PlayerState->PlayerName.c_str();
                const auto distance = static_cast<int>(worldDistance * 0.01f);
                name += L" [" + std::to_wstring(distance) + L"m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topPosition.X, topPosition.Y - 10.f);
                Utilities::Drawing::DrawString(hud, name, nameScreen, colour);
            }*/

            // Draw health bar
            if (const auto healthComponent = player->HealthComponent)
            {
                const auto healthCurrent = healthComponent->GetCurrentHealth();
                const auto healthMax = healthComponent->GetMaxHealth();
                Utilities::Drawing::DrawHealthBar({ topPosition.X, topPosition.Y -= 15.f }, healthCurrent, healthMax);
            }

            if (const auto playerState = player->PlayerState)
            {
                // Get name
                auto name = playerState->PlayerName.ToString();

                if (name.empty())
                {
                    name = "Player";
                }

                name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

                // Draw name
                Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
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
                            const auto itemName = itemDesc->Title.DisplayString->ToString();
                            Utilities::Drawing::DrawString(itemName, { bottomPosition.X, bottomPosition.Y += 15.f }, Utilities::Drawing::Colour::White);
                        }
                    }
                }
            }
        }
    }
}
