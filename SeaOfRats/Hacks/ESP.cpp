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
        auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(playerController->Pawn);
        auto player = reinterpret_cast<AAthenaPlayerCharacter*>(actor);

        //bool enemy = !UCrewFunctions::AreCharactersInSameCrew(localPlayer, player);

        auto location = player->RootComponent->K2_GetComponentLocation();

        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }

        Drawing::DrawBoundingBox(client, hud, actor, Drawing::Colour::White);
    }

    void DrawSkeleton(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto skeleton = reinterpret_cast<AAthenaAICharacter*>(actor);

        auto location = skeleton->RootComponent->K2_GetComponentLocation();

        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }

        Drawing::DrawBoundingBox(client, hud, actor, Drawing::Colour::White);
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

        std::wstring shipText = shipType + L" " + std::to_wstring(distance) + L"m";
        Drawing::DrawActorString(hud, shipText, screen, Drawing::Colour::White);
        //Drawing::DrawBoundingBox(client, hud, actor, Drawing::Colour::White);
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

        std::wstring shipText = shipType + L" " + std::to_wstring(distance) + L"m";
        Drawing::DrawActorString(hud, shipText, screen, Drawing::Colour::White);
    }

    void DrawItem(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;
        auto item = reinterpret_cast<ABootyProxy*>(actor);

        auto location = item->K2_GetRootComponent()->K2_GetComponentLocation();

        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }

        int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);

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

        std::wstring itemText = itemName + L" " + std::to_wstring(distance) + L"m";
        Drawing::DrawActorString(hud, itemText, screen, colour);
        //Drawing::DrawBoundingBox(client, hud, actor, colour);
    }

    void DrawMapPins(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;
        auto table = reinterpret_cast<AMapTable*>(actor);

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
            std::wstring pinText = L"Map Pin " + std::to_wstring(distance) + L"m";
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

        std::string name = actor->GetFullName();
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

        name = actor->GetName();
        std::wstring namew(name.begin(), name.end());
        Drawing::DrawActorString(hud, namew, screen, Drawing::Colour::Red);
    }

    void RenderESP(UGameViewportClient* client, AHUD* hud)
    {
        UWorld* world = client->World;
        if (!world)
        {
            spdlog::error("World Null");
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
            spdlog::error("Level Null");
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
                DrawPlayer(client, hud, actor);
                continue;
            }

            if (actor->IsA(AAthenaAICharacter::StaticClass()))
            {
                DrawSkeleton(client, hud, actor);
                continue;
            }

            if (actor->IsA(AShip::StaticClass()))
            {
                DrawShip(client, hud, actor);
                continue;
            }

            if (actor->IsA(AShipNetProxy::StaticClass()))
            {
                DrawShipFar(client, hud, actor);
                continue;
            }

            if (actor->IsA(ABootyProxy::StaticClass()))
            {
                DrawItem(client, hud, actor);
                continue;
            }

            if (actor->IsA(AMapTable::StaticClass()))
            {
                DrawMapPins(client, hud, actor);
                continue;
            }

            //DrawDebug(client, hud, actor);
        }
    }
}