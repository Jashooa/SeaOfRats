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
            inline ImU32 colour(int r, int g, int b, int a = 255)
            {
                return IM_COL32(r, g, b, a);
            }
            //inline const auto White = colour(253, 254, 254);
            inline const auto White = colour(255, 255, 255);
            //inline const auto Black = colour(23, 32, 42);
            inline const auto Black = colour(0, 0, 0);
            inline const auto Grey = colour(153, 164, 164);
            inline const auto Red = colour(192, 57, 43);
            inline const auto Orange = colour(230, 126, 34);
            inline const auto Yellow = colour(241, 196, 15);
            inline const auto Green = colour(39, 174, 96);
            inline const auto Blue = colour(52, 152, 219);
            inline const auto Purple = colour(142, 68, 173);
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
