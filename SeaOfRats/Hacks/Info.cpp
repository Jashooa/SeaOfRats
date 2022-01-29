#include "Info.h"

#include "include/SDK/SDK.h"
#include "include/spdlog/spdlog.h"

#include <cmath>

#include "Config.h"
#include "Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace Info
    {
        void DrawCrosshair()
        {
            const float centerX = std::trunc(Drawing::Window->Size.x * 0.5f);
            const float centerY = std::trunc(Drawing::Window->Size.y *0.5f);
            Drawing::DrawLine(FVector2D(centerX, centerY - 5), FVector2D(centerX, centerY + 5 + 1), Drawing::Colour::White);
            Drawing::DrawLine(FVector2D(centerX - 5, centerY), FVector2D(centerX + 5 + 1, centerY), Drawing::Colour::White);
        }

        void DrawPlayerList(UWorld* world)
        {
            auto gameState = world->GameState;
            if (!gameState)
            {
                return;
            }

            if (!gameState->IsA(AAthenaGameState::StaticClass()))
            {
                return;
            }

            auto athenaGameState = reinterpret_cast<AAthenaGameState*>(gameState);
            auto crewService = athenaGameState->CrewService;
            if (!crewService)
            {
                return;
            }

            auto crews = crewService->Crews;

            float positionX = 10.0f;
            float positionY = 120.0f;
            for (int32_t i = 0; i < crews.Num(); ++i)
            {
                FCrew crew = crews[i];
                auto players = crew.Players;
                std::wstring shipType;
                switch (crew.CrewSessionTemplate.MaxMatchmakingPlayers)
                {
                    case 2:
                        shipType = L"Sloop";
                        break;
                    case 3:
                        shipType = L"Brigantine";
                        break;
                    case 4:
                        shipType = L"Galleon";
                        break;
                    default:
                        shipType = L"";
                        break;
                }
                //shipType = shipType + L" " + UKismetGuidLibrary::Conv_GuidToString(crew.CrewId).c_str();
                Drawing::DrawString(shipType, FVector2D(positionX, positionY), Drawing::Colour::White, false, false);
                positionY += 15.0f;
                for (int32_t j = 0; j < players.Num(); ++j)
                {
                    auto player = reinterpret_cast<AAthenaPlayerState*>(players[j]);
                    
                    std::wstring activity = L"";
                    switch (player->GetPlayerActivity())
                    {
                        case EPlayerActivityType::EPlayerActivityType__None:
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Bailing:
                            activity = L"Bailing";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Cannon:
                            activity = L"Cannon";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Cannon_END:
                            activity = L"Cannon";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Capstan:
                            activity = L"Capstan";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Capstan_END:
                            activity = L"Capstan";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__CarryingBooty:
                            activity = L"Carrying Booty";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__CarryingBooty_END:
                            activity = L"Carrying Booty";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Dead:
                            activity = L"Dead";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Dead_END:
                            activity = L"Dead";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Digging:
                            activity = L"Digging";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Dousing:
                            activity = L"Dousing";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__EmptyingBucket:
                            activity = L"Emptying Bucket";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Harpoon:
                            activity = L"Harpoon";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Harpoon_END:
                            activity = L"Harpoon";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__LoseHealth:
                            activity = L"Losing Health";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Repairing:
                            activity = L"Repairing";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Sails:
                            activity = L"Sails";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Sails_END:
                            activity = L"Sails";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__UndoingRepair:
                            activity = L"Undoing Repair";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Wheel:
                            activity = L"Wheel";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Wheel_END:
                            activity = L"Wheel";
                            break;
                        default:
                            break;
                    }

                    std::wstring name = player->PlayerName.c_str();
                    if (!activity.empty())
                    {
                        name = name + L" - " + activity;
                    }
                    Drawing::DrawString(name, FVector2D(positionX + 10.0f, positionY), Drawing::Colour::White, false, false);
                    positionY += 15.0f;
                }
                positionY += 10.0f;
            }
        }

        void DrawCompass(UWorld* world)
        {
            static std::vector<const wchar_t*> compassDirections = {
                L"North",
                L"North North East",
                L"North East",
                L"East North East",
                L"East",
                L"East South East",
                L"South East",
                L"South South East",
                L"South",
                L"South South West",
                L"South West",
                L"West South West",
                L"West",
                L"West North West",
                L"North West",
                L"North North West"
            };

            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto cameraManager = playerController->PlayerCameraManager;

            if (!cameraManager)
            {
                spdlog::warn("CameraManager null");
                return;
            }

            auto rotation = cameraManager->GetCameraRotation();
            int32_t bearing = static_cast<int32_t>(std::round(rotation.Yaw) + 450) % 360;
            int32_t index = static_cast<int32_t>(std::trunc(std::fmodf(static_cast<float>(bearing) + 11.25f, 360.0f)) * 0.04444444444f);

            float centerX = Drawing::Window->Size.x * 0.5f;
            Drawing::DrawString(std::to_wstring(bearing), FVector2D(centerX, 10), Drawing::Colour::White);
            Drawing::DrawString(compassDirections[index], FVector2D(centerX, 25), Drawing::Colour::White);
        }

        void DrawOxygen(UWorld* world)
        {
            auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn);

            if (!localPlayer->IsInWater())
            {
                return;
            }

            auto drowningComponent = localPlayer->DrowningComponent;
            if (drowningComponent)
            {
                int oxygenLevel = static_cast<int>(drowningComponent->GetOxygenLevel() * 100.0f);
                if (oxygenLevel < 100)
                {
                    float centerX = Drawing::Window->Size.x * 0.5f;
                    std::wstring oxygenText = L"Oxygen: " + std::to_wstring(oxygenLevel) + L"%";
                    Drawing::DrawString(oxygenText, FVector2D(centerX, 50), Drawing::Colour::Red);
                }
            }
        }

        void DrawWaterLevel(UWorld* world)
        {
            auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn);

            auto ship = reinterpret_cast<AShip*>(localPlayer->GetCurrentShip());
            if (ship)
            {
                auto waterInfo = ship->GetInternalWater();
                if (waterInfo)
                {
                    float waterMax = waterInfo->InternalWaterParams.MaxWaterAmount;
                    int32_t waterLevel = static_cast<int32_t>((waterInfo->WaterAmount / waterMax) * 100.0f);
                    if (waterLevel > 10)
                    {
                        std::wstring waterText = L"Water Level: " + std::to_wstring(waterLevel) + L"%";
                        float centerX = Drawing::Window->Size.x * 0.5f;
                        Drawing::DrawString(waterText, FVector2D(centerX, 65), Drawing::Colour::Red);
                    }
                }
            }
        }

        void DrawAnchor(UWorld* world)
        {
            auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn);

            auto parent = localPlayer->GetAttachParentActor();

            if (parent && parent->IsA(ACapstanArm::StaticClass()))
            {
                auto parentParent = parent->GetParentActor();
                if (parentParent && parentParent->IsA(ACapstan::StaticClass()))
                {
                    auto capstan = reinterpret_cast<ACapstan*>(parentParent);
                    int32_t anchorLevel = static_cast<int32_t>(capstan->NetState.TargetRatio * 100.0f);

                    std::wstring capstanText = L"Anchor Level: " + std::to_wstring(anchorLevel) + L"%";
                    float centerX = Drawing::Window->Size.x * 0.5f;
                    Drawing::DrawString(capstanText, FVector2D(centerX, 80), Drawing::Colour::Red);
                }
            }

        }

        void Render(UWorld* world)
        {
            if (config.info.crosshair)
            {
                spdlog::debug("DrawCrosshair");
                DrawCrosshair();
            }

            if (config.info.playerList)
            {
                spdlog::debug("DrawPlayerList");
                DrawPlayerList(world);
            }

            if (config.info.compass)
            {
                spdlog::debug("DrawCompass");
                DrawCompass(world);
            }

            if (config.info.oxygen)
            {
                spdlog::debug("DrawOxygen");
                DrawOxygen(world);
            }

            if (config.info.waterLevel)
            {
                spdlog::debug("DrawWaterLevel");
                DrawWaterLevel(world);
            }

            if (config.info.anchor)
            {
                spdlog::debug("DrawAnchor");
                DrawAnchor(world);
            }

        }
    }
}
