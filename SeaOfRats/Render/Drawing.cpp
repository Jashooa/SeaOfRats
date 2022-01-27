#include "Drawing.h"

#include <cmath>
#include <string>

#include "include/SDK/SDK.h"

using namespace SDK;

namespace Render
{
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
            //FVector2D newPosition(std::trunc(position.X), std::trunc(position.Y));
            hud->Canvas->K2_DrawText(RobotoFont, static_cast<FString>(string.c_str()), position, color, 1.0f, Colour::Black, FVector2D(0.0f, 0.0f), true, true, true, Colour::Black);
            //hud->DrawText(static_cast<FString>(string.c_str()), color, newPosition.X, newPosition.Y, RobotoFont, 1.0f, false);
        }

        void DrawInterfaceString(AHUD* hud, const std::wstring string, const FVector2D& position, const FLinearColor& color, bool centreX, bool centreY)
        {
            FVector2D newPosition(std::trunc(position.X), std::trunc(position.Y));
            hud->Canvas->K2_DrawText(RobotoFont, static_cast<FString>(string.c_str()), newPosition, color, 1.0f, Colour::Black, FVector2D(0.0f, 0.0f), centreX, centreY, true, Colour::Black);
        }

        /*void DrawCircle(AHUD* hud, const FVector2D& position, const FLinearColor& color, const float radius)
        {
        }*/

        void DrawRect(AHUD* hud, const FVector2D& minPosition, const FVector2D& maxPosition, const FLinearColor& color, const float thickness = 1.0f)
        {
            hud->Canvas->K2_DrawLine(minPosition, FVector2D(maxPosition.X, minPosition.Y), thickness, color);
            hud->Canvas->K2_DrawLine(minPosition, FVector2D(minPosition.X, maxPosition.Y), thickness, color);
            hud->Canvas->K2_DrawLine(FVector2D(minPosition.X, maxPosition.Y), maxPosition, thickness, color);
            hud->Canvas->K2_DrawLine(FVector2D(maxPosition.X, minPosition.Y), maxPosition, thickness, color);
        }

        void DrawHealthBar(AHUD* hud, const FVector2D& minPosition, const FVector2D& maxPosition, float currentHealth, float maxHealth)
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
            hud->DrawRect(Colour::Black, x - 1, y - 1, w + 2, h + 2);
            hud->DrawRect(Colour::Green, x, y, w * health, h);
        }

        void DrawBoundingRect(UGameViewportClient* client, AHUD* hud, AActor* actor, const FLinearColor& color)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;

            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);
            FRotator rotation = actor->K2_GetActorRotation();

            FVector topLeft;
            FVector bottomRight;
            topLeft = { -extent.X, 0.f, extent.Z };
            bottomRight = { extent.X, 0.f, -extent.Z };

            FVector2D topLeftScreen, bottomRightScreen;
            FTransform const transform(rotation);

            topLeft = transform.TransformPosition(topLeft) + origin;
            bottomRight = transform.TransformPosition(bottomRight) + origin;

            if (!playerController->ProjectWorldLocationToScreen(topLeft, &topLeftScreen) || !playerController->ProjectWorldLocationToScreen(bottomRight, &bottomRightScreen))
            {
                return;
            }

            DrawRect(hud, topLeftScreen, bottomRightScreen, color);
        }

        void DrawBoundingBox(UGameViewportClient* client, AHUD* hud, AActor* actor, const FLinearColor& color)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;

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
                hud->Canvas->K2_DrawLine(screen[0][i], screen[0][(i + 1) % 4], 1.f, color);
                hud->Canvas->K2_DrawLine(screen[1][i], screen[1][(i + 1) % 4], 1.f, color);
                hud->Canvas->K2_DrawLine(screen[0][i], screen[1][i], 1.f, color);
            }
        }
    }
}
