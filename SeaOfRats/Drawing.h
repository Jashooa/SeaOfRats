#pragma once

#include "SDK.hpp"

using namespace SDK;

namespace Drawing
{
    inline UFont* RobotoFont = nullptr;
    inline UFont* RobotoTinyFont = nullptr;

    namespace Colour
    {
        FLinearColor colour(int r, int g, int b, int a);
        extern const FLinearColor White;
        extern const FLinearColor Black;
        extern const FLinearColor Grey;
        extern const FLinearColor Red;
        extern const FLinearColor Orange;
        extern const FLinearColor Yellow;
        extern const FLinearColor Green;
        extern const FLinearColor Blue;
        extern const FLinearColor Purple;
    }

    void DrawActorString(AHUD* hud, const std::wstring string, const FVector2D& position, const FLinearColor& color);
    void DrawInterfaceString(AHUD* hud, const std::wstring string, const FVector2D& position, const FLinearColor& color, bool centreX = true, bool centreY = true);
    void DrawRect(AHUD* hud, const FVector2D& minPosition, const FVector2D& maxPosition, const FLinearColor& color, const float thickness);
    void DrawBoundingBox(UGameViewportClient* client, AHUD* hud, AActor* actor, const FLinearColor& color);
}