#include "ESP.h"

#include <cmath>
#include <string>
#include <vector>

#include "include/SDK/SDK.h"
#include "include/spdlog/spdlog.h"

#include "Config.h"
#include "Drawing.h"
#include "Hacks/Bones.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        /*void DrawBarrel(UWorld* world, AActor* actor)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
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
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.f);
                Drawing::DrawString(hud, name, nameScreen, Drawing::Colour::White);
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

                            FVector2D itemNameScreen = FVector2D(topScreen.X, nameScreen.Y + 15.f * (i + 1));
                            Drawing::DrawString(hud, itemName, itemNameScreen, Drawing::Colour::White);
                        }
                    }
                }
            }
        }*/

        /*void DrawShipwreck(UWorld* world, AActor* actor)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto shipwreck = reinterpret_cast<AShipwreck*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            location.Z = 100.f;
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
            FVector2D nameScreen = FVector2D(screen.X, screen.Y - 10.f);
            Drawing::DrawString(hud, name, nameScreen, Drawing::Colour::White);
        }*/

        /*void DrawEvent(UWorld* world, AActor* actor)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto event = reinterpret_cast<AGameplayEventSignal*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            location.Z = 100.f;
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }
            Drawing::DrawBoundingBox(client, hud, actor, Drawing::Colour::White);

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
            FVector2D nameScreen = FVector2D(screen.X, screen.Y - 10.f);
            Drawing::DrawString(hud, name, nameScreen, Drawing::Colour::White);
        }*/

        /*void DrawDebug(UWorld* world, AActor* actor)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;

            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            std::string name = actor->GetName();
            if (name.find("_") != std::string::npos)
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
                return;
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
            Drawing::DrawString(name, screen, Drawing::Colour::Red);
        }*/
    }
}
