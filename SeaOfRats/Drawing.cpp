#include "Drawing.h"

#include <Windows.h>

#include <string>

#include "include/imgui/imgui.h"
#include "include/imgui/imgui_internal.h"
#include "include/SDK/SDK.h"

using namespace SDK;

namespace Drawing
{
    namespace Colour
    {
        ImU32 colour(int r, int g, int b, int a = 255)
        {
            return IM_COL32(r, g, b, a);
        }
        //const ImU32 White = colour(253, 254, 254);
        const ImU32 White = colour(255, 255, 255);
        //const ImU32 Black = colour(23, 32, 42);
        const ImU32 Black = colour(0, 0, 0);
        const ImU32 Grey = colour(153, 164, 164);
        const ImU32 Red = colour(192, 57, 43);
        const ImU32 Orange = colour(230, 126, 34);
        const ImU32 Yellow = colour(241, 196, 15);
        const ImU32 Green = colour(39, 174, 96);
        const ImU32 Blue = colour(52, 152, 219);
        const ImU32 Purple = colour(142, 68, 173);
    }

    void DrawLine(const FVector2D& start, const FVector2D& end, const ImU32 colour, const float thickness)
    {
        Window->DrawList->AddLine(ImVec2(start.X, start.Y), ImVec2(end.X, end.Y), colour, thickness);
    }

    void DrawString(const std::string string, const FVector2D& position, const ImU32 colour, bool centreX , bool centreY)
    {
        ImVec2 newPosition(position.X, position.Y);
        if (centreX || centreY)
        {
            auto textSize = ImGui::CalcTextSize(string.c_str());
            if (centreX)
            {
                newPosition.x -= textSize.x * 0.5f;
            }

            if (centreY)
            {
                newPosition.y -= textSize.y * 0.5f;
            }
        }

        Window->DrawList->AddText(ImVec2(newPosition.x + 1, newPosition.y + 1), Colour::Black, string.c_str());
        Window->DrawList->AddText(newPosition, colour, string.c_str());
    }

    void DrawCircle(const FVector2D& position, const float radius, const ImU32 colour, const float thickness)
    {
        Window->DrawList->AddCircle(ImVec2(position.X, position.Y), radius, colour, 0, thickness);
    }

    void DrawCircleFilled(const FVector2D& position, const float radius, const ImU32 colour)
    {
        Window->DrawList->AddCircleFilled(ImVec2(position.X, position.Y), radius, colour, 0);
    }

    void DrawRect(const FVector2D& minPosition, const FVector2D& maxPosition, const ImU32 colour, const float thickness)
    {
        Window->DrawList->AddRect(ImVec2(minPosition.X, minPosition.Y), ImVec2(maxPosition.X, maxPosition.Y), colour, 0.0f, 0, thickness);
    }

    void DrawRectFilled(const FVector2D& minPosition, const FVector2D& maxPosition, const ImU32 colour)
    {
        Window->DrawList->AddRectFilled(ImVec2(minPosition.X, minPosition.Y), ImVec2(maxPosition.X, maxPosition.Y), colour, 0.0f, 0);
    }

    void DrawHealthBar(const FVector2D& minPosition, const FVector2D& maxPosition, float currentHealth, float maxHealth)
    {
        if (currentHealth > maxHealth)
        {
            currentHealth = maxHealth;
        }
        float health = currentHealth / maxHealth;
        float x = minPosition.X;
        float y = minPosition.Y;
        float w = maxPosition.X - x;
        float h = maxPosition.Y - y;

        Window->DrawList->AddRectFilled(ImVec2(x - 1, y - 1), ImVec2(x + w + 1, y + h + 1), Colour::Black);
        Window->DrawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), Colour::Red);
        Window->DrawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w * health, y + h), Colour::Green);
    }

    void DrawBoundingRect(UWorld* world, AActor* actor, const ImU32 colour)
    {
        auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;

        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);
        /*FRotator rotation = actor->K2_GetActorRotation();

        FVector topLeft;
        FVector bottomRight;
        topLeft = { -extent.X, 0.f, extent.Z };
        bottomRight = { extent.X, 0.f, -extent.Z };

        FTransform const transform(rotation);

        topLeft = transform.TransformPosition(topLeft) + origin;
        bottomRight = transform.TransformPosition(bottomRight) + origin;*/

        FVector topLeft(origin.X - extent.X, origin.Y, origin.Z + extent.Z);
        FVector bottomRight(origin.X + extent.X, origin.Y, origin.Z - extent.Z);

        FVector2D topLeftScreen, bottomRightScreen;
        if (!playerController->ProjectWorldLocationToScreen(topLeft, &topLeftScreen) || !playerController->ProjectWorldLocationToScreen(bottomRight, &bottomRightScreen))
        {
            return;
        }

        DrawRect(topLeftScreen, bottomRightScreen, colour);
    }

    void DrawBoundingBox(UWorld* world, AActor* actor, const ImU32 colour)
    {
        auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;

        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);
        FRotator rotation = actor->K2_GetActorRotation();

        FVector vertices[2][4];
        vertices[0][0] = { -extent.X, -extent.Y,  -extent.Z };
        vertices[0][1] = { extent.X, -extent.Y,  -extent.Z };
        vertices[0][2] = { extent.X, extent.Y,  -extent.Z };
        vertices[0][3] = { -extent.X, extent.Y, -extent.Z };

        vertices[1][0] = { -extent.X, -extent.Y, extent.Z };
        vertices[1][1] = { extent.X, -extent.Y, extent.Z };
        vertices[1][2] = { extent.X, extent.Y, extent.Z };
        vertices[1][3] = { -extent.X, extent.Y, extent.Z };

        FVector2D screen[2][4];
        FTransform const transform(rotation);

        for (int32_t i = 0; i < 2; i++)
        {
            for (int32_t j = 0; j < 4; j++)
            {
                auto& vertex = vertices[i][j];
                vertex = transform.TransformPosition(vertex) + origin;
                if (!playerController->ProjectWorldLocationToScreen(vertex, &screen[i][j]))
                {
                    return;
                }
            }
        }

        for (int32_t i = 0; i < 4; i++)
        {
            DrawLine(screen[0][i], screen[0][(i + 1) % 4], colour);
            DrawLine(screen[1][i], screen[1][(i + 1) % 4], colour);
            DrawLine(screen[0][i], screen[1][i], colour);
        }
    }
}
