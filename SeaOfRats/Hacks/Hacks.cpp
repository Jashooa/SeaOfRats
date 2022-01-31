#include "Hacks.h"

#include "include/SDK/SDK.h"
#include "include/spdlog/spdlog.h"

#include "Config.h"
#include "Drawing.h"
#include "Hacks/Aimbot/Player.h"
#include "Hacks/ESP/Animal.h"
#include "Hacks/ESP/Item.h"
#include "Hacks/ESP/Map.h"
#include "Hacks/ESP/Mermaid.h"
#include "Hacks/ESP/Player.h"
#include "Hacks/ESP/Skeleton.h"
#include "Hacks/ESP/Ship.h"
#include "Hacks/Info/Anchor.h"
#include "Hacks/Info/Compass.h"
#include "Hacks/Info/Oxygen.h"
#include "Hacks/Info/PlayerList.h"
#include "Hacks/Info/WaterLevel.h"

using namespace SDK;

bool NullChecks(UWorld* world)
{
    if (!world)
    {
        spdlog::warn("World null");
        return false;
    }
    if (!world->GameState)
    {
        spdlog::warn("GameState null");
        return false;
    }
    if (!world->GameState->IsA(AAthenaGameState::StaticClass()))
    {
        return false;
    }
    if (!world->OwningGameInstance)
    {
        spdlog::warn("GameInstance null");
        return false;
    }
    if (!world->PersistentLevel)
    {
        spdlog::warn("PersistentLevel null");
        return false;
    }
    if (world->OwningGameInstance->LocalPlayers.Num() < 1)
    {
        spdlog::warn("LocalPlayers < 1");
        return false;
    }
    if (!world->OwningGameInstance->LocalPlayers[0]->PlayerController)
    {
        spdlog::warn("PlayerController null");
        return false;
    }
    if (!world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn)
    {
        spdlog::warn("Pawn null");
        return false;
    }
    if (!world->OwningGameInstance->LocalPlayers[0]->PlayerController->PlayerCameraManager)
    {
        spdlog::warn("PlayerCameraManager null");
        return false;
    }
    return true;
}

namespace Hacks
{
    void Loop()
    {
        UWorld* world = UAthenaGameViewportClient::GAthenaGameViewportClient->World;

        if (NullChecks(world))
        {
            ULevel* level = world->PersistentLevel;

            /*auto levels = world->Levels;
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

                    if (actor->IsA(AStorageContainer::StaticClass()))
                    {
                        if (config.esp.barrel.enable)
                        {
                            ESP::DrawBarrel(world, hud, actor);
                        }
                        continue;
                    }
                }
            }*/

            if (config.aim.enable)
            {
                spdlog::debug("Aimbot::InitPlayer");
                Aimbot::InitPlayer(world);
            }

            auto actors = level->AActors;

            for (int32_t i = 0; i < actors.Num(); ++i)
            {
                AActor* actor = actors[i];

                if (!actor)
                {
                    continue;
                }

                if (actor == world->OwningGameInstance->LocalPlayers[0]->PlayerController)
                {
                    continue;
                }

                if (actor->IsA(AAthenaPlayerCharacter::StaticClass()))
                {
                    if (config.esp.player.enable)
                    {
                        if (config.aim.enable && config.aim.player.enable)
                        {
                            spdlog::debug("Aimbot::CalculateAimPlayer");
                            Aimbot::CalculateAimPlayer(world, actor);
                        }
                        spdlog::debug("ESP::DrawPlayer");
                        ESP::DrawPlayer(world, actor);
                    }
                    continue;
                }

                if (actor->IsA(AAthenaAICharacter::StaticClass()))
                {
                    if (config.esp.skeleton.enable)
                    {
                        if (config.aim.enable && config.aim.skeleton.enable)
                        {
                            spdlog::debug("Aimbot::CalculateAimPlayer");
                            Aimbot::CalculateAimPlayer(world, actor);
                        }
                        spdlog::debug("ESP::DrawSkeleton");
                        ESP::DrawSkeleton(world, actor);
                    }
                    continue;
                }

                if (actor->IsA(AShip::StaticClass()))
                {
                    if (config.esp.ship.enable)
                    {
                        spdlog::debug("ESP::DrawShip");
                        ESP::DrawShip(world, actor);
                    }
                    continue;
                }

                if (actor->IsA(AShipNetProxy::StaticClass()))
                {
                    if (config.esp.ship.enable)
                    {
                        spdlog::debug("ESP::DrawShipFar");
                        ESP::DrawShipFar(world, actor);
                    }
                    continue;
                }

                if (actor->IsA(AFauna::StaticClass()))
                {
                    if (config.esp.animal.enable)
                    {
                        spdlog::debug("ESP::DrawAnimal");
                        ESP::DrawAnimal(world, actor);
                    }
                    continue;
                }

                if (actor->IsA(AMermaid::StaticClass()))
                {
                    if (config.esp.mermaid.enable)
                    {
                        spdlog::debug("ESP::DrawMermaid");
                        ESP::DrawMermaid(world, actor);
                    }
                    continue;
                }

                if (actor->IsA(ABootyProxy::StaticClass()))
                {
                    if (config.esp.item.enable)
                    {
                        spdlog::debug("ESP::DrawItem");
                        ESP::DrawItem(world, actor);
                    }
                    continue;
                }

                if (actor->IsA(AMapTable::StaticClass()))
                {
                    if (config.esp.map.enable)
                    {
                        spdlog::debug("ESP::DrawMap");
                        ESP::DrawMap(world, actor);
                    }
                    continue;
                }

                /*if (actor->IsA(ASharkPawn::StaticClass()))
                {
                    if (config.esp.shark.enable)
                    {
                        ESP::DrawShark(world, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AKraken::StaticClass()))
                {
                    if (config->krakenESP)
                    {
                        ESP::DrawKraken(world, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AKrakenTentacle::StaticClass()))
                {
                    if (config->krakenTentacleESP)
                    {
                        ESP::DrawKrakenTentacle(world, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AAggressiveGhostShip::StaticClass()))
                {
                    if (config->ghostShipESP)
                    {
                        ESP::DrawGhostShip(world, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(ARowboat::StaticClass()))
                {
                    if (config.esp.rowboat.enable)
                    {
                        ESP::DrawRowboat(world, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AStorageContainer::StaticClass()))
                {
                    if (config.esp.barrel.enable)
                    {
                        ESP::DrawBarrel(world, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AShipwreck::StaticClass()))
                {
                    if (config.esp.shipwreck.enable)
                    {
                        ESP::DrawShipwreck(world, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AStorm::StaticClass()))
                {
                    if (config.esp.storm.enable)
                    {
                        ESP::DrawStorm(world, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AGameplayEventSignal::StaticClass()))
                {
                    if (config->eventESP)
                    {
                        ESP::DrawEvent(world, hud, actor);
                    }
                    continue;
                }

                if (config.esp.debug.enable)
                {
                    spdlog::debug("DrawDebug");
                    DrawDebug(world, actor);
                }*/
            }

            if (config.aim.enable)
            {
                spdlog::debug("Aimbot::AimPlayer");
                Aimbot::AimPlayer(world);
            }

            if (config.info.crosshair)
            {
                const float centerX = std::trunc(Drawing::Window->Size.x * 0.5f);
                const float centerY = std::trunc(Drawing::Window->Size.y * 0.5f);
                Drawing::DrawLine(FVector2D(centerX, centerY - 5), FVector2D(centerX, centerY + 5 + 1), Drawing::Colour::White);
                Drawing::DrawLine(FVector2D(centerX - 5, centerY), FVector2D(centerX + 5 + 1, centerY), Drawing::Colour::White);
            }

            if (config.info.playerList)
            {
                spdlog::debug("Info::DrawPlayerList");
                Info::DrawPlayerList(world);
            }

            if (config.info.compass)
            {
                spdlog::debug("Info::DrawCompass");
                Info::DrawCompass(world);
            }

            if (config.info.oxygen)
            {
                spdlog::debug("Info::DrawOxygen");
                Info::DrawOxygen(world);
            }

            if (config.info.waterLevel)
            {
                spdlog::debug("Info::DrawWaterLevel");
                Info::DrawWaterLevel(world);
            }

            if (config.info.anchor)
            {
                spdlog::debug("Info::DrawAnchor");
                Info::DrawAnchor(world);
            }
        }
    }
}