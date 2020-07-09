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

    void DrawInterfaceString(AHUD* hud, const std::wstring string, const FVector2D& position, const FLinearColor& color, bool centreX, bool centreY)
    {
        FVector2D newPosition(std::trunc(position.X), std::trunc(position.Y));
        hud->Canvas->K2_DrawText(RobotoFont, static_cast<FString>(string.c_str()), newPosition, color, 1.0f, Colour::Black, FVector2D(0.0f, 0.0f), centreX, centreY, true, Colour::Black);
    }

    void DrawRect(AHUD* hud, const FVector2D& minPosition, const FVector2D& maxPosition, const FLinearColor& color, const float thickness = 1.0f)
    {
        hud->Canvas->K2_DrawLine(minPosition, FVector2D(maxPosition.X, minPosition.Y), thickness, color);
        hud->Canvas->K2_DrawLine(minPosition, FVector2D(minPosition.X, maxPosition.Y), thickness, color);
        hud->Canvas->K2_DrawLine(FVector2D(minPosition.X, maxPosition.Y), maxPosition, thickness, color);
        hud->Canvas->K2_DrawLine(FVector2D(maxPosition.X, minPosition.Y), maxPosition, thickness, color);
    }

    FVector RotateCorner(FVector origin, FVector corner, float theta)
    {
        float x = corner.X - origin.X;
        float y = corner.Y - origin.Y;

        return {
            origin.X + (x * UKismetMathLibrary::Cos(theta) - y * UKismetMathLibrary::Sin(theta)),
            origin.Y + (x * UKismetMathLibrary::Sin(theta) + y * UKismetMathLibrary::Cos(theta)),
            corner.Z
        };
    }

    void DrawBoundingBox(UGameViewportClient* client, AHUD* hud, AActor* actor, const FLinearColor& color)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;

        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);

        FRotator rotation = actor->K2_GetActorRotation();
        float yaw = UKismetMathLibrary::DegreesToRadians(std::fmodf(rotation.Yaw + 450.0f, 360.0f));

        FVector t1 = origin, t2 = origin, t3 = origin, t4 = origin, b1 = origin, b2 = origin, b3 = origin, b4 = origin;
        t1.X -= extent.X;
        t1.Y -= extent.Y;
        t1.Z -= extent.Z;
        t2.X += extent.X;
        t2.Y -= extent.Y;
        t2.Z -= extent.Z;
        t3.X += extent.X;
        t3.Y += extent.Y;
        t3.Z -= extent.Z;
        t4.X -= extent.X;
        t4.Y += extent.Y;
        t4.Z -= extent.Z;

        t1 = RotateCorner(origin, t1, yaw);
        t2 = RotateCorner(origin, t2, yaw);
        t3 = RotateCorner(origin, t3, yaw);
        t4 = RotateCorner(origin, t4, yaw);

        FVector2D ts1, ts2, ts3, ts4;
        if (!playerController->ProjectWorldLocationToScreen(t1, &ts1)
            || !playerController->ProjectWorldLocationToScreen(t2, &ts2)
            || !playerController->ProjectWorldLocationToScreen(t3, &ts3)
            || !playerController->ProjectWorldLocationToScreen(t4, &ts4))
        {
            return;
        }

        b1.X -= extent.X;
        b1.Y -= extent.Y;
        b1.Z += extent.Z;
        b2.X += extent.X;
        b2.Y -= extent.Y;
        b2.Z += extent.Z;
        b3.X += extent.X;
        b3.Y += extent.Y;
        b3.Z += extent.Z;
        b4.X -= extent.X;
        b4.Y += extent.Y;
        b4.Z += extent.Z;

        b1 = RotateCorner(origin, b1, yaw);
        b2 = RotateCorner(origin, b2, yaw);
        b3 = RotateCorner(origin, b3, yaw);
        b4 = RotateCorner(origin, b4, yaw);

        FVector2D bs1, bs2, bs3, bs4;
        if (!playerController->ProjectWorldLocationToScreen(b1, &bs1)
            || !playerController->ProjectWorldLocationToScreen(b2, &bs2)
            || !playerController->ProjectWorldLocationToScreen(b3, &bs3)
            || !playerController->ProjectWorldLocationToScreen(b4, &bs4))
        {
            return;
        }

        hud->Canvas->K2_DrawLine(ts1, ts2, 1.f, color);
        hud->Canvas->K2_DrawLine(ts2, ts3, 1.f, color);
        hud->Canvas->K2_DrawLine(ts3, ts4, 1.f, color);
        hud->Canvas->K2_DrawLine(ts4, ts1, 1.f, color);
        hud->Canvas->K2_DrawLine(bs1, bs2, 1.f, color);
        hud->Canvas->K2_DrawLine(bs2, bs3, 1.f, color);
        hud->Canvas->K2_DrawLine(bs3, bs4, 1.f, color);
        hud->Canvas->K2_DrawLine(bs4, bs1, 1.f, color);
        hud->Canvas->K2_DrawLine(ts1, bs1, 1.f, color);
        hud->Canvas->K2_DrawLine(ts2, bs2, 1.f, color);
        hud->Canvas->K2_DrawLine(ts3, bs3, 1.f, color);
        hud->Canvas->K2_DrawLine(ts4, bs4, 1.f, color);
    }
}