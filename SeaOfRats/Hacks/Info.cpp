#include "Info.h"

#include "spdlog/spdlog.h"

#include "Config.h"
#include "Drawing.h"
#include "SDK.hpp"

using namespace SDK;

namespace Hacks
{
    void DrawCrosshair(AHUD* hud)
    {
        const float centerX = static_cast<float>(hud->Canvas->SizeX) / 2;
        const float centerY = static_cast<float>(hud->Canvas->SizeY) / 2;
        hud->Canvas->K2_DrawLine(FVector2D(centerX, centerY - 5), FVector2D(centerX, centerY + 5), 2, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        hud->Canvas->K2_DrawLine(FVector2D(centerX - 5, centerY), FVector2D(centerX + 5, centerY), 2, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

        //hud->DrawLine(centerX, centerY - 5, centerX, centerY + 5, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        //hud->DrawLine(centerX - 5, centerY, centerX + 5, centerY, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
    }

    void DrawCompass(UGameViewportClient* client, AHUD* hud)
    {
        spdlog::debug("DrawCompass Before");
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

        float centerX = static_cast<float>(hud->Canvas->SizeX) / 2.0f;
        Drawing::DrawInterfaceString(hud, std::to_wstring(bearing), FVector2D(centerX, 10), Drawing::Colour::White);
        Drawing::DrawInterfaceString(hud, compassDirections[index], FVector2D(centerX, 25), Drawing::Colour::White);
        spdlog::debug("DrawCompass After");
    }

    void DrawPlayerList(UGameViewportClient* client, AHUD* hud)
    {
        spdlog::debug("DrawPlayerList Before");
        auto gameState = reinterpret_cast<AAthenaGameState*>(client->World->GameState);
        auto crewService = gameState->CrewService;

        if (crewService == nullptr)
        {
            return;
        }

        auto crews = crewService->Crews;

        float positionX = 10.0f;
        float positionY = 60.0f;
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
        spdlog::debug("DrawPlayerList After");
    }

    void RenderInfo(UGameViewportClient* client, AHUD* hud)
    {
        if (config->crosshair)
        {
            DrawCrosshair(hud);
        }

        if (config->compass)
        {
            DrawCompass(client, hud);
        }

        if (config->playerList)
        {
            DrawPlayerList(client, hud);
        }
    }
}