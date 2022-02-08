#pragma once

#include <math.h>

namespace SDK
{
    // ScriptStruct CoreUObject.Vector
    // 0x000C
    struct FVector
    {
        float X; // 0x0000(0x0004)
        float Y; // 0x0004(0x0004)
        float Z; // 0x0008(0x0004)

        inline FVector() : X(0.f), Y(0.f), Z(0.f)
        {
        }

        inline FVector(float InF) : X(InF), Y(InF), Z(InF)
        {
        }

        inline FVector(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ)
        {
        }

        inline FVector& operator=(const FVector& Other)
        {
            this->X = Other.X;
            this->Y = Other.Y;
            this->Z = Other.Z;
            return *this;
        }

        inline FVector operator^(const FVector& V) const
        {
            return FVector
            (
                Y * V.Z - Z * V.Y,
                Z * V.X - X * V.Z,
                X * V.Y - Y * V.X
            );
        }

        inline float operator|(const FVector& V) const
        {
            return X * V.X + Y * V.Y + Z * V.Z;
        }

        inline FVector operator+(const FVector& V) const
        {
            return FVector(X + V.X, Y + V.Y, Z + V.Z);
        }

        inline FVector operator-(const FVector& V) const
        {
            return FVector(X - V.X, Y - V.Y, Z - V.Z);
        }

        inline FVector operator-(float Bias) const
        {
            return FVector(X - Bias, Y - Bias, Z - Bias);
        }

        inline FVector operator+(float Bias) const
        {
            return FVector(X + Bias, Y + Bias, Z + Bias);
        }

        inline FVector operator*(float Scale) const
        {
            return FVector(X * Scale, Y * Scale, Z * Scale);
        }

        inline FVector operator/(float Scale) const
        {
            const float RScale = 1.f / Scale;
            return FVector(X * RScale, Y * RScale, Z * RScale);
        }

        inline FVector operator*(const FVector& V) const
        {
            return FVector(X * V.X, Y * V.Y, Z * V.Z);
        }

        inline FVector operator/(const FVector& V) const
        {
            return FVector(X / V.X, Y / V.Y, Z / V.Z);
        }

        inline bool operator==(const FVector& V) const
        {
            return X == V.X && Y == V.Y && Z == V.Z;
        }

        inline bool operator!=(const FVector& V) const
        {
            return X != V.X || Y != V.Y || Z != V.Z;
        }

        inline FVector operator-() const
        {
            return FVector(-X, -Y, -Z);
        }

        inline FVector& operator+=(const FVector& V)
        {
            X += V.X; Y += V.Y; Z += V.Z;
            return *this;
        }

        inline FVector& operator-=(const FVector& V)
        {
            X -= V.X; Y -= V.Y; Z -= V.Z;
            return *this;
        }

        inline FVector operator*=(float Scale)
        {
            X *= Scale; Y *= Scale; Z *= Scale;
            return *this;
        }

        inline FVector& operator/=(const float V)
        {
            const float RV = 1.f / V;
            X *= RV; Y *= RV; Z *= RV;
            return *this;
        }

        inline FVector& operator*=(const FVector& V)
        {
            X *= V.X; Y *= V.Y; Z *= V.Z;
            return *this;
        }

        inline FVector operator/=(const FVector& V)
        {
            X /= V.X; Y /= V.Y; Z /= V.Z;
            return *this;
        }

        inline float Size() const
        {
            //return FMath::Sqrt(X * X + Y * Y + Z * Z);
            return sqrtf(X * X + Y * Y + Z * Z);
        }

        inline float SizeSquared() const
        {
            return X * X + Y * Y + Z * Z;
        }

        static const FVector ZeroVector;
    };
}
