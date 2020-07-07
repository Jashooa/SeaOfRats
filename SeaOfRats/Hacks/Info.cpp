#include "Info.h"

#include "spdlog/spdlog.h"

#include "Global.h"
#include "SDK.hpp"

using namespace SDK;

namespace Hacks
{
    void RenderCrosshair(UCanvas* canvas)
    {
        const float centerX = static_cast<float>(canvas->SizeX) / 2;
        const float centerY = static_cast<float>(canvas->SizeY) / 2;
        canvas->K2_DrawLine(FVector2D(centerX, centerY - 5), FVector2D(centerX, centerY + 5), 2, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        canvas->K2_DrawLine(FVector2D(centerX - 5, centerY), FVector2D(centerX + 5, centerY), 2, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

        /*spdlog::info("MyHUD: {:p}", reinterpret_cast<void*>(client->GameInstance->LocalPlayers[0]->PlayerController->MyHUD));
        spdlog::info("GetHUD: {:p}", reinterpret_cast<void*>(client->GameInstance->LocalPlayers[0]->PlayerController->GetHUD()));
        spdlog::info("MyHUD->Canvas: {:p}", reinterpret_cast<void*>(client->GameInstance->LocalPlayers[0]->PlayerController->MyHUD->Canvas));
        spdlog::info("GetHUD->Canvas2: {:p}", reinterpret_cast<void*>(client->GameInstance->LocalPlayers[0]->PlayerController->GetHUD()->Canvas));
        spdlog::info("canvas: {:p}", reinterpret_cast<void*>(canvas));
        AHUD* hud = client->GameInstance->LocalPlayers[0]->PlayerController->GetHUD();
        hud->Canvas = canvas;

        AHUD* hud2 = client->GameInstance->LocalPlayers[0]->PlayerController->MyHUD;
        hud2->Canvas = canvas;*/

        //hud->Canvas->K2_DrawLine(FVector2D(centerX, centerY - 5), FVector2D(centerX, centerY + 5), 2, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        //hud->Canvas->K2_DrawLine(FVector2D(centerX - 5, centerY), FVector2D(centerX + 5, centerY), 2, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

        //hud->DrawLine(centerX, centerY - 5, centerX, centerY + 5, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        //hud->DrawLine(centerX - 5, centerY, centerX + 5, centerY, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

        //hud2->DrawLine(centerX, centerY - 5, centerX, centerY + 5, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        //hud2->DrawLine(centerX - 5, centerY, centerX + 5, centerY, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
    }
}