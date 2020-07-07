#include "Drawing.h"

#include <cmath>
#include <string>

#include "SDK.hpp"

using namespace SDK;

namespace Drawing
{
    namespace Colour
    {
        FLinearColor colour(int r, int g, int b, int a = 255)
        {
            return FLinearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
        }
        //const FLinearColor White = colour(253, 254, 254);
        const FLinearColor White = colour(255, 255, 255);
        //const FLinearColor Black = colour(23, 32, 42);
        const FLinearColor Black = colour(0, 0, 0);
        const FLinearColor Grey = colour(153, 164, 164);
        const FLinearColor Red = colour(192, 57, 43);
        const FLinearColor Orange = colour(230, 126, 34);
        const FLinearColor Yellow = colour(241, 196, 15);
        const FLinearColor Green = colour(39, 174, 96);
        const FLinearColor Blue = colour(52, 152, 219);
        const FLinearColor Purple = colour(142, 68, 173);
    }

    void DrawActorString(AHUD* hud, const std::wstring string, const FVector2D& position, const FLinearColor& color)
    {
        FVector2D newPosition(std::trunc(position.X), std::trunc(position.Y));
        hud->Canvas->K2_DrawText(RobotoFont, static_cast<FString>(string.c_str()), newPosition, color, 1.0f, Colour::Black, FVector2D(0.0f, 0.0f), true, true, true, Colour::Black);
        //hud->DrawText(static_cast<FString>(string.c_str()), color, newPosition.X, newPosition.Y, RobotoFont, 1.0f, false);
    }

    void DrawRect(AHUD* hud, const FVector2D& minPosition, const FVector2D& maxPosition, const FLinearColor& color, const float thickness = 1.0f)
    {
        hud->Canvas->K2_DrawLine(minPosition, FVector2D(maxPosition.X, minPosition.Y), thickness, color);
        hud->Canvas->K2_DrawLine(minPosition, FVector2D(minPosition.X, maxPosition.Y), thickness, color);
        hud->Canvas->K2_DrawLine(FVector2D(minPosition.X, maxPosition.Y), maxPosition, thickness, color);
        hud->Canvas->K2_DrawLine(FVector2D(maxPosition.X, minPosition.Y), maxPosition, thickness, color);
    }
}