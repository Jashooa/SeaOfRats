#include "Drawing.h"

#include <Windows.h>

#include <string>

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

    FVector2D GetScreenCentre()
    {
        const float centreX = std::trunc(Drawing::Window->Size.x * 0.5f);
        const float centreY = std::trunc(Drawing::Window->Size.y * 0.5f);

        return FVector2D(centreX, centreY);
    }

    void DrawLine(const FVector2D& start, const FVector2D& end, const ImU32 colour, const float thickness)
    {
        Window->DrawList->AddLine(ImVec2(start.X, start.Y), ImVec2(end.X, end.Y), colour, thickness);
    }

    void DrawString(const std::string string, const FVector2D& position, const ImU32 colour, bool centreX, bool centreY)
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

        Window->DrawList->AddText(ImVec2(newPosition.x + 1.f, newPosition.y + 1.f), Colour::Black, string.c_str());
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
        Window->DrawList->AddRect(ImVec2(minPosition.X, minPosition.Y), ImVec2(maxPosition.X, maxPosition.Y), colour, 0.f, 0, thickness);
    }

    void DrawRectFilled(const FVector2D& minPosition, const FVector2D& maxPosition, const ImU32 colour)
    {
        Window->DrawList->AddRectFilled(ImVec2(minPosition.X, minPosition.Y), ImVec2(maxPosition.X, maxPosition.Y), colour, 0.f, 0);
    }

    void DrawHealthBar(const FVector2D& position, float currentHealth, float maxHealth)
    {
        if (currentHealth > maxHealth)
        {
            currentHealth = maxHealth;
        }
        std::string text = std::to_string(static_cast<int32_t>(currentHealth)) + "/" + std::to_string(static_cast<int32_t>(maxHealth));
        auto textSize = ImGui::CalcTextSize(text.c_str());
        float health = currentHealth / maxHealth;
        float x = position.X - 50.f;
        float y = std::truncf(position.Y - (textSize.y * 0.5f) + 2.f);
        float w = 100.f;
        float h = textSize.y - 2.f;

        Window->DrawList->AddRectFilled(ImVec2(x - 1.f, y - 1.f), ImVec2(x + w + 1.f, y + h + 1.f), Colour::Black);
        Window->DrawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), Colour::Red);
        Window->DrawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w * health, y + h), Colour::Green);
        DrawString(text, position, Colour::White);
    }

    void DrawBoundingRect(UWorld* world, AActor* actor, const ImU32 colour)
    {
        const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;

        /*FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);
        origin = actor->K2_GetActorLocation();
        FRotator rotation = actor->K2_GetActorRotation();

        FVector topLeft;
        FVector bottomRight;
        topLeft = { -extent.X, 0.f, extent.Z };
        bottomRight = { extent.X, 0.f, -extent.Z };

        const FTransform transform(rotation);

        topLeft = transform.TransformPosition(topLeft) + origin;
        bottomRight = transform.TransformPosition(bottomRight) + origin;

        FVector2D topLeftScreen, bottomRightScreen;
        if (!playerController->ProjectWorldLocationToScreen(topLeft, &topLeftScreen) || !playerController->ProjectWorldLocationToScreen(bottomRight, &bottomRightScreen))
        {
            return;
        }*/

        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);
        FRotator rotation = actor->K2_GetActorRotation();
        origin = actor->K2_GetActorLocation();

        FVector vertices[2][4];
        vertices[0][0] = { -extent.X, -extent.Y, -extent.Z }; // Left Back Bottom
        vertices[0][1] = { extent.X, -extent.Y, -extent.Z }; // Right Back Bottom
        vertices[0][2] = { extent.X, extent.Y, -extent.Z }; // Right Front Bottom
        vertices[0][3] = { -extent.X, extent.Y, -extent.Z }; // Left Front Bottom

        vertices[1][0] = { -extent.X, -extent.Y, extent.Z }; // Left Back Top
        vertices[1][1] = { extent.X, -extent.Y, extent.Z }; // Right Back Top
        vertices[1][2] = { extent.X, extent.Y, extent.Z }; // Right Front Top
        vertices[1][3] = { -extent.X, extent.Y, extent.Z }; // Left Front Top

        FVector2D screen[2][4];
        const FTransform transform(rotation);

        for (auto i = 0; i < 2; i++)
        {
            for (auto j = 0; j < 4; j++)
            {
                auto& vertex = vertices[i][j];
                vertex = transform.TransformPosition(vertex) + origin;
                if (!playerController->ProjectWorldLocationToScreen(vertex, &screen[i][j]))
                {
                    return;
                }
            }
        }

        float left = screen[0][3].X;
        float top = screen[0][3].Y;
        float right = screen[0][3].X;
        float bottom = screen[0][3].Y;

        for (auto i = 0; i < 2; ++i)
        {
            for (auto j = 0; j < 4; ++j)
            {
                if (left > screen[i][j].X)
                {
                    left = screen[i][j].X;
                }

                if (top < screen[i][j].Y)
                {
                    top = screen[i][j].Y;
                }

                if (right < screen[i][j].X)
                {
                    right = screen[i][j].X;
                }

                if (bottom > screen[i][j].Y)
                {
                    bottom = screen[i][j].Y;
                }
            }
        }

        FVector2D topLeftScreen(left, top);
        FVector2D bottomRightScreen(right, bottom);

        DrawRect(topLeftScreen, bottomRightScreen, colour);
    }

    void DrawBoundingBox(UWorld* world, AActor* actor, const ImU32 colour)
    {
        auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;

        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);
        FRotator rotation = actor->K2_GetActorRotation();
        origin = actor->K2_GetActorLocation();

        FVector vertices[2][4];
        vertices[0][0] = { -extent.X, -extent.Y, -extent.Z }; // Left Back Bottom
        vertices[0][1] = { extent.X, -extent.Y, -extent.Z }; // Right Back Bottom
        vertices[0][2] = { extent.X, extent.Y, -extent.Z }; // Right Front Bottom
        vertices[0][3] = { -extent.X, extent.Y, -extent.Z }; // Left Front Bottom

        vertices[1][0] = { -extent.X, -extent.Y, extent.Z }; // Left Back Top
        vertices[1][1] = { extent.X, -extent.Y, extent.Z }; // Right Back Top
        vertices[1][2] = { extent.X, extent.Y, extent.Z }; // Right Front Top
        vertices[1][3] = { -extent.X, extent.Y, extent.Z }; // Left Front Top

        FVector2D screen[2][4];
        const FTransform transform(rotation);

        for (auto i = 0; i < 2; i++)
        {
            for (auto j = 0; j < 4; j++)
            {
                auto& vertex = vertices[i][j];
                vertex = transform.TransformPosition(vertex) + origin;
                if (!playerController->ProjectWorldLocationToScreen(vertex, &screen[i][j]))
                {
                    return;
                }
            }
        }

        for (auto i = 0; i < 4; i++)
        {
            DrawLine(screen[0][i], screen[0][(i + 1) % 4], colour);
            DrawLine(screen[1][i], screen[1][(i + 1) % 4], colour);
            DrawLine(screen[0][i], screen[1][i], colour);
        }
    }

    void DrawPath(UWorld* world, std::vector<FVector> path, const ImU32 colour)
    {
        auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;

        for (auto& point : path)
        {
            FVector2D screen{};
            if (!playerController->ProjectWorldLocationToScreen(point, &screen))
            {
                break;
            }
            Window->DrawList->PathLineTo(ImVec2(screen.X, screen.Y));
        }
        Window->DrawList->PathStroke(colour);
    }
}
