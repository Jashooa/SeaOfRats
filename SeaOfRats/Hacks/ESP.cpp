#include "ESP.h"

#include <cmath>
#include <string>
#include <vector>

#include "include/SDK/SDK.h"
#include "include/spdlog/spdlog.h"

#include "Config.h"
#include "Hacks/Bones.h"
#include "Render/Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void DrawPlayer(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
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
            FLinearColor colour = Render::Drawing::Colour::Red;
            if (friendly)
            {
                colour = Render::Drawing::Colour::Green;
            }
            //Drawing::DrawBoundingBox(client, hud, actor, colour);
            DrawBones(client, hud, actor);

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
                    Render::Drawing::DrawActorString(hud, name, nameScreen, colour);
                }*/

                // Get name
                std::wstring name = player->PlayerState->PlayerName.c_str();
                int32_t distance = static_cast<int32_t>(worldDistance * 0.01f);
                name += L" [" + std::to_wstring(distance) + L"m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Render::Drawing::DrawActorString(hud, name, nameScreen, colour);
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
                    Render::Drawing::DrawHealthBar(hud, healthTopLeft, healthBottomRight, healthComponent->GetCurrentHealth(), healthComponent->GetMaxHealth());
                }

                // Draw item info
                auto wieldedItem = reinterpret_cast<AWieldableItem*>(player->WieldedItemComponent->CurrentlyWieldedItem);
                if (wieldedItem)
                {
                    auto itemInfo = wieldedItem->ItemInfo;
                    if (itemInfo)
                    {
                        auto itemDesc = itemInfo->Desc;
                        if (itemDesc)
                        {
                            std::wstring itemName = UKismetTextLibrary::Conv_TextToString(itemDesc->Title).c_str();

                            FVector2D itemScreen = FVector2D(bottomScreen.X, bottomScreen.Y + 25.0f);
                            Render::Drawing::DrawActorString(hud, itemName, itemScreen, Render::Drawing::Colour::White);
                        }
                    }
                }
            }
        }

        void DrawSkeleton(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto skeleton = reinterpret_cast<AAthenaAICharacter*>(actor);

            // Check if dead
            if (skeleton->IsDead())
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
            //Render::Drawing::DrawBoundingBox(client, hud, actor, Render::Drawing::Colour::White);
            //Render::Drawing::DrawBoundingRect(client, hud, actor, Render::Drawing::Colour::White);
            DrawBones(client, hud, actor);

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get name
                std::wstring name = L"Skeleton";
                /*if (skeleton->AssignedMesh)
                {
                    std::string meshName = skeleton->AssignedMesh->GetName();
                    if (meshName.find("skellyshadow") != std::string::npos)
                    {
                        name = L"Shadow " + name;
                    }
                    else if (meshName.find("skellymetal") != std::string::npos)
                    {
                        name = L"Metal " + name;
                    }
                    else if (meshName.find("skellyplant") != std::string::npos)
                    {
                        name = L"Plant " + name;
                    }
                    else if (meshName.find("skellyash") != std::string::npos)
                    {
                        name = L"Ashen " + name;
                    }

                    if (meshName.find("_cap_") != std::string::npos)
                    {
                        name += L" Captain";
                    }

                    name += L" Mesh: " + std::wstring(meshName.begin(), meshName.end());

                    if (skeleton->TeamColorTexture)
                    {
                        std::string skeletonColour = skeleton->TeamColorTexture->GetName();
                        /*if (skeletonColour.find("venom") != std::string::npos)
                        {
                            name = L"Purple " + name;
                        }
                        else if (skeletonColour.find("shark") != std::string::npos)
                        {
                            name = L"Blue " + name;
                        }
                        else if (skeletonColour.find("lightning") != std::string::npos)
                        {
                            name = L"White " + name;
                        }
                        else if (skeletonColour.find("player") != std::string::npos)
                        {
                            name = L"Pink " + name;
                        }
                        else if (skeletonColour.find("skeleton") != std::string::npos)
                        {
                            name = L"Green " + name;
                        }*/
                        /*if (skeletonColour.find("_red_") != std::string::npos)
                        {
                            name = L"Red " + name;
                        }
                        else if (skeletonColour.find("_green_") != std::string::npos)
                        {
                            name = L"Green " + name;
                        }
                        else if (skeletonColour.find("_blue_") != std::string::npos)
                        {
                            name = L"Blue " + name;
                        }
                        else
                        {
                            name += L" Texture: " + std::wstring(skeletonColour.begin(), skeletonColour.end());
                        }
                    }
                }*/

                float worldDistance = localPlayer->GetDistanceTo(actor);

                /*auto namePlate = reinterpret_cast<UAINameplateComponent*>(skeleton->GetComponentByClass(UAINameplateComponent::StaticClass()));
                bool isNameplateShown = false;
                if (!namePlate->DisplayNameAsString.IsEmpty())
                {
                    isNameplateShown = (worldDistance < namePlate->VisibleUntilWorldDistance) && playerController->LineOfSightTo(actor, FVector(0.0f, 0.0f, 0.0f), false);
                    std::wstring namePlateText = namePlate->DisplayNameAsString.c_str();
                    name = namePlateText + L" " + name;
                }

                if (!isNameplateShown)
                {
                    int32_t distance = static_cast<int32_t>(worldDistance * 0.01f);
                    name += L" [" + std::to_wstring(distance) + L"m]";

                    // Draw name
                    FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                    Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);
                }*/
                int32_t distance = static_cast<int32_t>(worldDistance * 0.01f);
                name += L" [" + std::to_wstring(distance) + L"m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);
            }

            // Get bottom coordinates
            auto bottomLocation = FVector(origin.X, origin.Y, origin.Z - extent.Z);
            FVector2D bottomScreen;
            if (playerController->ProjectWorldLocationToScreen(bottomLocation, &bottomScreen))
            {

                // Draw health bar
                /*auto healthComponent = skeleton->HealthComponent;
                if (healthComponent)
                {
                    FVector2D healthScreen = FVector2D(bottomScreen.X, bottomScreen.Y + 10.0f);
                    FVector2D healthTopLeft = FVector2D(healthScreen.X - 50.0f, healthScreen.Y);
                    FVector2D healthBottomRight = FVector2D(healthTopLeft.X + 100.0f, healthTopLeft.Y + 5.0f);
                    Drawing::DrawHealthBar(hud, healthTopLeft, healthBottomRight, healthComponent->GetCurrentHealth(), healthComponent->GetMaxHealth());
                }*/

                // Draw item info
                auto wieldedItem = reinterpret_cast<AWieldableItem*>(skeleton->WieldedItemComponent->CurrentlyWieldedItem);
                if (wieldedItem)
                {
                    auto itemInfo = wieldedItem->ItemInfo;
                    if (itemInfo)
                    {
                        auto itemDesc = itemInfo->Desc;
                        if (itemDesc)
                        {
                            std::wstring itemName = UKismetTextLibrary::Conv_TextToString(itemDesc->Title).c_str();
                            FVector2D itemScreen = FVector2D(bottomScreen.X, bottomScreen.Y + 10.0f);
                            Render::Drawing::DrawActorString(hud, itemName, itemScreen, Render::Drawing::Colour::White);
                        }
                    }
                }
            }
        }

        /*void DrawShark(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto shark = reinterpret_cast<ASharkPawn*>(actor);

            switch (shark->AIControllerParams->TeamID)
            {
                case EAthenaAITeam::Sharks:
                    break;
                case EAthenaAITeam::TinyShark:
                    break;
            }

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get name
                std::wstring name = L"Shark";
                std::string actorName = actor->GetName();
                name += L" " + std::wstring(actorName.begin(), actorName.end());

                int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                name += L" [" + std::to_wstring(distance) + L"m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 25.0f);
                Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);

                // Draw health bar
                auto healthComponent = shark->HealthComponent;
                if (healthComponent)
                {
                    FVector2D healthScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                    FVector2D healthTopLeft = FVector2D(healthScreen.X - 50.0f, healthScreen.Y);
                    FVector2D healthBottomRight = FVector2D(healthTopLeft.X + 100.0f, healthTopLeft.Y + 5.0f);
                    Render::Drawing::DrawHealthBar(hud, healthTopLeft, healthBottomRight, healthComponent->GetCurrentHealth(), healthComponent->GetMaxHealth());
                }
            }
        }*/

        /*void DrawKraken(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto kraken = reinterpret_cast<AKraken*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }
            Render::Drawing::DrawBoundingBox(client, hud, actor, Render::Drawing::Colour::White);

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get name
                std::wstring name = L"Kraken";
                std::string actorName = actor->GetName();
                name += L" " + std::wstring(actorName.begin(), actorName.end());

                int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                name += L" [" + std::to_wstring(distance) + L"m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 25.0f);
                Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);

                // Draw tentacles remaining
                std::wstring tentaclesRemaining = L"Tentacles Remaining: " + std::to_wstring(kraken->NumTentaclesRemaining);
                FVector2D tentaclesScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Render::Drawing::DrawActorString(hud, tentaclesRemaining, tentaclesScreen, Render::Drawing::Colour::White);
            }
        }

        void DrawKrakenTentacle(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto tentacle = reinterpret_cast<AKrakenTentacle*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }
            Render::Drawing::DrawBoundingBox(client, hud, actor, Render::Drawing::Colour::White);

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get name
                std::wstring name = L"Kraken Tentacle";
                std::string actorName = actor->GetName();
                name += L" " + std::wstring(actorName.begin(), actorName.end());

                int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                name += L" [" + std::to_wstring(distance) + L"m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 25.0f);
                Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);

                // Draw health bar
                auto healthComponent = tentacle->HealthComponent;
                if (healthComponent)
                {
                    FVector2D healthScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                    FVector2D healthTopLeft = FVector2D(healthScreen.X - 50.0f, healthScreen.Y);
                    FVector2D healthBottomRight = FVector2D(healthTopLeft.X + 100.0f, healthTopLeft.Y + 5.0f);
                    Render::Drawing::DrawHealthBar(hud, healthTopLeft, healthBottomRight, healthComponent->GetCurrentHealth(), healthComponent->GetMaxHealth());
                }
            }
        }*/

        void DrawAnimal(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto animal = reinterpret_cast<AFauna*>(actor);

            /*switch (animal->AIControllerParams->TeamID)
            {
                case EAthenaAITeam::Fauna_Chickens:
                    break;
                case EAthenaAITeam::Fauna_Pigs:
                    break;
                case EAthenaAITeam::Fauna_Snakes:
                    break;
            }*/

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get name
                std::wstring name = UKismetTextLibrary::Conv_TextToString(animal->DisplayName).c_str();
                int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                name += L" [" + std::to_wstring(distance) + L"m]";
                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);
            }
        }

        void DrawMermaid(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto mermaid = reinterpret_cast<AMermaid*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get name
                std::wstring name = L"Mermaid ";

                // Check if my mermaid
                auto localCrewId = UCrewFunctions::GetCrewIdFromActor(client->World, localPlayer);
                auto crewIds = mermaid->GetCrewIdsResponsibleForSavingAsCopy();
                for (int32_t i = 0; i < crewIds.Num(); ++i)
                {
                    if (UKismetGuidLibrary::EqualEqual_GuidGuid(crewIds[i], localCrewId))
                    {
                        name = L"My " + name;
                    }
                }

                int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                name += L" [" + std::to_wstring(distance) + L"m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);
            }
        }

        void DrawShip(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto ship = reinterpret_cast<AShip*>(actor);

            auto location = actor->K2_GetActorLocation();
            location.Z += 25 * 100;

            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            if (distance >= 1300)
            {
                return;
            }

            //Render::Drawing::DrawBoundingBox(client, hud, actor, Render::Drawing::Colour::White);

            std::string actorName = actor->GetName();
            std::wstring name = L"Ship";
            if (actorName.find("Large") != std::string::npos)
            {
                name = L"Galleon";
            }
            else if (actorName.find("Medium") != std::string::npos)
            {
                name = L"Brigantine";
            }
            else if (actorName.find("Small") != std::string::npos)
            {
                name = L"Sloop";
            }

            if (actorName.find("AI") != std::string::npos)
            {
                name = L"Skeleton " + name;
            }

            if (UCrewFunctions::IsActorMemberOfCharactersCrew(ship, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
            {
                name = L"My " + name;
            }

            name += L" [" + std::to_wstring(distance) + L"m]";

            FVector2D nameScreen = FVector2D(screen.X, screen.Y - 25.0f);
            Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);

            auto waterInfo = ship->GetInternalWater();
            if (waterInfo)
            {
                FVector2D healthScreen = FVector2D(screen.X, screen.Y - 10.0f);
                FVector2D healthTopLeft = FVector2D(healthScreen.X - 50.0f, healthScreen.Y);
                FVector2D healthBottomRight = FVector2D(healthScreen.X + 50.0f, healthScreen.Y + 5.0f);
                float waterMax = waterInfo->InternalWaterParams.MaxWaterAmount;
                float waterLevel = waterMax - waterInfo->WaterAmount;
                Render::Drawing::DrawHealthBar(hud, healthTopLeft, healthBottomRight, waterLevel, waterMax);
            }
        }

        void DrawShipFar(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto ship = reinterpret_cast<AShipNetProxy*>(actor);

            auto location = actor->K2_GetActorLocation();
            location.Z += 25 * 100;

            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            if (distance < 1300)
            {
                return;
            }

            std::string actorName = actor->GetName();
            std::wstring name = L"Ship";
            if (actorName.find("Large") != std::string::npos)
            {
                name = L"Galleon";
            }
            else if (actorName.find("Medium") != std::string::npos)
            {
                name = L"Brigantine";
            }
            else if (actorName.find("Small") != std::string::npos)
            {
                name = L"Sloop";
            }

            if (actorName.find("AI") != std::string::npos)
            {
                name = L"Skeleton " + name;
            }

            if (UCrewFunctions::IsActorMemberOfCharactersCrew(ship, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
            {
                name = L"My " + name;
            }

            name += L" [" + std::to_wstring(distance) + L"m]";

            FVector2D nameScreen = FVector2D(screen.X, screen.Y - 10.0f);
            Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);
        }

        /*void DrawGhostShip(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto ship = reinterpret_cast<AAggressiveGhostShip*>(actor);

            auto location = actor->K2_GetActorLocation();
            location.Z += 25 * 100;

            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            std::wstring name = L"Ghost Ship";
            switch (ship->GetShipType())
            {
                case EAggressiveGhostShipType::EAggressiveGhostShipType__Grunt:
                    name += L"Grunt Ship";
                    break;
                case EAggressiveGhostShipType::EAggressiveGhostShipType__FormationGrunt:
                    name += L"Ghost Flagship";
                    break;
                case EAggressiveGhostShipType::EAggressiveGhostShipType__FormationLeader:
                    name += L"Ghost Captain Ship";
                    break;
                case EAggressiveGhostShipType::EAggressiveGhostShipType__CaptainFormationGrunt:
                    name += L"Ashen Dragon Ship";
                    break;
                case EAggressiveGhostShipType::EAggressiveGhostShipType__Captain:
                    name += L"The Burning Blade";
                    break;
            }

            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += L" [" + std::to_wstring(distance) + L"m]";

            FVector2D nameScreen = FVector2D(screen.X, screen.Y - 25.0f);
            Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);

            // Draw hits remaining
            std::wstring hitsRemaining = L"Hits Remaining: " + std::to_wstring(ship->NumShotsLeftToKill);
            FVector2D hitsScreen = FVector2D(screen.X, screen.Y - 10.0f);
            Render::Drawing::DrawActorString(hud, hitsRemaining, hitsScreen, Render::Drawing::Colour::White);
        }*/

        /*void DrawRowboat(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto rowboat = reinterpret_cast<ARowboat*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get name
                std::wstring name = L"Rowboat";

                std::string actorName = actor->GetName();
                if (actorName.find("Harpoon") != std::string::npos)
                {
                    name = L"Harpoon " + name;
                }

                int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                name += L" [" + std::to_wstring(distance) + L"m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);
            }
        }*/

        void DrawItem(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto item = reinterpret_cast<ABootyProxy*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get item info
            auto itemInfo = reinterpret_cast<ABootyItemInfo*>(item->ItemInfo);
            if (!itemInfo)
            {
                spdlog::warn("ItemInfo null");
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get colour
                std::string rarity = itemInfo->Rarity.GetName();
                FLinearColor colour = Render::Drawing::Colour::Blue;
                if (rarity == "Common")
                {
                    colour = Render::Drawing::Colour::Grey;
                }
                else if (rarity == "Rare")
                {
                    colour = Render::Drawing::Colour::Green;
                }
                else if (rarity == "Legendary")
                {
                    colour = Render::Drawing::Colour::Purple;
                }
                else if (rarity == "Mythical")
                {
                    colour = Render::Drawing::Colour::Orange;
                }

                // Get name
                std::wstring name = UKismetTextLibrary::Conv_TextToString(itemInfo->Desc->Title).c_str();
                int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                name += L" [" + std::to_wstring(distance) + L"m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Render::Drawing::DrawActorString(hud, name, nameScreen, colour);
            }
        }

        /*void DrawBarrel(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto barrel = reinterpret_cast<AStorageContainer*>(actor);

            if (actor->IsA(ABuoyantStorageContainer::StaticClass()))
            {
                return;
            };

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(false, &origin, &extent);

            // Get top coordinates
            auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get name
                std::wstring name = L"Barrel";
                if (actor->IsA(ABuoyantStorageContainer::StaticClass()))
                {
                    name = L"Water " + name;
                }

                int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                name += L" [" + std::to_wstring(distance) + L"m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);
                auto storageComponent = reinterpret_cast<UStorageContainerComponent*>(actor->GetComponentByClass(UStorageContainerComponent::StaticClass()));

                if (storageComponent)
                {
                    auto nodes = storageComponent->ContainerNodes.ContainerNodes;
                    for (int32_t i = 0; i < nodes.Num(); ++i)
                    {
                        auto node = nodes[i];
                        UItemDesc* itemDesc = node.ItemDesc->CreateDefaultObject<UItemDesc>();
                        if (itemDesc)
                        {
                            if (UKismetTextLibrary::TextIsEmpty(itemDesc->Title))
                            {
                                continue;
                            }
                            std::wstring itemName = UKismetTextLibrary::Conv_TextToString(itemDesc->Title).c_str();
                            itemName = std::to_wstring(node.NumItems) + L"x " + itemName;

                            FVector2D itemNameScreen = FVector2D(topScreen.X, nameScreen.Y + 15.0f * (i + 1));
                            Render::Drawing::DrawActorString(hud, itemName, itemNameScreen, Render::Drawing::Colour::White);
                        }
                    }
                }
            }
        }*/

        /*void DrawShipwreck(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto shipwreck = reinterpret_cast<AShipwreck*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            location.Z = 100.0f;
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get name
            //std::wstring name = UKismetTextLibrary::Conv_TextToString(shipwreck->LocalisedName).c_str();
            std::wstring name = L"Shipwreck";

            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += L" [" + std::to_wstring(distance) + L"m]";

            // Draw name
            FVector2D nameScreen = FVector2D(screen.X, screen.Y - 10.0f);
            Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);
        }*/

        /*void DrawStorm(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto storm = reinterpret_cast<AStorm*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            location.Z = 100.0f;
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }
            Render::Drawing::DrawBoundingBox(client, hud, actor, Render::Drawing::Colour::White);

            // Get name
            std::wstring name = storm->SubjectName.c_str();

            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += L" [" + std::to_wstring(distance) + L"m]";

            // Draw name
            FVector2D nameScreen = FVector2D(screen.X, screen.Y - 10.0f);
            Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);
        }*/

        /*void DrawEvent(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto event = reinterpret_cast<AGameplayEventSignal*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            location.Z = 100.0f;
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }
            Render::Drawing::DrawBoundingBox(client, hud, actor, Render::Drawing::Colour::White);

            // Get name
            std::wstring name = L"Event";
            switch (event->EventType)
            {
                case EGameplayEventSignalType::EGameplayEventSignalType__SkellyFort:
                    name = L"Skeleton Fort";
                    break;
                case EGameplayEventSignalType::EGameplayEventSignalType__SkellyShip:
                    name = L"Skeleton Fleet";
                    break;
                case EGameplayEventSignalType::EGameplayEventSignalType__AshenLord:
                    name = L"Fort of the Damned";
                    break;
                case EGameplayEventSignalType::EGameplayEventSignalType__FlameheartGhostShips:
                    name = L"Ghost Fleet";
                    break;
            }

            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += L" [" + std::to_wstring(distance) + L"m]";

            // Draw name
            FVector2D nameScreen = FVector2D(screen.X, screen.Y - 10.0f);
            Render::Drawing::DrawActorString(hud, name, nameScreen, Render::Drawing::Colour::White);
        }*/

        void DrawMap(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto table = reinterpret_cast<AMapTable*>(actor);

            auto parentShip = actor->GetAttachParentActor();
            /*auto currentShip = reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)->GetCurrentShip();
            if (parentShip != currentShip)
            {
                return;
            }*/

            if (!UCrewFunctions::IsActorMemberOfCharactersCrew(parentShip, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
            {
                return;
            }

            auto pins = table->MapPins;

            for (int32_t i = 0; i < pins.Num(); ++i)
            {
                auto pin = pins[i];
                FVector location((pin.X * 100.0f), (pin.Y * 100.0f), 100.0f);

                FVector2D screen;
                if (!playerController->ProjectWorldLocationToScreen(location, &screen))
                {
                    continue;
                }

                int32_t distance = static_cast<int32_t>(UVectorMaths::Distance(localPlayer->RootComponent->K2_GetComponentLocation(), location) * 0.01f);
                std::wstring pinText = L"Map Pin [" + std::to_wstring(distance) + L"m]";
                Render::Drawing::DrawActorString(hud, pinText, screen, Render::Drawing::Colour::White);
            }
        }

        void DrawDebug(UGameViewportClient* client, AHUD* hud, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;

            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            std::string name = actor->GetName();
            /*if (name.find("_") != std::string::npos)
                return;
            if (name.find("cmn") != std::string::npos)
                return;
            if (name.find("wsp") != std::string::npos)
                return;
            if (name.find("vfx") != std::string::npos)
                return;
            if (name.find("ske") != std::string::npos)
                return;
            if (name.find("dvr") != std::string::npos)
                return;
            if (name.find("ref") != std::string::npos)
                return;
            if (name.find("bp") != std::string::npos)
                return;
            if (name.find("bld") != std::string::npos)
                return;
            if (name.find("bsp") != std::string::npos)
                return;*/
            if (name.find("wpn") != std::string::npos)
                return;
            if (name.find("tls") != std::string::npos)
                return;
            if (name.find("wld_feature") != std::string::npos)
                return;
            if (name.find("Copied") != std::string::npos)
                return;
            if (name.find("NavBlocker") != std::string::npos)
                return;
            if (name.find("NavMesh") != std::string::npos)
                return;
            if (name.find("Light") != std::string::npos)
                return;
            if (name.find("water") != std::string::npos)
                return;
            if (name.find("Water") != std::string::npos)
                return;
            if (name.find("rocks") != std::string::npos)
                return;
            if (name.find("jetty") != std::string::npos)
                return;
            if (name.find("shop") != std::string::npos)
                return;
            if (name.find("volume") != std::string::npos)
                return;
            if (name.find("Volume") != std::string::npos)
                return;
            if (name.find("NulVol") != std::string::npos)
                return;
            if (name.find("PhasedClusterRoot") != std::string::npos)
                return;
            if (name.find("StaticMeshActor") != std::string::npos)
                return;
            //name = actor->GetFullName();
            std::wstring namew(name.begin(), name.end());
            Render::Drawing::DrawActorString(hud, namew, screen, Render::Drawing::Colour::Red);
        }
    }
}
