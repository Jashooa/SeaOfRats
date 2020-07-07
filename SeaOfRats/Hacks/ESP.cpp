#include "ESP.h"

#include <string>

#include "spdlog/spdlog.h"

#include "Drawing.h"
#include "SDK.hpp"
#include "Global.h"

using namespace SDK;

namespace Hacks
{
    void DrawPlayer(UGameViewportClient* client, UCanvas* canvas, AActor* actor)
    {
    }

    void DrawShip(UGameViewportClient* client, UCanvas* canvas, AActor* actor)
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
        Drawing::DrawActorString(canvas, shipText, screen, Drawing::Colour::White);
    }

    void DrawShipFar(UGameViewportClient* client, UCanvas* canvas, AActor* actor)
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
        Drawing::DrawActorString(canvas, shipText, screen, Drawing::Colour::White);
    }

    void DrawMapPins(UGameViewportClient* client, UCanvas* canvas, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;
        auto table = reinterpret_cast<AMapTable*>(actor);
        spdlog::info("Table Address: {:p}", reinterpret_cast<void*>(table));

        auto pins = table->MapPins;
        spdlog::info("Table->MapPins Address: {:p}", reinterpret_cast<void*>(&(table->MapPins)));
        spdlog::info("table pins {}", pins.Num());

        for (int32_t i = 0; i < pins.Num(); ++i)
        {
            spdlog::info("Drawing map pin1");
            auto pin = pins[i];
            FVector location((pin.X * 100.0f), (pin.Y * 100.0f), localPlayer->K2_GetActorLocation().Z);
            //FVector location((pin.X * 100.0f), (pin.Y * 100.0f), 1000.0f);

            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                continue;
            }

            spdlog::info("Drawing map pin");
            int32_t distance = static_cast<int32_t>(UVectorMaths::Distance(localPlayer->RootComponent->K2_GetComponentLocation(), location) * 0.01f);
            std::wstring pinText = L"Map Pin " + std::to_wstring(distance) + L"m";
            Drawing::DrawActorString(canvas, pinText, screen, Drawing::Colour::White);
        }
    }

    void RenderESP(UGameViewportClient* client, UCanvas* canvas)
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
                DrawPlayer(client, canvas, actor);
                continue;
            }

            if (actor->IsA(AShip::StaticClass()))
            {
                DrawShip(client, canvas, actor);
                continue;
            }

            if (actor->IsA(AShipNetProxy::StaticClass()))
            {
                DrawShipFar(client, canvas, actor);
                continue;
            }

            if (actor->IsA(AMapTable::StaticClass()))
            {
                DrawMapPins(client, canvas, actor);
                continue;
            }
        }
    }
}