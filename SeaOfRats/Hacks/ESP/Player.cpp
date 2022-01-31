#include "Player.h"

#include "Drawing.h"
#include "Hacks/Bones.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawPlayer(UWorld* world, AActor* actor)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto player = reinterpret_cast<AAthenaPlayerCharacter*>(actor);

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
            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Check friendly
            bool friendly = UCrewFunctions::AreCharactersInSameCrew(reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer), player);
            ImU32 colour = Drawing::Colour::Red;
            if (friendly)
            {
                colour = Drawing::Colour::Green;
            }
            //Drawing::DrawBoundingBox(world, actor, colour);
            DrawBones(world, actor);

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {

                float worldDistance = localPlayer->GetDistanceTo(actor);

                /*auto namePlate = reinterpret_cast<UPlayerNameplateComponent*>(player->GetComponentByClass(UPlayerNameplateComponent::StaticClass()));
                bool isNameplateShown = (worldDistance < namePlate->VisibleUntilWorldDistanceNonCrew) && playerController->LineOfSightTo(actor, FVector(0.0f, 0.0f, 0.0f), false);

                if (!isNameplateShown)
                {
                    // Get name
                    std::wstring name = player->PlayerState->PlayerName.c_str();
                    int32_t distance = static_cast<int32_t>(worldDistance * 0.01f);
                    name += L" [" + std::to_wstring(distance) + L"m]";

                    // Draw name
                    FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                    Drawing::DrawString(hud, name, nameScreen, colour);
                }*/

                // Get name
                std::string name = player->PlayerState->PlayerName.ToString();
                int32_t distance = static_cast<int32_t>(worldDistance * 0.01f);
                name += " [" + std::to_string(distance) + "m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Drawing::DrawString(name, nameScreen, colour);
            }

            // Get bottom coordinates
            auto bottomLocation = FVector(origin.X, origin.Y, origin.Z - extent.Z);
            FVector2D bottomScreen;
            if (playerController->ProjectWorldLocationToScreen(bottomLocation, &bottomScreen))
            {
                // Draw health bar
                auto healthComponent = player->HealthComponent;
                if (healthComponent)
                {
                    FVector2D healthScreen = FVector2D(bottomScreen.X, bottomScreen.Y + 10.0f);
                    FVector2D healthTopLeft = FVector2D(healthScreen.X - 50.0f, healthScreen.Y);
                    FVector2D healthBottomRight = FVector2D(healthScreen.X + 50.0f, healthScreen.Y + 5.0f);
                    Drawing::DrawHealthBar(healthTopLeft, healthBottomRight, healthComponent->GetCurrentHealth(), healthComponent->GetMaxHealth());
                }

                // Draw item info
                auto wieldedItemComponent = player->WieldedItemComponent;
                if (wieldedItemComponent)
                {
                    auto wieldedItem = reinterpret_cast<AWieldableItem*>(wieldedItemComponent->CurrentlyWieldedItem);
                    if (wieldedItem)
                    {
                        auto itemInfo = wieldedItem->ItemInfo;
                        if (itemInfo)
                        {
                            auto itemDesc = itemInfo->Desc;
                            if (itemDesc)
                            {
                                std::string itemName = UKismetTextLibrary::Conv_TextToString(itemDesc->Title).ToString();

                                FVector2D itemScreen = FVector2D(bottomScreen.X, bottomScreen.Y + 25.0f);
                                Drawing::DrawString(itemName, itemScreen, Drawing::Colour::White);
                            }
                        }
                    }
                }
            }
        }
    }
}
