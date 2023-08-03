#include "Hacks.h"

#include <Windows.h>
#include <stdexcept>

#include "include/SDK/SDK.h"
#include "include/spdlog/spdlog.h"

#include "Config.h"
#include "SeaOfRats.h"
#include "Aimbot/Cannon.h"
#include "Aimbot/Player.h"
#include "ESP/Animal.h"
#include "ESP/Barrel.h"
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
#include "Utilities/Drawing.h"
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

        if (NullChecks(world))
        {
            // Island level actors
            const auto levels = world->Levels;
            for (int levelIndex = 6; levelIndex < levels.Num(); ++levelIndex)
            {
                const auto actors = levels[levelIndex]->AActors;
                for (int actorIndex = 0; actorIndex < actors.Num(); ++actorIndex)
                {
                    AActor* actor = actors[actorIndex];

                    if (!actor)
                    {
                        continue;
                    }

                    // Barrel
                    if (config.esp.barrel.enable)
                    {
                        if (actor->IsA(AStorageContainer::StaticClass()))
                        {
                            try
                            {
                                ESP::Barrel::Draw(world, actor);
                            }
                            catch (...)
                            {
                                throw std::runtime_error("ESP::Barrel::Draw");
                            }
                            continue;
                        }
                    }

                    // Skeleton Throne
                    if (config.esp.skeletonthrone.enable)
                    {
                        if (actor->IsA(ASkeletonThrone::StaticClass()))
                        {
                            try
                            {
                                ESP::SkeletonThrone::Draw(world, actor);
                            }
                            catch (...)
                            {
                                throw std::runtime_error("ESP::SkeletonThrone::Draw");
                            }
                            continue;
                        }
                    }

                    // Lore Book
                    if (config.esp.lorebook.enable)
                    {
                        if (actor->IsA(AModalInteractionProxy::StaticClass()))
                        {
                            try
                            {
                                ESP::LoreBook::Draw(world, actor);
                            }
                            catch (...)
                            {
                                throw std::runtime_error("ESP::LoreBook::Draw");
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
                    Aimbot::Player::InitAim(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Aimbot::Player::InitAim");
                }
            }

            if (config.aim.cannon.enable)
            {
                try
                {
                    Aimbot::Cannon::InitAim(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Aimbot::Cannon::InitAim");
                }
            }

            // Main level actors
            const ULevel* level = world->PersistentLevel;
            const auto actors = level->AActors;
            for (int actorIndex = 0; actorIndex < actors.Num(); ++actorIndex)
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

                // Player
                if (actor->IsA(AAthenaPlayerCharacter::StaticClass()))
                {
                    if (config.aim.player.enable && config.aim.player.player)
                    {
                        try
                        {
                            Aimbot::Player::CalculateAim(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::Player::CalculateAim");
                        }
                    }

                    if (config.esp.player.enable)
                    {
                        try
                        {
                            ESP::Player::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Player::Draw");
                        }
                    }

                    continue;
                }

                // Skeleton
                if (actor->IsA(AAthenaAICharacter::StaticClass()))
                {
                    if (config.aim.player.enable && config.aim.player.skeleton)
                    {
                        try
                        {
                            Aimbot::Player::CalculateAim(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::Player::CalculateAim");
                        }
                    }

                    if (config.esp.skeleton.enable)
                    {
                        try
                        {
                            ESP::Skeleton::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Skeleton::Draw");
                        }
                    }

                    continue;
                }

                // Ship
                if (actor->IsA(AShip::StaticClass()))
                {
                    if (config.aim.cannon.enable)
                    {
                        try
                        {
                            Aimbot::Cannon::CalculateAim(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::Cannon::CalculateAim");
                        }
                    }

                    if (config.esp.ship.enable)
                    {
                        try
                        {
                            ESP::Ship::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Ship::Draw");
                        }
                    }

                    continue;
                }

                // ShipNetProxy
                if (config.esp.ship.enable)
                {
                    if (actor->IsA(AShipNetProxy::StaticClass()))
                    {
                        try
                        {
                            ESP::Ship::DrawFar(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Ship::DrawFar");
                        }

                        continue;
                    }
                }

                // GhostShip
                if (actor->IsA(AAggressiveGhostShip::StaticClass()))
                {
                    if (config.aim.cannon.enable)
                    {
                        try
                        {
                            Aimbot::Cannon::CalculateAim(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::Cannon::CalculateAim");
                        }
                    }

                    if (config.esp.ghostship.enable)
                    {
                        try
                        {
                            ESP::GhostShip::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::GhostShip::Draw");
                        }
                    }

                    continue;
                }

                // Rowboat
                if (config.esp.rowboat.enable)
                {
                    if (actor->IsA(ARowboat::StaticClass()))
                    {
                        try
                        {
                            ESP::Rowboat::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Rowboat::Draw");
                        }

                        continue;
                    }
                }

                // Animal
                if (config.esp.animal.enable)
                {
                    if (actor->IsA(AFauna::StaticClass()))
                    {
                        try
                        {
                            ESP::Animal::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Animal::Draw");
                        }

                        continue;
                    }
                }

                // Megalodon
                if (actor->IsA(ATinyShark::StaticClass()))
                {
                    if (config.aim.cannon.enable)
                    {
                        try
                        {
                            Aimbot::Cannon::CalculateAim(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::Cannon::CalculateAim");
                        }
                    }

                    if (config.esp.megalodon.enable)
                    {
                        try
                        {
                            ESP::Megalodon::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Megalodon::Draw");
                        }
                    }

                    continue;
                }

                // Shark
                if (config.esp.shark.enable)
                {
                    if (actor->IsA(ASharkPawn::StaticClass()))
                    {
                        try
                        {
                            ESP::Shark::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Shark::Draw");
                        }

                        continue;
                    }
                }

                // Siren
                if (actor->IsA(ASirenPawn::StaticClass()))
                {
                    if (config.aim.player.enable)
                    {
                        try
                        {
                            Aimbot::Player::CalculateAim(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::Player::CalculateAim");
                        }
                    }

                    if (config.esp.siren.enable)
                    {
                        try
                        {
                            ESP::Siren::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Siren::Draw");
                        }
                    }

                    continue;
                }

                // Mermaid
                if (config.esp.mermaid.enable)
                {
                    if (actor->IsA(AMermaid::StaticClass()))
                    {
                        try
                        {
                            ESP::Mermaid::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Mermaid::Draw");
                        }

                        continue;
                    }
                }

                // Item
                if (config.esp.item.enable)
                {
                    if (actor->IsA(AFloatingItemProxy::StaticClass()))
                    {
                        try
                        {
                            ESP::Item::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Item::Draw");
                        }

                        continue;
                    }
                }

                // Barrel
                if (config.esp.barrel.enable)
                {
                    if (actor->IsA(AStorageContainer::StaticClass()))
                    {
                        try
                        {
                            ESP::Barrel::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Barrel::Draw");
                        }

                        continue;
                    }
                }

                // Map Pin
                if (config.esp.mappin.enable)
                {
                    if (actor->IsA(AMapTable::StaticClass()))
                    {
                        try
                        {
                            ESP::MapPin::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::MapPin::Draw");
                        }

                        continue;
                    }
                }

                // Kraken
                if (config.esp.kraken.enable)
                {
                    if (actor->IsA(AKraken::StaticClass()))
                    {
                        try
                        {
                            ESP::Kraken::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Kraken::Draw");
                        }

                        continue;
                    }
                }

                if (actor->IsA(AKrakenTentacle::StaticClass()))
                {
                    if (config.aim.cannon.enable)
                    {
                        try
                        {
                            Aimbot::Cannon::CalculateAim(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::Cannon::CalculateAim");
                        }
                    }

                    if (config.esp.kraken.enable)
                    {
                        try
                        {
                            ESP::Kraken::DrawTentacle(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Kraken::DrawTentacle");
                        }
                    }

                    continue;
                }

                // Lore Book
                if (config.esp.lorebook.enable)
                {
                    if (actor->IsA(AModalInteractionProxy::StaticClass()))
                    {
                        try
                        {
                            ESP::LoreBook::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::LoreBook::Draw");
                        }

                        continue;
                    }
                }

                // Skeleton Throne
                if (config.esp.skeletonthrone.enable)
                {
                    if (actor->IsA(ASkeletonThrone::StaticClass()))
                    {
                        try
                        {
                            ESP::SkeletonThrone::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::SkeletonThrone::Draw");
                        }

                        continue;
                    }
                }

                // Treasure Map
                if (config.esp.treasuremap.enable)
                {
                    if (actor->IsA(ARiddleMap::StaticClass()))
                    {
                        try
                        {
                            ESP::TreasureMap::DrawRiddleMap(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::TreasureMap::DrawRiddleMap");
                        }

                        continue;
                    }

                    if (actor->IsA(AXMarksTheSpotMap::StaticClass()))
                    {
                        try
                        {
                            ESP::TreasureMap::DrawXMarksTheSpotMap(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::TreasureMap::DrawXMarksTheSpotMap");
                        }

                        continue;
                    }

                    /*if (actor->IsA(ATornMap::StaticClass()))
                    {
                        try
                        {
                            ESP::TreasureMap::DrawTornMap(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::TreasureMap::DrawTornMap");
                        }
                        continue;
                    }*/
                }

                // Enchanted Compass
                if (config.esp.enchantedcompass.enable)
                {
                    if (actor->IsA(AEnchantedCompass::StaticClass()))
                    {
                        try
                        {
                            ESP::EnchantedCompass::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::EnchantedCompass::Draw");
                        }

                        continue;
                    }

                    if (actor->IsA(AMultiTargetEnchantedCompass::StaticClass()))
                    {
                        try
                        {
                            ESP::EnchantedCompass::DrawMultiTarget(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::EnchantedCompass::DrawMultiTarget");
                        }

                        continue;
                    }
                }

                /*if (actor->IsA(AShipwreck::StaticClass()))
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

            // Storm
            if (config.esp.storm.enable)
            {
                try
                {
                    ESP::Storm::Draw(world);
                }
                catch (...)
                {
                    throw std::runtime_error("ESP::Storm::Draw");
                }
            }

            if (config.aim.player.enable)
            {
                try
                {
                    Aimbot::Player::Aim(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Aimbot::Player::Aim");
                }
            }

            if (config.aim.cannon.enable)
            {
                try
                {
                    Aimbot::Cannon::Aim(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Aimbot::Cannon::Aim");
                }
            }

            if (config.aim.cannon.path)
            {
                try
                {
                    Aimbot::Cannon::TracePath(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Aimbot::Cannon::TracePath");
                }
            }

            // Crosshair
            if (config.info.crosshair)
            {
                try
                {
                    const float centreX = std::trunc(Utilities::Drawing::Window->Size.x * 0.5f);
                    const float centreY = std::trunc(Utilities::Drawing::Window->Size.y * 0.5f);
                    Utilities::Drawing::DrawLine(FVector2D(centreX, centreY - 5), FVector2D(centreX, centreY + 5 + 1), Utilities::Drawing::Colour::White);
                    Utilities::Drawing::DrawLine(FVector2D(centreX - 5, centreY), FVector2D(centreX + 5 + 1, centreY), Utilities::Drawing::Colour::White);

                    /*auto player = world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn;
                    auto location = player->K2_GetActorLocation();
                    Utilities::Drawing::DrawString(std::to_string(location.X), FVector2D(200, 200), Utilities::Drawing::Colour::White);
                    Utilities::Drawing::DrawString(std::to_string(location.Y), FVector2D(200, 215), Utilities::Drawing::Colour::White);
                    Utilities::Drawing::DrawString(std::to_string(location.Z), FVector2D(200, 230), Utilities::Drawing::Colour::White);*/
                }
                catch (...)
                {
                    throw std::runtime_error("Crosshair");
                }
            }

            // Player List
            if (config.info.playerList)
            {
                try
                {
                    Info::PlayerList::Draw(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Info::PlayerList::Draw");
                }
            }

            // Compass
            if (config.info.compass)
            {
                try
                {
                    Info::Compass::Draw(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Info::Compass::Draw");
                }
            }

            // Oxygen
            if (config.info.oxygen)
            {
                try
                {
                    Info::Oxygen::Draw(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Info::Oxygen::Draw");
                }
            }

            // Water Level
            if (config.info.waterLevel)
            {
                try
                {
                    Info::WaterLevel::Draw(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Info::WaterLevel::Draw");
                }
            }

            // Anchor
            if (config.info.anchor)
            {
                try
                {
                    Info::Anchor::Draw(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Info::Anchor::Draw");
                }
            }

            // Debug
            if (config.info.debug)
            {
                try
                {
                    Info::Debug::Draw(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Info::Debug::Draw");
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
