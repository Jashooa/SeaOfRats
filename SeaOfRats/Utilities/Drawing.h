#pragma once

#include <vector>

#include "include/FontAwesome/FontAwesome.h"
#include "include/imgui/imgui.h"
#include "include/imgui/imgui_internal.h"
#include "include/SDK/SDK.h"

namespace Utilities
{
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

        SDK::FVector2D GetScreenCentre();
        void DrawLine(const SDK::FVector2D& start, const SDK::FVector2D& end, ImU32 colour, float thickness = 1.f);
        void DrawString(const std::string& string, const SDK::FVector2D& position, ImU32 colour, bool centreX = true, bool centreY = true);
        void DrawCircle(const SDK::FVector2D& position, float radius, ImU32 colour, float thickness = 1.f);
        void DrawCircleFilled(const SDK::FVector2D& position, float radius, ImU32 colour);
        void DrawRect(const SDK::FVector2D& minPosition, const SDK::FVector2D& maxPosition, ImU32 colour, float thickness = 1.f);
        void DrawRectFilled(const SDK::FVector2D& minPosition, const SDK::FVector2D& maxPosition, ImU32 colour);
        void DrawHealthBar(const SDK::FVector2D& position, float currentHealth, float maxHealth);
        void DrawBoundingRect(SDK::UWorld* world, SDK::AActor* actor, ImU32 colour);
        void DrawBoundingBox(SDK::UWorld* world, SDK::AActor* actor, ImU32 colour);
        void DrawPath(SDK::UWorld* world, const std::vector<SDK::FVector>& path, ImU32 colour);

        inline ImGuiWindow* Window = nullptr;
    }
}
