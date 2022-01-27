#pragma once

namespace SDK
{
    // ScriptStruct CoreUObject.Vector2D
    // 0x0008
    struct FVector2D
    {
        float X; // 0x0000(0x0004)
        float Y; // 0x0004(0x0004)

        inline FVector2D() : X(0.f), Y(0.f)
        {}

        inline FVector2D(float InX, float InY) : X(InX), Y(InY)
        {}

        inline FVector2D operator+(const FVector2D& V) const
        {
            return FVector2D(X + V.X, Y + V.Y);
        }

        inline FVector2D operator-(const FVector2D& V) const
        {
            return FVector2D(X - V.X, Y - V.Y);
        }

        inline FVector2D operator*(const FVector2D& V) const
        {
            return FVector2D(X * V.X, Y * V.Y);
        }

        inline FVector2D operator/(const FVector2D& V) const
        {
            return FVector2D(X / V.X, Y / V.Y);
        }
    };
}
