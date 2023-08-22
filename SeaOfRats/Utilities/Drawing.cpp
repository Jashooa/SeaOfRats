#include "Drawing.h"

#include <Windows.h>

#include <string>

using namespace SDK;

namespace Utilities
{
    namespace Drawing
    {
        FVector2D GetScreenCentre()
        {
            const auto centreX = std::trunc(Window->Size.x * 0.5f);
            const auto centreY = std::trunc(Window->Size.y * 0.5f);

            return FVector2D{ centreX, centreY };
        }

        void DrawLine(const FVector2D& start, const FVector2D& end, ImU32 colour, float thickness)
        {
            Window->DrawList->AddLine({ start.X, start.Y }, { end.X, end.Y }, colour, thickness);
        }

        void DrawString(const std::string& string, const FVector2D& position, ImU32 colour, bool centreX, bool centreY)
        {
            auto newPosition = ImVec2{ position.X, position.Y };
            if (centreX || centreY)
            {
                const auto textSize = ImGui::CalcTextSize(string.c_str());
                if (centreX)
                {
                    newPosition.x -= textSize.x * 0.5f;
                }

                if (centreY)
                {
                    newPosition.y -= textSize.y * 0.5f;
                }
            }

            Window->DrawList->AddText({ newPosition.x + 1.f, newPosition.y + 1.f }, Colour::Black, string.c_str());
            Window->DrawList->AddText(newPosition, colour, string.c_str());
        }

        void DrawCircle(const FVector2D& position, float radius, ImU32 colour, float thickness)
        {
            Window->DrawList->AddCircle({ position.X, position.Y }, radius, colour, 0, thickness);
        }

        void DrawCircleFilled(const FVector2D& position, float radius, ImU32 colour)
        {
            Window->DrawList->AddCircleFilled({ position.X, position.Y }, radius, colour, 0);
        }

        void DrawRect(const FVector2D& minPosition, const FVector2D& maxPosition, ImU32 colour, float thickness)
        {
            Window->DrawList->AddRect({ minPosition.X, minPosition.Y }, { maxPosition.X, maxPosition.Y }, colour, 0.f, 0, thickness);
        }

        void DrawRectFilled(const FVector2D& minPosition, const FVector2D& maxPosition, ImU32 colour)
        {
            Window->DrawList->AddRectFilled({ minPosition.X, minPosition.Y }, { maxPosition.X, maxPosition.Y }, colour, 0.f, 0);
        }

        void DrawHealthBar(const FVector2D& position, float currentHealth, float maxHealth)
        {
            if (currentHealth > maxHealth)
            {
                currentHealth = maxHealth;
            }
            const auto text = std::to_string(static_cast<int>(currentHealth)) + "/" + std::to_string(static_cast<int>(maxHealth));
            const auto textSize = ImGui::CalcTextSize(text.c_str());
            const auto health = currentHealth / maxHealth;
            const auto x = position.X - 50.f;
            const auto y = std::trunc(position.Y - (textSize.y * 0.5f) + 2.f);
            const auto w = 100.f;
            const auto h = textSize.y - 2.f;

            Window->DrawList->AddRectFilled({ x - 1.f, y - 1.f }, { x + w + 1.f, y + h + 1.f }, Colour::Black);
            Window->DrawList->AddRectFilled({ x, y }, { x + w, y + h }, Colour::Red);
            Window->DrawList->AddRectFilled({ x, y }, { x + w * health, y + h }, Colour::Green);
            DrawString(text, position, Colour::White);
        }

        void DrawBoundingRect(UWorld* world, AActor* actor, ImU32 colour)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;

            /*auto origin = FVector{};
            auto extent = FVector{};
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

            auto origin = FVector{};
            auto extent = FVector{};
            actor->GetActorBounds(true, &origin, &extent);
            const auto rotation = actor->K2_GetActorRotation();
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
            const auto transform = FTransform{ rotation };

            for (int i = 0; i < 2; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    auto& vertex = vertices[i][j];
                    vertex = transform.TransformPosition(vertex) + origin;
                    if (!playerController->ProjectWorldLocationToScreen(vertex, &screen[i][j]))
                    {
                        return;
                    }
                }
            }

            auto left = screen[0][3].X;
            auto top = screen[0][3].Y;
            auto right = screen[0][3].X;
            auto bottom = screen[0][3].Y;

            for (int i = 0; i < 2; ++i)
            {
                for (int j = 0; j < 4; ++j)
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

            const auto topLeftScreen = FVector2D{ left, top };
            const auto bottomRightScreen = FVector2D{ right, bottom };

            DrawRect(topLeftScreen, bottomRightScreen, colour);
        }

        void DrawBoundingBox(UWorld* world, AActor* actor, ImU32 colour)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;

            auto origin = FVector{};
            auto extent = FVector{};
            actor->GetActorBounds(true, &origin, &extent);
            const auto rotation = actor->K2_GetActorRotation();
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
            const auto transform = FTransform{ rotation };

            for (int i = 0; i < 2; ++i)
            {
                for (int j = 0; j < 4; ++j)
                {
                    auto& vertex = vertices[i][j];
                    vertex = transform.TransformPosition(vertex) + origin;
                    if (!playerController->ProjectWorldLocationToScreen(vertex, &screen[i][j]))
                    {
                        return;
                    }
                }
            }

            for (int i = 0; i < 4; ++i)
            {
                DrawLine(screen[0][i], screen[0][(i + 1) % 4], colour);
                DrawLine(screen[1][i], screen[1][(i + 1) % 4], colour);
                DrawLine(screen[0][i], screen[1][i], colour);
            }
        }

        void DrawPath(UWorld* world, const std::vector<FVector>& path, ImU32 colour)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;

            for (const auto& point : path)
            {
                auto screen = FVector2D{};
                if (!playerController->ProjectWorldLocationToScreen(point, &screen))
                {
                    break;
                }
                Window->DrawList->PathLineTo({ screen.X, screen.Y });
            }
            Window->DrawList->PathStroke(colour);
        }
    }

}
