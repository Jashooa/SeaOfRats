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
#include "ESP/EnchantedCompass.h"
#include "ESP/GhostShip.h"
#include "ESP/Item.h"
#include "ESP/Kraken.h"
#include "ESP/LoreBook.h"
#include "ESP/MapPin.h"
#include "ESP/Megalodon.h"
#include "ESP/Mermaid.h"
#include "ESP/Player.h"
#include "ESP/Rowboat.h"
#include "ESP/Skeleton.h"
#include "ESP/SkeletonThrone.h"
#include "ESP/Shark.h"
#include "ESP/Ship.h"
#include "ESP/Siren.h"
#include "ESP/Storm.h"
#include "ESP/TreasureMap.h"
#include "Info/Anchor.h"
#include "Info/Compass.h"
#include "Info/Debug.h"
#include "Info/Oxygen.h"
#include "Info/PlayerList.h"
#include "Info/WaterLevel.h"
#include "Utilities/Math.h"

using namespace SDK;

namespace Hacks
{
    bool NullChecks(UWorld* world)
    {
        if (!world)
        {
            return false;
        }
        if (!world->GameState)
        {
            return false;
        }
        if (!world->GameState->IsA(AAthenaGameState::StaticClass()))
        {
            return false;
        }
        if (!world->OwningGameInstance)
        {
            return false;
        }
        if (!world->PersistentLevel)
        {
            return false;
        }
        if (world->OwningGameInstance->LocalPlayers.Num() < 1)
        {
            return false;
        }
        if (!world->OwningGameInstance->LocalPlayers[0]->PlayerController)
        {
            return false;
        }
        if (!world->OwningGameInstance->LocalPlayers[0]->PlayerController->IsA(AOnlineAthenaPlayerController::StaticClass()))
        {
            return false;
        }
        if (!world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn)
        {
            return false;
        }
        if (!world->OwningGameInstance->LocalPlayers[0]->PlayerController->PlayerCameraManager)
        {
            return false;
        }
        return true;
    }

    void Hack()
    {
        UWorld* world = UAthenaGameViewportClient::GAthenaGameViewportClient->World;

        /*try
        {
            TArray<FVector> actorlist{};
            actorlist.Push(FVector(-10, -50, 0)); // North
            actorlist.Push(FVector(80, 90, 20)); // South West
            actorlist.Push(FVector(-50, 10, 10)); // East
            actorlist.Push(FVector(50, -50, 40)); // North West

            FVector closest = Utilities::ClosestRelativeActorToBearing(FVector(0.f, 0.f, 0.f), actorlist, "South West");

            spdlog::info("{} {} {}", closest.X, closest.Y, closest.Z);
        }
        catch (...)
        {
            throw std::runtime_error("Test");
        }*/

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

                    if (config.esp.lorebook.enable)
                    {
                        if (actor->IsA(AModalInteractionProxy::StaticClass()))
                        {
                            try
                            {
                                ESP::DrawLoreBook(world, actor);
                            }
                            catch (...)
                            {
                                throw std::runtime_error("ESP::DrawLoreBook");
                            }
                            continue;
                        }
                    }

                    if (config.esp.skeletonthrone.enable)
                    {
                        if (actor->IsA(ASkeletonThrone::StaticClass()))
                        {
                            try
                            {
                                ESP::DrawSkeletonThrone(world, actor);
                            }
                            catch (...)
                            {
                                throw std::runtime_error("ESP::DrawSkeletonThrone");
                            }
                            continue;
                        }
                    }
                }
            }

            if (config.aim.player.enable)
            {
                try
                {
                    Aimbot::InitAimPlayer(world);
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

                if (config.esp.ship.enable)
                {
                    if (actor->IsA(AShipNetProxy::StaticClass()))
                    {

                        try
                        {
                            ESP::DrawShipFar(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawShipFar");
                        }
                        continue;
                    }
                }

                if (config.esp.ghostship.enable)
                {
                    if (actor->IsA(AAggressiveGhostShip::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawGhostShip(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawGhostShip");
                        }
                        continue;
                    }
                }

                if (config.esp.rowboat.enable)
                {
                    if (actor->IsA(ARowboat::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawRowboat(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawRowboat");
                        }
                        continue;
                    }
                }

                if (config.esp.animal.enable)
                {
                    if (actor->IsA(AFauna::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawAnimal(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawAnimal");
                        }
                        continue;
                    }
                }

                if (config.esp.shark.enable)
                {
                    if (actor->IsA(ATinyShark::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawMegalodon(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawMegalodon");
                        }
                        continue;
                    }
                }

                if (config.esp.megalodon.enable)
                {
                    if (actor->IsA(ASharkPawn::StaticClass()) && !actor->IsA(ATinyShark::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawShark(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawShark");
                        }
                        continue;
                    }
                }

                if (actor->IsA(ASirenPawn::StaticClass()))
                {
                    if (config.aim.player.enable)
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
                    if (config.esp.siren.enable)
                    {
                        try
                        {
                            ESP::DrawSiren(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawSiren");
                        }
                    }
                    continue;
                }

                if (config.esp.mermaid.enable)
                {
                    if (actor->IsA(AMermaid::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawMermaid(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawMermaid");
                        }
                        continue;
                    }
                }

                if (config.esp.item.enable)
                {
                    if (actor->IsA(AFloatingItemProxy::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawItem(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawItem");
                        }
                        continue;
                    }
                }

                if (config.esp.mappin.enable)
                {
                    if (actor->IsA(AMapTable::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawMapPin(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawMapPin");
                        }
                        continue;
                    }
                }

                if (config.esp.kraken.enable)
                {
                    if (actor->IsA(AKraken::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawKraken(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawKraken");
                        }
                        continue;
                    }

                    if (actor->IsA(AKrakenTentacle::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawKrakenTentacle(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawKrakenTentacle");
                        }
                        continue;
                    }
                }

                if (config.esp.lorebook.enable)
                {
                    if (actor->IsA(AModalInteractionProxy::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawLoreBook(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawLoreBook");
                        }
                        continue;
                    }
                }

                if (config.esp.skeletonthrone.enable)
                {
                    if (actor->IsA(ASkeletonThrone::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawSkeletonThrone(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawSkeletonThrone");
                        }
                        continue;
                    }
                }

                if (config.esp.treasuremap.enable)
                {
                    if (actor->IsA(ARiddleMap::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawRiddleMap(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawRiddleMap");
                        }
                        continue;
                    }

                    if (actor->IsA(AXMarksTheSpotMap::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawXMarksTheSpotMap(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawXMarksTheSpotMap");
                        }
                        continue;
                    }

                    /*if (actor->IsA(ATornMap::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawTornMap(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawTornMap");
                        }
                        continue;
                    }*/
                }

                if (config.esp.enchantedcompass.enable)
                {
                    if (actor->IsA(AEnchantedCompass::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawEnchantedCompass(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawEnchantedCompass");
                        }
                        continue;
                    }

                    if (actor->IsA(AMultiTargetEnchantedCompass::StaticClass()))
                    {
                        try
                        {
                            ESP::DrawMultiTargetEnchantedCompass(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::DrawMultiTargetEnchantedCompass");
                        }
                        continue;
                    }
                }

                /*if (actor->IsA(AStorageContainer::StaticClass()))
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
            }

            if (config.esp.storm.enable)
            {
                try
                {
                    ESP::DrawStorms(world);
                }
                catch (...)
                {
                    throw std::runtime_error("ESP::DrawStorms");
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
                try
                {
                    const float centreX = std::trunc(Drawing::Window->Size.x * 0.5f);
                    const float centreY = std::trunc(Drawing::Window->Size.y * 0.5f);
                    Drawing::DrawLine(FVector2D(centreX, centreY - 5), FVector2D(centreX, centreY + 5 + 1), Drawing::Colour::White);
                    Drawing::DrawLine(FVector2D(centreX - 5, centreY), FVector2D(centreX + 5 + 1, centreY), Drawing::Colour::White);

                    /*auto player = world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn;
                    auto location = player->K2_GetActorLocation();
                    Drawing::DrawString(std::to_string(location.X), FVector2D(200, 200), Drawing::Colour::White);
                    Drawing::DrawString(std::to_string(location.Y), FVector2D(200, 215), Drawing::Colour::White);
                    Drawing::DrawString(std::to_string(location.Z), FVector2D(200, 230), Drawing::Colour::White);*/
                }
                catch (...)
                {
                    throw std::runtime_error("Crosshair");
                }
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

            const auto onlinePlayerController = reinterpret_cast<AOnlineAthenaPlayerController*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController);

            if (config.client.antiafk == onlinePlayerController->IdleDisconnectEnabled)
            {
                onlinePlayerController->IdleDisconnectEnabled = !config.client.antiafk;
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
