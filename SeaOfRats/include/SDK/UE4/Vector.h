#pragma once

#include <cmath>

namespace SDK
{
    // ScriptStruct CoreUObject.Vector
    // 0x000C
    struct FVector
    {
        float X; // 0x0000(0x0004)
        float Y; // 0x0004(0x0004)
        float Z; // 0x0008(0x0004)

        static const FVector ZeroVector;
        static const FVector OneVector;
        static const FVector UpVector;
        static const FVector DownVector;
        static const FVector ForwardVector;
        static const FVector BackwardVector;
        static const FVector RightVector;
        static const FVector LeftVector;

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
            return std::sqrtf(X * X + Y * Y + Z * Z);
        }

        inline float SizeSquared() const
        {
            return X * X + Y * Y + Z * Z;
        }

        inline float Sum() const
        {
            return X + Y + Z;
        }

        inline bool Normalize(float Tolerance = SMALL_NUMBER)
        {
            const float SquareSum = X * X + Y * Y + Z * Z;

            if (SquareSum > Tolerance)
            {
                const float Scale = FMath::InvSqrt(SquareSum);
                X *= Scale; Y *= Scale; Z *= Scale;
                return true;
            }

            return false;
        }

        inline FVector GetSafeNormal(float Tolerance = SMALL_NUMBER) const
        {
            const float SquareSum = X * X + Y * Y + Z * Z;

            if (SquareSum == 1.f)
            {
                return *this;
            }
            else if (SquareSum < Tolerance)
            {
                return FVector::ZeroVector;
            }

            const float Scale = FMath::InvSqrt(SquareSum);
            return FVector(X * Scale, Y * Scale, Z * Scale);
        }

        inline FVector GetSafeNormal2D(float Tolerance = SMALL_NUMBER) const
        {
            const float SquareSum = X * X + Y * Y;

            if (SquareSum == 1.f)
            {
                if (Z == 0.f)
                {
                    return *this;
                }
                else
                {
                    return FVector(X, Y, 0.f);
                }
            }
            else if (SquareSum < Tolerance)
            {
                return FVector::ZeroVector;
            }

            const float Scale = FMath::InvSqrt(SquareSum);
            return FVector(X * Scale, Y * Scale, 0.f);
        }

        inline FVector GetUnsafeNormal() const
        {
            const float Scale = FMath::InvSqrt(X * X + Y * Y + Z * Z);
            return FVector(X * Scale, Y * Scale, Z * Scale);
        }

        inline FVector GetUnsafeNormal2D() const
        {
            const float Scale = FMath::InvSqrt(X * X + Y * Y);
            return FVector(X * Scale, Y * Scale, 0.f);
        }

        static inline float DistSquared(const FVector& V1, const FVector& V2)
        {
            return FMath::Square(V2.X - V1.X) + FMath::Square(V2.Y - V1.Y) + FMath::Square(V2.Z - V1.Z);
        }

        static inline float Dist(const FVector& V1, const FVector& V2)
        {
            return std::sqrtf(FVector::DistSquared(V1, V2));
        }

        struct FRotator Rotation() const;
    };
}
