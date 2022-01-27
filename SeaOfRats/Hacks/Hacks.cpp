#include "Hacks.h"

#include "include/SDK/SDK.h"
#include "include/spdlog/spdlog.h"

#include "Config.h"
#include "Hacks/Aimbot.h"
#include "Hacks/ESP.h"
#include "Hacks/Info.h"

using namespace SDK;

bool NullChecks(UGameViewportClient* client)
{
    if (!client->World)
    {
        spdlog::warn("World null");
        return false;
    }
    if (!client->World->GameState)
    {
        spdlog::warn("GameState null");
        return false;
    }
    if (!client->World->GameState->IsA(AAthenaGameState::StaticClass()))
    {
        return false;
    }
    if (!client->World->PersistentLevel)
    {
        spdlog::warn("PersistentLevel null");
        return false;
    }
    if (!client->GameInstance)
    {
        spdlog::warn("GameInstance null");
        return false;
    }
    if (client->GameInstance->LocalPlayers.Num() < 1)
    {
        spdlog::warn("LocalPlayers < 1");
        return false;
    }
    if (!client->GameInstance->LocalPlayers[0]->PlayerController)
    {
        spdlog::warn("PlayerController null");
        return false;
    }
    if (!client->GameInstance->LocalPlayers[0]->PlayerController->Pawn)
    {
        spdlog::warn("Pawn null");
        return false;
    }
    return true;
}

namespace Hacks
{
    void Loop(UGameViewportClient* client, UCanvas* canvas)
    {
        if (NullChecks(client))
        {
            AHUD* hud = client->GameInstance->LocalPlayers[0]->PlayerController->MyHUD;
            hud->Canvas = canvas;

            UWorld* world = client->World;
            if (!world)
            {
                spdlog::warn("World null");
                return;
            }

            ULevel* level = world->PersistentLevel;
            if (!level)
            {
                spdlog::warn("PersistentLevel null");
                return;
            }

            auto levels = world->Levels;

            /*for (int32_t i = 6; i < levels.Num(); ++i)
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
                            ESP::DrawBarrel(client, hud, actor);
                        }
                        continue;
                    }
                }
            }*/

            if (config.aim.enable)
            {
                Aimbot::Init(client);
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
                    if (config.esp.player.enable)
                    {
                        if (config.aim.player.enable)
                        {
                            Aimbot::CalculateAim(client, actor);
                        }
                        ESP::DrawPlayer(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AAthenaAICharacter::StaticClass()))
                {
                    if (config.esp.skeleton.enable)
                    {
                        if (config.aim.skeleton.enable)
                        {
                            Aimbot::CalculateAim(client, actor);
                        }
                        ESP::DrawSkeleton(client, hud, actor);
                    }
                    continue;
                }

                /*if (actor->IsA(ASharkPawn::StaticClass()))
                {
                    if (config.esp.shark.enable)
                    {
                        ESP::DrawShark(client, hud, actor);
                    }
                    continue;
                }*/

                /*if (actor->IsA(AKraken::StaticClass()))
                {
                    if (config->krakenESP)
                    {
                        ESP::DrawKraken(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AKrakenTentacle::StaticClass()))
                {
                    if (config->krakenTentacleESP)
                    {
                        ESP::DrawKrakenTentacle(client, hud, actor);
                    }
                    continue;
                }*/

                if (actor->IsA(AFauna::StaticClass()))
                {
                    if (config.esp.animal.enable)
                    {
                        ESP::DrawAnimal(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AMermaid::StaticClass()))
                {
                    if (config.esp.mermaid.enable)
                    {
                        ESP::DrawMermaid(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AShip::StaticClass()))
                {
                    if (config.esp.ship.enable)
                    {
                        ESP::DrawShip(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AShipNetProxy::StaticClass()))
                {
                    if (config.esp.ship.enable)
                    {
                        ESP::DrawShipFar(client, hud, actor);
                    }
                    continue;
                }

                /*if (actor->IsA(AAggressiveGhostShip::StaticClass()))
                {
                    if (config->ghostShipESP)
                    {
                        ESP::DrawGhostShip(client, hud, actor);
                    }
                    continue;
                }*/

                /*if (actor->IsA(ARowboat::StaticClass()))
                {
                    if (config.esp.rowboat.enable)
                    {
                        ESP::DrawRowboat(client, hud, actor);
                    }
                    continue;
                }*/

                if (actor->IsA(ABootyProxy::StaticClass()))
                {
                    if (config.esp.item.enable)
                    {
                        ESP::DrawItem(client, hud, actor);
                    }
                    continue;
                }

                /*if (actor->IsA(AStorageContainer::StaticClass()))
                {
                    if (config.esp.barrel.enable)
                    {
                        ESP::DrawBarrel(client, hud, actor);
                    }
                    continue;
                }*/

                /*if (actor->IsA(AShipwreck::StaticClass()))
                {
                    if (config.esp.shipwreck.enable)
                    {
                        ESP::DrawShipwreck(client, hud, actor);
                    }
                    continue;
                }*/

                /*if (actor->IsA(AStorm::StaticClass()))
                {
                    if (config.esp.storm.enable)
                    {
                        ESP::DrawStorm(client, hud, actor);
                    }
                    continue;
                }*/

                /*if (actor->IsA(AGameplayEventSignal::StaticClass()))
                {
                    if (config->eventESP)
                    {
                        ESP::DrawEvent(client, hud, actor);
                    }
                    continue;
                }*/

                if (actor->IsA(AMapTable::StaticClass()))
                {
                    if (config.esp.map.enable)
                    {
                        ESP::DrawMap(client, hud, actor);
                    }
                    continue;
                }

                if (config.esp.debug.enable)
                {
                    ESP::DrawDebug(client, hud, actor);
                }
            }

            if (config.aim.enable)
            {
                Aimbot::Aim(client, hud);
            }

            Info::Render(client, hud);
        }
    }
}