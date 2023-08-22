#pragma once

#include "Math.h"

namespace SDK
{
    // ScriptStruct CoreUObject.Vector2D
    // 0x0008
    struct FVector2D
    {
        float X; // 0x0000(0x0004)
        float Y; // 0x0004(0x0004)

        static const FVector2D ZeroVector;
        static const FVector2D UnitVector;

        inline FVector2D() : X(0.f), Y(0.f)
        {
        }

        inline FVector2D(float InX, float InY) : X(InX), Y(InY)
        {
        }

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

        inline FVector2D operator+(float A) const
        {
            return FVector2D(X + A, Y + A);
        }

        inline FVector2D operator-(float A) const
        {
            return FVector2D(X - A, Y - A);
        }

        inline FVector2D operator*(float Scale) const
        {
            return FVector2D(X * Scale, Y * Scale);
        }

        inline FVector2D operator/(float Scale) const
        {
            const float RScale = 1.f / Scale;
            return FVector2D(X * RScale, Y * RScale);
        }

        inline float operator|(const FVector2D& V) const
        {
            return X * V.X + Y * V.Y;
        }

        inline bool operator==(const FVector2D& V) const
        {
            return X == V.X && Y == V.Y;
        }

        inline bool operator!=(const FVector2D& V) const
        {
            return X != V.X || Y != V.Y;
        }

        inline FVector2D GetRotated(const float AngleDeg) const
        {
            float S, C;
            FMath::SinCos(&S, &C, FMath::DegreesToRadians(AngleDeg));

            return FVector2D(
                C * X - S * Y,
                S * X + C * Y);
        }

        inline static float DotProduct(const FVector2D& A, const FVector2D& B)
        {
            return A | B;
        }

        inline static float DistSquared(const FVector2D& V1, const FVector2D& V2)
        {
            return FMath::Square(V2.X - V1.X) + FMath::Square(V2.Y - V1.Y);
        }


        inline static float Distance(const FVector2D& V1, const FVector2D& V2)
        {
            return sqrtf(FVector2D::DistSquared(V1, V2));
        }

        inline void Normalize(float Tolerance = SMALL_NUMBER)
        {
            const float SquareSum = X * X + Y * Y;
            if (SquareSum > Tolerance)
            {
                const float Scale = FMath::InvSqrt(SquareSum);
                X *= Scale;
                Y *= Scale;
                return;
            }
            X = 0.f;
            Y = 0.f;
        }

        inline FVector2D GetSafeNormal(float Tolerance = SMALL_NUMBER) const
        {
            const float SquareSum = X * X + Y * Y;
            if (SquareSum > Tolerance)
            {
                const float Scale = FMath::InvSqrt(SquareSum);
                return FVector2D(X * Scale, Y * Scale);
            }
            return FVector2D(0.f, 0.f);
        }

        inline bool IsZero() const
        {
            return X == 0.f && Y == 0.f;
        }
    };
}
