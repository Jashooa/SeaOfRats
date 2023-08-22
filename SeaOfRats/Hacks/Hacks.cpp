#include "Hacks.h"

#include <Windows.h>

#include <stdexcept>

#include "include/SDK/SDK.h"
#include "include/spdlog/spdlog.h"

#include "Config.h"
#include "SeaOfRats.h"
#include "Aimbot/Cannon.h"
#include "Aimbot/Harpoon.h"
#include "Aimbot/Weapon.h"
#include "ESP/Animal.h"
#include "ESP/Barrel.h"
#include "ESP/EnchantedCompass.h"
#include "ESP/Event.h"
#include "ESP/GhostShip.h"
#include "ESP/Island.h"
#include "ESP/Item.h"
#include "ESP/Kraken.h"
#include "ESP/LoreBook.h"
#include "ESP/MapPin.h"
#include "ESP/Megalodon.h"
#include "ESP/Mermaid.h"
#include "ESP/NPC.h"
#include "ESP/Player.h"
#include "ESP/Rowboat.h"
#include "ESP/Skeleton.h"
#include "ESP/SkeletonThrone.h"
#include "ESP/Shark.h"
#include "ESP/Ship.h"
#include "ESP/Shipwreck.h"
#include "ESP/Siren.h"
#include "ESP/Storm.h"
#include "ESP/TreasureMap.h"
#include "ESP/Trigger.h"
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
        if (!world->OwningGameInstance->IsA(UAthenaGameInstance::StaticClass()))
        {
            return false;
        }
        if (!reinterpret_cast<UAthenaGameInstance*>(world->OwningGameInstance)->GameContext)
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

    void RunOnce(UWorld* world)
    {
        try
        {
            ESP::Item::GetPrices(world);
        }
        catch (...)
        {
            throw std::runtime_error("ESP::Item::GetPrices");
        }
    }

    void Hack()
    {
        UWorld* world = nullptr;
            
        try {
            world = UAthenaGameViewportClient::GAthenaGameViewportClient->World;
        }
        catch (...)
        {
            throw std::runtime_error("UAthenaGameViewportClient::GAthenaGameViewportClient->World");
        } 

        auto check = false;
        try {
            check = NullChecks(world);
        }
        catch (...)
        {
            throw std::runtime_error("NullChecks");
        }

        if (check)
        {
            static std::once_flag flag;
            std::call_once(flag, [&](){ RunOnce(world); });

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

            // Island
            if (config.esp.island.enable)
            {
                try
                {
                    ESP::Island::Draw(world);
                }
                catch (...)
                {
                    throw std::runtime_error("ESP::Island::Draw");
                }
            }

            // Island level actors
            const auto levels = world->Levels;
            for (int levelIndex = 6; levelIndex < levels.Num(); ++levelIndex)
            {
                for (const auto& actor : levels[levelIndex]->AActors)
                {
                    if (!actor)
                    {
                        continue;
                    }

                    // NPC
                    if (config.esp.npc.enable)
                    {
                        if (actor->IsA(ANPC::StaticClass()))
                        {
                            try
                            {
                                ESP::NPC::Draw(world, actor);
                            }
                            catch (...)
                            {
                                throw std::runtime_error("ESP::NPC::Draw");
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

                    // Trigger
                    if (config.esp.trigger.enable)
                    {
                        if (actor->IsA(ASwitchMechanismTrigger::StaticClass()))
                        {
                            try
                            {
                                ESP::Trigger::DrawSwitch(world, actor);
                            }
                            catch (...)
                            {
                                throw std::runtime_error("ESP::Trigger::DrawSwitch");
                            }

                            continue;
                        }

                        if (actor->IsA(APressurePlateMechanismTriggerBase::StaticClass()))
                        {
                            try
                            {
                                ESP::Trigger::DrawPressurePlate(world, actor);
                            }
                            catch (...)
                            {
                                throw std::runtime_error("ESP::Trigger::DrawPressurePlate");
                            }

                            continue;
                        }

                        if (actor->IsA(ATripwireMechanismTrigger::StaticClass()))
                        {
                            try
                            {
                                ESP::Trigger::DrawTripwire(world, actor);
                            }
                            catch (...)
                            {
                                throw std::runtime_error("ESP::Trigger::DrawTripwire");
                            }

                            continue;
                        }

                        if (actor->IsA(AVolumeMechanismTrigger::StaticClass()))
                        {
                            try
                            {
                                ESP::Trigger::DrawVolume(world, actor);
                            }
                            catch (...)
                            {
                                throw std::runtime_error("ESP::Trigger::DrawVolume");
                            }

                            continue;
                        }

                        if (actor->GetComponentByClass(UMechanismTriggerComponent::StaticClass()))
                        {
                            try
                            {
                                ESP::Trigger::Draw(world, actor);
                            }
                            catch (...)
                            {
                                throw std::runtime_error("ESP::Trigger::Draw");
                            }

                            continue;
                        }
                    }
                }
            }

            if (config.aim.weapon.enable)
            {
                try
                {
                    Aimbot::Weapon::InitAim(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Aimbot::Weapon::InitAim");
                }
            }

            if (config.aim.harpoon.enable)
            {
                try
                {
                    Aimbot::Harpoon::InitAim(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Aimbot::Harpoon::InitAim");
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
            const auto level = world->PersistentLevel;
            for (const auto& actor : level->AActors)
            {
                if (!actor)
                {
                    continue;
                }

                if (actor == world->OwningGameInstance->LocalPlayers[0]->PlayerController)
                {
                    continue;
                }

                /*
                // Class Athena.LaunchableProjectile
                // 0x0238 (0x0600 - 0x03C8)
                class ALaunchableProjectile : public AActor
                {
                public:
                    char pad_0x03C8[0x0118];
                    float LaunchSpeed; // 0x04E0(0x0004)
                    float GravityScale; // 0x04E4(0x0004)
                    char pad_0x04E8[0x0118];

                    static UClass* StaticClass()
                    {
                        static auto ptr = UObject::FindObject<UClass>("Class Athena.LaunchableProjectile");
                        return ptr;
                    }
                };

                // Class Athena.CannonProjectile
                // 0x0050 (0x0650 - 0x0600)
                class ACannonProjectile : public ALaunchableProjectile
                {
                public:
                    char pad_0x0600[0x0050];

                    static UClass* StaticClass()
                    {
                        static auto ptr = UObject::FindObject<UClass>("Class Athena.CannonProjectile");
                        return ptr;
                    }
                };

                static auto found = false;

                if (actor->IsA(ACannon::StaticClass()))
                {
                    const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
                    const auto localPlayer = reinterpret_cast<AAthenaCharacter*>(playerController->Pawn);
                    const auto cannon = reinterpret_cast<ACannon*>(actor);

                    if (const auto attachActor = localPlayer->GetAttachParentActor())
                    {
                        if (attachActor != actor)
                        {
                            continue;
                        }
                    }
                    else
                    {
                        continue;
                    }

                    auto cannonRotation = cannon->K2_GetActorRotation();
                    auto cameraLocation = playerController->PlayerCameraManager->GetCameraLocation();
                    auto cannonLocation = cannon->K2_GetActorLocation();

                    const auto angle = FRotator{ cannon->ServerPitch, cannon->ServerYaw, 0.f } + cannonRotation;
                    const auto forwardVector = angle.Vector();
                    auto location = cannon->K2_GetActorLocation();
                    location.Z += 100.f;
                    location += forwardVector * 150.f;

                    const auto cameraAngle = playerController->PlayerCameraManager->GetCameraRotation();
                    const auto cameraForwardVector = cameraAngle.Vector();
                    auto adjustLocation = cannon->K2_GetActorLocation();
                    adjustLocation += cameraForwardVector * 200.f;

                    if (!found)
                    {
                        spdlog::info("Cannon {} {} {}", cannonLocation.X, cannonLocation.Y, cannonLocation.Z);
                        spdlog::info("Camera {} {} {}", cameraLocation.X, cameraLocation.Y, cameraLocation.Z);
                        spdlog::info("Adjusted {} {} {}", location.X, location.Y, location.Z);
                        spdlog::info("Angle {} {} {}", angle.Yaw, angle.Pitch, angle.Roll);
                        spdlog::info("Forward {} {} {}", forwardVector.X, forwardVector.Y, forwardVector.Z);
                        spdlog::info("cameraAngle {} {} {}", cameraAngle.Yaw, cameraAngle.Pitch, cameraAngle.Roll);
                        spdlog::info("cameraForwardVector {} {} {}", cameraForwardVector.X, cameraForwardVector.Y, cameraForwardVector.Z);
                        spdlog::info("Camera Adjusted {} {} {}", adjustLocation.X, adjustLocation.Y, adjustLocation.Z);
                    }
                }

                if (!found && actor->IsA(ACannonProjectile::StaticClass()))
                {
                    const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
                    auto ball = reinterpret_cast<ACannonProjectile*>(actor);

                    static auto location = ball->K2_GetActorLocation();
                    static auto speed = ball->LaunchSpeed;
                    static auto gravity = ball->GravityScale;

                    spdlog::info("Ball {} {} {} Speed {} Gravity {}", location.X, location.Y, location.Z, speed, gravity);

                    auto position = FVector2D{};
                    if (playerController->ProjectWorldLocationToScreen(location, &position))
                    {
                        Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::White);
                    }

                    if (playerController->ProjectWorldLocationToScreen(location + ball->AttachmentReplication.LocationOffset, &position))
                    {
                        Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::White);
                    }

                    found = true;
                }*/

                // Player
                if (actor->IsA(AAthenaPlayerCharacter::StaticClass()))
                {
                    if (config.aim.weapon.enable && config.aim.weapon.player)
                    {
                        try
                        {
                            Aimbot::Weapon::CalculateAim(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::Weapon::CalculateAim");
                        }
                    }

                    if (config.aim.harpoon.enable)
                    {
                        try
                        {
                            Aimbot::Harpoon::CalculateAim(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::Harpoon::CalculateAim");
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
                    if (config.aim.weapon.enable && config.aim.weapon.skeleton)
                    {
                        try
                        {
                            Aimbot::Weapon::CalculateAim(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::Weapon::CalculateAim");
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

                // NPC
                if (config.esp.npc.enable)
                {
                    if (actor->IsA(ANPC::StaticClass()))
                    {
                        try
                        {
                            ESP::NPC::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::NPC::Draw");
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
                    if (config.aim.weapon.enable)
                    {
                        try
                        {
                            Aimbot::Weapon::CalculateAim(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::Weapon::CalculateAim");
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
                if (actor->IsA(AFloatingItemProxy::StaticClass()))
                {
                    if (config.aim.harpoon.enable)
                    {
                        try
                        {
                            Aimbot::Harpoon::CalculateAim(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("Aimbot::Harpoon::CalculateAim");
                        }
                    }

                    if (config.esp.item.enable)
                    {
                        try
                        {
                            ESP::Item::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Item::Draw");
                        }
                    }

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

                // Shipwreck
                if (config.esp.shipwreck.enable)
                {
                    if (actor->IsA(AShipwreck::StaticClass()))
                    {
                        try
                        {
                            ESP::Shipwreck::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Shipwreck::Draw");
                        }

                        continue;
                    }
                }

                // Event
                if (config.esp.event.enable)
                {
                    if (actor->IsA(AGameplayEventSignal::StaticClass()))
                    {
                        try
                        {
                            ESP::Event::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Event::Draw");
                        }

                        continue;
                    }
                }

                // Trigger
                if (config.esp.trigger.enable)
                {
                    if (actor->IsA(ASwitchMechanismTrigger::StaticClass()))
                    {
                        try
                        {
                            ESP::Trigger::DrawSwitch(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Trigger::DrawSwitch");
                        }

                        continue;
                    }

                    if (actor->IsA(APressurePlateMechanismTriggerBase::StaticClass()))
                    {
                        try
                        {
                            ESP::Trigger::DrawPressurePlate(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Trigger::DrawPressurePlate");
                        }

                        continue;
                    }

                    if (actor->IsA(ATripwireMechanismTrigger::StaticClass()))
                    {
                        try
                        {
                            ESP::Trigger::DrawTripwire(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Trigger::DrawTripwire");
                        }

                        continue;
                    }

                    if (actor->IsA(AVolumeMechanismTrigger::StaticClass()))
                    {
                        try
                        {
                            ESP::Trigger::DrawVolume(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Trigger::DrawVolume");
                        }

                        continue;
                    }

                    if (actor->GetComponentByClass(UMechanismTriggerComponent::StaticClass()))
                    {
                        try
                        {
                            ESP::Trigger::Draw(world, actor);
                        }
                        catch (...)
                        {
                            throw std::runtime_error("ESP::Trigger::Draw");
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
            }

            if (config.aim.weapon.enable)
            {
                try
                {
                    Aimbot::Weapon::Aim(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Aimbot::Weapon::Aim");
                }
            }

            if (config.aim.harpoon.enable)
            {
                try
                {
                    Aimbot::Harpoon::Aim(world);
                }
                catch (...)
                {
                    throw std::runtime_error("Aimbot::Harpoon::Aim");
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

            try
            {
                const auto onlinePlayerController = reinterpret_cast<AOnlineAthenaPlayerController*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController);

                if (config.client.antiafk == onlinePlayerController->IdleDisconnectEnabled)
                {
                    onlinePlayerController->IdleDisconnectEnabled = !config.client.antiafk;
                }
            }
            catch (...)
            {
                throw std::runtime_error("IdleDisconnect");
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
