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
                        if (config->barrelESP)
                        {
                            ESP::DrawBarrel(client, hud, actor);
                        }
                        continue;
                    }
                }
            }

            if (config->enabledAimbot)
            {
                Aimbot::Init(hud);
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
                    if (config->playerESP)
                    {
                        if (config->enabledAimbot)
                        {
                            Aimbot::SetNearest(client, actor);
                        }
                        ESP::DrawPlayer(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AAthenaAICharacter::StaticClass()))
                {
                    if (config->skeletonESP)
                    {
                        if (config->enabledAimbot)
                        {
                            Aimbot::SetNearest(client, actor);
                        }
                        ESP::DrawSkeleton(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(ASharkPawn::StaticClass()))
                {
                    if (config->sharkESP)
                    {
                        ESP::DrawShark(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AKraken::StaticClass()))
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
                }

                if (actor->IsA(AFauna::StaticClass()))
                {
                    if (config->animalESP)
                    {
                        ESP::DrawAnimal(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AMermaid::StaticClass()))
                {
                    if (config->mermaidESP)
                    {
                        ESP::DrawMermaid(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AShip::StaticClass()))
                {
                    if (config->shipESP)
                    {
                        ESP::DrawShip(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AShipNetProxy::StaticClass()))
                {
                    if (config->farShipESP)
                    {
                        ESP::DrawShipFar(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AAggressiveGhostShip::StaticClass()))
                {
                    if (config->ghostShipESP)
                    {
                        ESP::DrawGhostShip(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(ARowboat::StaticClass()))
                {
                    if (config->rowboatESP)
                    {
                        ESP::DrawRowboat(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(ABootyProxy::StaticClass()))
                {
                    if (config->itemESP)
                    {
                        ESP::DrawItem(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AStorageContainer::StaticClass()))
                {
                    if (config->barrelESP)
                    {
                        ESP::DrawBarrel(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AShipwreck::StaticClass()))
                {
                    if (config->shipwreckESP)
                    {
                        ESP::DrawShipwreck(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AStorm::StaticClass()))
                {
                    if (config->stormESP)
                    {
                        ESP::DrawStorm(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AGameplayEventSignal::StaticClass()))
                {
                    if (config->eventESP)
                    {
                        ESP::DrawEvent(client, hud, actor);
                    }
                    continue;
                }

                if (actor->IsA(AMapTable::StaticClass()))
                {
                    if (config->mapESP)
                    {
                        ESP::DrawMap(client, hud, actor);
                    }
                    continue;
                }

                if (config->debugESP)
                {
                    ESP::DrawDebug(client, hud, actor);
                }
            }

            if (config->enabledAimbot)
            {
                Aimbot::Aim(client, hud);
            }

            Info::Render(client, hud);
        }
    }
}