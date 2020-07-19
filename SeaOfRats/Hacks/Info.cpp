#include "Info.h"

#include "SDK/SDK.h"
#include "spdlog/spdlog.h"

#include "Config.h"
#include "Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace Info
    {
        void DrawCrosshair(AHUD* hud)
        {
            const float centerX = static_cast<float>(hud->Canvas->SizeX) * 0.5f;
            const float centerY = static_cast<float>(hud->Canvas->SizeY) * 0.5f;
            hud->Canvas->K2_DrawLine(FVector2D(centerX, centerY - 5), FVector2D(centerX, centerY + 5), 2, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
            hud->Canvas->K2_DrawLine(FVector2D(centerX - 5, centerY), FVector2D(centerX + 5, centerY), 2, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

            //hud->DrawLine(centerX, centerY - 5, centerX, centerY + 5, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
            //hud->DrawLine(centerX - 5, centerY, centerX + 5, centerY, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        }

        void DrawPlayerList(UGameViewportClient* client, AHUD* hud)
        {
            auto world = client->World;
            if (!world)
            {
                return;
            }

            auto gameState = client->World->GameState;
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
                auto crew = crews[i];
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
                Drawing::DrawInterfaceString(hud, shipType, FVector2D(positionX, positionY), Drawing::Colour::White, false, false);
                positionY += 15.0f;
                for (int32_t j = 0; j < players.Num(); ++j)
                {
                    auto player = players[j];
                    std::wstring playerName = player->PlayerName.c_str();
                    Drawing::DrawInterfaceString(hud, playerName, FVector2D(positionX + 10.0f, positionY), Drawing::Colour::White, false, false);
                    positionY += 15.0f;
                }
                positionY += 10.0f;
            }
        }

        void DrawCompass(UGameViewportClient* client, AHUD* hud)
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

            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto cameraManager = playerController->PlayerCameraManager;

            if (!cameraManager)
            {
                spdlog::warn("CameraManager null");
                return;
            }

            auto rotation = cameraManager->GetCameraRotation();
            int32_t bearing = static_cast<int32_t>(std::round(rotation.Yaw) + 450) % 360;
            int32_t index = static_cast<int32_t>(std::trunc(std::fmodf(static_cast<float>(bearing) + 11.25f, 360.0f)) * 0.04444444444f);

            float centerX = static_cast<float>(hud->Canvas->SizeX) * 0.5f;
            Drawing::DrawInterfaceString(hud, std::to_wstring(bearing), FVector2D(centerX, 10), Drawing::Colour::White);
            Drawing::DrawInterfaceString(hud, compassDirections[index], FVector2D(centerX, 25), Drawing::Colour::White);
        }

        void DrawOxygen(UGameViewportClient* client, AHUD* hud)
        {
            auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(client->GameInstance->LocalPlayers[0]->PlayerController->Pawn);

            auto drowningComponent = localPlayer->DrowningComponent;
            if (drowningComponent)
            {
                int oxygenLevel = static_cast<int>(drowningComponent->OxygenLevel * 100.0f);
                if (oxygenLevel < 100)
                {
                    float centerX = static_cast<float>(hud->Canvas->SizeX) * 0.5f;
                    std::wstring oxygenText = L"Oxygen: " + std::to_wstring(oxygenLevel) + L"%";
                    Drawing::DrawInterfaceString(hud, oxygenText, FVector2D(centerX, 50), Drawing::Colour::Red);
                }
            }
        }

        void DrawWaterLevel(UGameViewportClient* client, AHUD* hud)
        {
            auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(client->GameInstance->LocalPlayers[0]->PlayerController->Pawn);

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
                        float centerX = static_cast<float>(hud->Canvas->SizeX) * 0.5f;
                        Drawing::DrawInterfaceString(hud, waterText, FVector2D(centerX, 65), Drawing::Colour::Red);
                    }
                }
            }
        }

        void DrawAnchor(UGameViewportClient* client, AHUD* hud)
        {
            auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(client->GameInstance->LocalPlayers[0]->PlayerController->Pawn);

            auto parent = localPlayer->GetAttachParentActor();

            if (parent && parent->IsA(ACapstanArm::StaticClass()))
            {
                auto parentParent = parent->GetParentActor();
                if (parentParent && parentParent->IsA(ACapstan::StaticClass()))
                {
                    auto capstan = reinterpret_cast<ACapstan*>(parentParent);
                    int32_t anchorLevel = static_cast<int32_t>(capstan->NetState.TargetRatio * 100.0f);

                    std::wstring capstanText = L"Anchor Level: " + std::to_wstring(anchorLevel) + L"%";
                    float centerX = static_cast<float>(hud->Canvas->SizeX) * 0.5f;
                    Drawing::DrawInterfaceString(hud, capstanText, FVector2D(centerX, 80), Drawing::Colour::Red);
                }
            }

        }

        void Render(UGameViewportClient* client, AHUD* hud)
        {
            if (config->crosshairInfo)
            {
                DrawCrosshair(hud);
            }

            if (config->playerListInfo)
            {
                DrawPlayerList(client, hud);
            }

            if (config->compassInfo)
            {
                DrawCompass(client, hud);
            }

            if (config->oxygenInfo)
            {
                DrawOxygen(client, hud);
            }

            if (config->waterLevelInfo)
            {
                DrawWaterLevel(client, hud);
            }

            if (config->anchorInfo)
            {
                DrawAnchor(client, hud);
            }

        }
    }
}
