#include "Info.h"

#include "spdlog/spdlog.h"

#include "SDK.hpp"

using namespace SDK;

namespace Hacks
{
    void RenderCrosshair(AHUD* hud)
    {
        const float centerX = static_cast<float>(hud->Canvas->SizeX) / 2;
        const float centerY = static_cast<float>(hud->Canvas->SizeY) / 2;
        hud->Canvas->K2_DrawLine(FVector2D(centerX, centerY - 5), FVector2D(centerX, centerY + 5), 2, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        hud->Canvas->K2_DrawLine(FVector2D(centerX - 5, centerY), FVector2D(centerX + 5, centerY), 2, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

        //hud->DrawLine(centerX, centerY - 5, centerX, centerY + 5, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        //hud->DrawLine(centerX - 5, centerY, centerX + 5, centerY, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
    }
}