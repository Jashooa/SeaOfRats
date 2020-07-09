#include "ESP.h"

#include <cmath>
#include <string>
#include <vector>

#include "spdlog/spdlog.h"

#include "Drawing.h"
#include "SDK.hpp"

using namespace SDK;

namespace Hacks
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

        // Check if on-screen
        auto location = player->K2_GetActorLocation();
        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }

        // Check friendly
        bool friendly = UCrewFunctions::AreCharactersInSameCrew(reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer), player);
        FLinearColor colour = Drawing::Colour::Red;
        if (friendly)
        {
            colour = Drawing::Colour::Green;
        }
        Drawing::DrawBoundingBox(client, hud, actor, colour);

        int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);

        // Get coordinates for name
        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);
        auto nameLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z + 10.0f);
        FVector2D nameScreen;
        if (playerController->ProjectWorldLocationToScreen(nameLocation, &nameScreen))
        {
            // Draw name
            std::wstring playerName = player->PlayerState->PlayerName.c_str();
            std::wstring playerNameText = playerName + L" [" + std::to_wstring(distance) + L"m]";
            Drawing::DrawActorString(hud, playerNameText, nameScreen, colour);
        }

        // Get coordinates for health bar
        auto healthLocation = FVector(origin.X, origin.Y, origin.Z - extent.Z - 10.0f);
        FVector2D healthScreen;
        if (playerController->ProjectWorldLocationToScreen(healthLocation, &healthScreen))
        {

        }

        // Get coordinates for held item
        auto itemLocation = FVector(origin.X, origin.Y, origin.Z - extent.Z - 25.0f);
        FVector2D itemScreen;
        if (playerController->ProjectWorldLocationToScreen(itemLocation, &itemScreen))
        {
            // Draw item info
            auto wieldedItem = reinterpret_cast<AWieldableItem*>(player->WieldedItemComponent->CurrentlyWieldedItem);
            if (wieldedItem)
            {
                auto itemDesc = wieldedItem->ItemInfo->Desc;
                if (itemDesc)
                {
                    std::wstring itemName = UKismetTextLibrary::Conv_TextToString(itemDesc->Title).c_str();
                    Drawing::DrawActorString(hud, itemName, itemScreen, Drawing::Colour::White);
                }
            }
        }
    }

    void DrawSkeleton(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;
        auto skeleton = reinterpret_cast<AAthenaAICharacter*>(actor);

        // Check if on-screen
        auto location = skeleton->K2_GetActorLocation();
        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }
        Drawing::DrawBoundingBox(client, hud, actor, Drawing::Colour::White);

        int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);

        // Get coordinates for name
        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);
        auto nameLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z + 10.0f);
        FVector2D nameScreen;
        if (playerController->ProjectWorldLocationToScreen(nameLocation, &nameScreen))
        {
            // Draw name
            std::wstring skeletonName = L"Skeleton";
            if (skeleton->AssignedMesh)
            {
                std::string meshName = skeleton->AssignedMesh->GetName();
                if (meshName.find("nme_skellyshadow") != std::string::npos)
                {
                    skeletonName = L"Shadow " + skeletonName;

                    if (skeleton->TeamColorTexture)
                    {
                        std::string skeletonColour = skeleton->TeamColorTexture->GetName();
                        if (skeletonColour.find("venom") != std::string::npos)
                        {
                            skeletonName = L"Purple " + skeletonName;
                        }
                        else if (skeletonColour.find("shark") != std::string::npos)
                        {
                            skeletonName = L"Blue " + skeletonName;
                        }
                        else if (skeletonColour.find("lightning") != std::string::npos)
                        {
                            skeletonName = L"White " + skeletonName;
                        }
                        else if (skeletonColour.find("player") != std::string::npos)
                        {
                            skeletonName = L"Pink " + skeletonName;
                        }
                        else if (skeletonColour.find("skeleton") != std::string::npos)
                        {
                            skeletonName = L"Green " + skeletonName;
                        }
                        else
                        {
                            skeletonName = std::wstring(skeletonColour.begin(), skeletonColour.end());
                        }
                    }
                }
                else if (meshName.find("nme_skelly_gen") == std::string::npos)
                {
                    skeletonName = std::wstring(meshName.begin(), meshName.end());
                }
            }

            std::wstring skeletonText = skeletonName + L" [" + std::to_wstring(distance) + L"m]";
            Drawing::DrawActorString(hud, skeletonText, nameScreen, Drawing::Colour::White);
        }
    }

    void DrawShip(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;
        auto ship = reinterpret_cast<AShip*>(actor);

        auto location = ship->K2_GetRootComponent()->K2_GetComponentLocation();
        location.Z += 25 * 100;

        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }
        //Drawing::DrawBoundingBox(client, hud, actor, Drawing::Colour::White);

        int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
        if (distance >= 1300)
        {
            return;
        }

        std::string name = actor->GetName();
        std::wstring shipType;
        if (name.find("Large") != std::string::npos)
        {
            shipType = L"Galleon";
        }
        else if (name.find("Medium") != std::string::npos)
        {
            shipType = L"Brigantine";
        }
        else if (name.find("Small") != std::string::npos)
        {
            shipType = L"Sloop";
        }

        if (name.find("AI") != std::string::npos)
        {
            shipType = L"Skeleton " + shipType;
        }

        if (UCrewFunctions::IsActorMemberOfCharactersCrew(ship, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
        {
            shipType = L"My " + shipType;
        }

        std::wstring shipText = shipType + L" [" + std::to_wstring(distance) + L"m]";
        Drawing::DrawActorString(hud, shipText, screen, Drawing::Colour::White);
    }

    void DrawShipFar(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;
        auto ship = reinterpret_cast<AShipNetProxy*>(actor);

        auto location = ship->K2_GetRootComponent()->K2_GetComponentLocation();
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

        std::string name = actor->GetName();
        std::wstring shipType;
        if (name.find("Large") != std::string::npos)
        {
            shipType = L"Galleon";
        }
        else if (name.find("Medium") != std::string::npos)
        {
            shipType = L"Brigantine";
        }
        else if (name.find("Small") != std::string::npos)
        {
            shipType = L"Sloop";
        }

        if (name.find("AI") != std::string::npos)
        {
            shipType = L"Skeleton " + shipType;
        }

        if (UCrewFunctions::IsActorMemberOfCharactersCrew(ship, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
        {
            shipType = L"My " + shipType;
        }

        std::wstring shipText = shipType + L" [" + std::to_wstring(distance) + L"m]";
        Drawing::DrawActorString(hud, shipText, screen, Drawing::Colour::White);
    }

    void DrawItem(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;

        /*auto location = actor->K2_GetRootComponent()->K2_GetComponentLocation();
        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }*/

        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);
        auto nameLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z + 10.0f);
        FVector2D nameScreen;
        if (!playerController->ProjectWorldLocationToScreen(nameLocation, &nameScreen))
        {
            return;
        }

        int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);

        auto item = reinterpret_cast<ABootyProxy*>(actor);
        auto itemInfo = reinterpret_cast<ABootyItemInfo*>(item->ItemInfo);
        if (!itemInfo)
        {
            spdlog::warn("iteminfo null");
            return;
        }

        std::wstring itemName = UKismetTextLibrary::Conv_TextToString(itemInfo->Desc->Title).c_str();

        auto rarity = itemInfo->Rarity;
        FLinearColor colour = Drawing::Colour::Blue;
        if (rarity == "Common")
        {
            colour = Drawing::Colour::Grey;
        }
        else if (rarity == "Rare")
        {
            colour = Drawing::Colour::Green;
        }
        else if (rarity == "Legendary")
        {
            colour = Drawing::Colour::Purple;
        }
        else if (rarity == "Mythical")
        {
            colour = Drawing::Colour::Orange;
        }
        
        std::wstring itemText = itemName + L" [" + std::to_wstring(distance) + L"m]";
        Drawing::DrawActorString(hud, itemText, nameScreen, colour);
    }

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
            Drawing::DrawActorString(hud, pinText, screen, Drawing::Colour::White);
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
            return;*/
        if (name.find("cmn") != std::string::npos)
            return;
        if (name.find("wsp") != std::string::npos)
            return;
        if (name.find("water") != std::string::npos)
            return;
        if (name.find("Light") != std::string::npos)
            return;
        if (name.find("vfx") != std::string::npos)
            return;
        if (name.find("ske") != std::string::npos)
            return;
        if (name.find("wld") != std::string::npos)
            return;
        if (name.find("dvr") != std::string::npos)
            return;
        if (name.find("ref") != std::string::npos)
            return;
        if (name.find("volume") != std::string::npos)
            return;
        if (name.find("Volume") != std::string::npos)
            return;
        if (name.find("rocks") != std::string::npos)
            return;
        if (name.find("jetty") != std::string::npos)
            return;
        if (name.find("shop") != std::string::npos)
            return;
        if (name.find("bp") != std::string::npos)
            return;
        if (name.find("bld") != std::string::npos)
            return;
        if (name.find("bsp") != std::string::npos)
            return;
        if (name.find("Nav") != std::string::npos)
            return;
        if (name.find("Water") != std::string::npos)
            return;
        if (name.find("FishCreature") != std::string::npos)
            return;

        name = actor->GetFullName();
        std::wstring namew(name.begin(), name.end());
        Drawing::DrawActorString(hud, namew, screen, Drawing::Colour::Red);
    }

    void RenderESP(UGameViewportClient* client, AHUD* hud)
    {
        UWorld* world = client->World;
        if (!world)
        {
            spdlog::warn("World Null");
            return;
        }

        auto levels = world->Levels;

        for (int32_t i = 6; i < levels.Num(); ++i)
        {
            auto actors = levels[i]->AActors;

            for (int32_t j = 0; j < actors.Num(); ++j)
            {
                AActor* actor = actors[j];

                if (!actor)
                {
                    continue;
                }
            }
        }

        ULevel* level = world->PersistentLevel;
        if (!level)
        {
            spdlog::warn("Level Null");
            return;
        }

        auto actors = level->AActors;

        for (int32_t i = 0; i < actors.Num(); ++i)
        {
            AActor* actor = actors[i];

            if (!actor)
            {
                continue;
            }

            if (actor == client->GameInstance->LocalPlayers[0]->PlayerController)
            {
                continue;
            }

            if (actor->IsA(AAthenaPlayerCharacter::StaticClass()))
            {
                spdlog::debug("DrawPlayer Before");
                DrawPlayer(client, hud, actor);
                spdlog::debug("DrawPlayer After");
                continue;
            }

            if (actor->IsA(AAthenaAICharacter::StaticClass()))
            {
                spdlog::debug("DrawSkeleton Before");
                DrawSkeleton(client, hud, actor);
                spdlog::debug("DrawSkeleton After");
                continue;
            }

            if (actor->IsA(AShip::StaticClass()))
            {
                spdlog::debug("DrawShip Before");
                DrawShip(client, hud, actor);
                spdlog::debug("DrawShip After");
                continue;
            }

            if (actor->IsA(AShipNetProxy::StaticClass()))
            {
                spdlog::debug("DrawShipFar Before");
                DrawShipFar(client, hud, actor);
                spdlog::debug("DrawShipFar After");
                continue;
            }

            if (actor->IsA(ABootyProxy::StaticClass()))
            {
                spdlog::debug("DrawItem Before");
                DrawItem(client, hud, actor);
                spdlog::debug("DrawItem After");
                continue;
            }

            if (actor->IsA(AMapTable::StaticClass()))
            {
                spdlog::debug("DrawMapPins Before");
                DrawMap(client, hud, actor);
                spdlog::debug("DrawMapPins After");
                continue;
            }

            //DrawDebug(client, hud, actor);
        }
    }
}