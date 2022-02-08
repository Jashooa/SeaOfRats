#include "Hacks.h"

#include <Windows.h>
#include <stdexcept>

#include "include/SDK/SDK.h"
#include "include/spdlog/spdlog.h"

#include "Config.h"
#include "Drawing.h"
#include "SeaOfRats.h"
#include "Aimbot/Cannon.h"
#include "Aimbot/Player.h"
#include "ESP/Animal.h"
#include "ESP/GhostShip.h"
#include "ESP/Item.h"
#include "ESP/LoreBook.h"
#include "ESP/MapPin.h"
#include "ESP/Mermaid.h"
#include "ESP/Player.h"
#include "ESP/Rowboat.h"
#include "ESP/Skeleton.h"
#include "ESP/Ship.h"
#include "ESP/Storm.h"
#include "ESP/TreasureMap.h"
#include "Info/Anchor.h"
#include "Info/Compass.h"
#include "Info/Debug.h"
#include "Info/Oxygen.h"
#include "Info/PlayerList.h"
#include "Info/WaterLevel.h"

using namespace SDK;

namespace Hacks
{
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

    void Hack()
    {
        UWorld* world = UAthenaGameViewportClient::GAthenaGameViewportClient->World;

        if (NullChecks(world))
        {
            ULevel* level = world->PersistentLevel;

            const auto levels = world->Levels;
            for (auto levelIndex = 6; levelIndex < levels.Num(); ++levelIndex)
            {
                const auto actors = levels[levelIndex]->AActors;
                for (auto actorIndex = 0; actorIndex < actors.Num(); ++actorIndex)
                {
                    AActor* actor = actors[actorIndex];

                    if (!actor)
                    {
                        continue;
                    }

                    if (actor->IsA(AModalInteractionProxy::StaticClass()))
                    {
                        if (config.esp.lorebook.enable)
                        {
                            try
                            {
                                ESP::DrawLoreBook(world, actor);
                            }
                            catch (...)
                            {
                                throw std::runtime_error("ESP::DrawLoreBook");
                            }
                        }
                        continue;
                    }
                }
            }

            if (config.aim.player.enable)
            {
                try
                {
                    Aimbot::InitPlayer(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Aimbot::InitPlayer");
                }
            }

            const auto actors = level->AActors;
            for (auto actorIndex = 0; actorIndex < actors.Num(); ++actorIndex)
            {
                AActor* actor = actors[actorIndex];

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
                    if (config.aim.player.enable && config.aim.player.player)
                    {
                        try
                        {
                            Aimbot::CalculateAimPlayer(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::CalculateAimPlayer");
                        }
                    }
                    if (config.esp.player.enable)
                    {
                        try
                        {
                            ESP::DrawPlayer(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawPlayer");
                        }
                    }
                    continue;
                }

                if (actor->IsA(AAthenaAICharacter::StaticClass()))
                {
                    if (config.aim.player.enable && config.aim.player.skeleton)
                    {
                        try
                        {
                            Aimbot::CalculateAimPlayer(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::CalculateAimPlayer");
                        }
                    }
                    if (config.esp.skeleton.enable)
                    {
                        try
                        {
                            ESP::DrawSkeleton(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawSkeleton");
                        }
                    }
                    continue;
                }

                if (actor->IsA(AShip::StaticClass()))
                {
                    if (config.esp.ship.enable)
                    {
                        try
                        {
                            ESP::DrawShip(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawShip");
                        }
                    }
                    continue;
                }

                if (actor->IsA(AShipNetProxy::StaticClass()))
                {
                    if (config.esp.ship.enable)
                    {
                        try
                        {
                            ESP::DrawShipFar(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawShipFar");
                        }
                    }
                    continue;
                }

                if (actor->IsA(AAggressiveGhostShip::StaticClass()))
                {
                    if (config.esp.ghostship.enable)
                    {
                        try
                        {
                            ESP::DrawGhostShip(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawGhostShip");
                        }
                    }
                    continue;
                }

                if (actor->IsA(ARowboat::StaticClass()))
                {
                    if (config.esp.rowboat.enable)
                    {
                        try
                        {
                            ESP::DrawRowboat(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawRowboat");
                        }
                    }
                    continue;
                }

                if (actor->IsA(AFauna::StaticClass()))
                {
                    if (config.esp.animal.enable)
                    {
                        try
                        {
                            ESP::DrawAnimal(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawAnimal");
                        }
                    }
                    continue;
                }

                if (actor->IsA(AMermaid::StaticClass()))
                {
                    if (config.esp.mermaid.enable)
                    {
                        try
                        {
                            ESP::DrawMermaid(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawMermaid");
                        }
                    }
                    continue;
                }

                if (actor->IsA(ABootyProxy::StaticClass()))
                {
                    if (config.esp.item.enable)
                    {
                        try
                        {
                            ESP::DrawItem(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawItem");
                        }
                    }
                    continue;
                }

                if (actor->IsA(AMapTable::StaticClass()))
                {
                    if (config.esp.mappin.enable)
                    {
                        try
                        {
                            ESP::DrawMapPin(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawMapPin");
                        }
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

                if (actor->IsA(AGameplayEventSignal::StaticClass()))
                {
                    if (config->eventESP)
                    {
                        ESP::DrawEvent(world, hud, actor);
                    }
                    continue;
                }*/

                if (actor->IsA(AModalInteractionProxy::StaticClass()))
                {
                    if (config.esp.lorebook.enable)
                    {
                        try
                        {
                            ESP::DrawLoreBook(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawLoreBook");
                        }
                    }
                    continue;
                }

                if (actor->IsA(AXMarksTheSpotMap::StaticClass()))
                {
                    if (config.esp.treasuremap.enable)
                    {
                        try
                        {
                            ESP::DrawXMarksTheSpotMap(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawXMarksTheSpotMap");
                        }
                    }
                    continue;
                }

                if (actor->IsA(ARiddleMap::StaticClass()))
                {
                    if (config.esp.treasuremap.enable)
                    {
                        try
                        {
                            ESP::DrawRiddleMap(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawRiddleMap");
                        }
                    }
                    continue;
                }

                if (actor->IsA(AStorm::StaticClass()))
                {
                    if (config.esp.storm.enable)
                    {
                        try
                        {
                            ESP::DrawStorm(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawStorm");
                        }
                    }
                    continue;
                }
            }

            if (config.aim.cannon.path)
            {
                try
                {
                    Aimbot::CannonTrace(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Aimbot::CannonTrace");
                }
            }

            if (config.aim.player.enable)
            {
                try
                {
                    Aimbot::AimPlayer(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Aimbot::AimPlayer");
                }
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
                try
                {
                    Info::DrawPlayerList(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Info::DrawPlayerList");
                }
            }

            if (config.info.compass)
            {
                try
                {
                    Info::DrawCompass(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Info::DrawCompass");
                }
            }

            if (config.info.oxygen)
            {
                try
                {
                    Info::DrawOxygen(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Info::DrawOxygen");
                }
            }

            if (config.info.waterLevel)
            {
                try
                {
                    Info::DrawWaterLevel(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Info::DrawWaterLevel");
                }
            }

            if (config.info.anchor)
            {
                try
                {
                    Info::DrawAnchor(world);
                }
                catch (...)
                {
                    throw std::runtime_error(" Info::DrawAnchor");
                }
            }

            if (config.info.debug)
            {
                try
                {
                    Info::DrawDebug(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Info::DrawDebug");
                }
            }
        }
    }

    void Loop()
    {
        try
        {
            Hack();
        }
        catch (const std::exception& e)
        {
            spdlog::critical("Shutting Down. Critical Error: {}", e.what());
            seaofrats->Uninstall();
        }
    }
}
