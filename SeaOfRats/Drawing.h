#pragma once

#include <vector>

#include "include/FontAwesome/FontAwesome.h"
#include "include/imgui/imgui.h"
#include "include/imgui/imgui_internal.h"
#include "include/SDK/SDK.h"

using namespace SDK;

namespace Drawing
{
    namespace Colour
    {
        ImU32 colour(int r, int g, int b, int a);
        extern const ImU32 White;
        extern const ImU32 Black;
        extern const ImU32 Grey;
        extern const ImU32 Red;
        extern const ImU32 Orange;
        extern const ImU32 Yellow;
        extern const ImU32 Green;
        extern const ImU32 Blue;
        extern const ImU32 Purple;
    }

    FVector2D GetScreenCentre();
    void DrawLine(const FVector2D& start, const FVector2D& end, const ImU32 colour, const float thickness = 1.f);
    void DrawString(const std::string string, const FVector2D& position, const ImU32 colour, bool centreX = true, bool centreY = true);
    void DrawCircle(const FVector2D& position, const float radius, const ImU32 colour, const float thickness = 1.f);
    void DrawCircleFilled(const FVector2D& position, const float radius, const ImU32 colour);
    void DrawRect(const FVector2D& minPosition, const FVector2D& maxPosition, const ImU32 colour, const float thickness = 1.f);
    void DrawRectFilled(const FVector2D& minPosition, const FVector2D& maxPosition, const ImU32 colour);
    void DrawHealthBar(const FVector2D& position, float currentHealth, float maxHealth);
    void DrawBoundingRect(UWorld* world, AActor* actor, const ImU32 colour);
    void DrawBoundingBox(UWorld* world, AActor* actor, const ImU32 colour);
    void DrawPath(UWorld* world, std::vector<FVector> path, const ImU32 colour);

    inline ImGuiWindow* Window = nullptr;
}
