#pragma once

#include "Quat.h"

namespace SDK
{
    // ScriptStruct CoreUObject.Rotator
    // 0x000C
    struct FRotator
    {
        float Pitch; // 0x0000(0x0004)
        float Yaw; // 0x0004(0x0004)
        float Roll; // 0x0008(0x0004)

        static const FRotator ZeroRotator;

        inline FRotator() : Pitch(0.f), Yaw(0.f), Roll(0.f)
        {
        }

        inline FRotator(float InF) : Pitch(InF), Yaw(InF), Roll(InF)
        {
        }

        inline FRotator(float InPitch, float InYaw, float InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll)
        {
        }

        inline FRotator operator+(const FRotator& R) const
        {
            return FRotator(Pitch + R.Pitch, Yaw + R.Yaw, Roll + R.Roll);
        }

        inline FRotator operator-(const FRotator& R) const
        {
            return FRotator(Pitch - R.Pitch, Yaw - R.Yaw, Roll - R.Roll);
        }

        inline FRotator operator*(float Scale) const
        {
            return FRotator(Pitch * Scale, Yaw * Scale, Roll * Scale);
        }

        inline FRotator operator*=(float Scale)
        {
            Pitch = Pitch * Scale; Yaw = Yaw * Scale; Roll = Roll * Scale;
            return *this;
        }

        inline bool operator==(const FRotator& R) const
        {
            return Pitch == R.Pitch && Yaw == R.Yaw && Roll == R.Roll;
        }

        inline bool operator!=(const FRotator& V) const
        {
            return Pitch != V.Pitch || Yaw != V.Yaw || Roll != V.Roll;
        }

        inline FRotator operator+=(const FRotator& R)
        {
            Pitch += R.Pitch; Yaw += R.Yaw; Roll += R.Roll;
            return *this;
        }

        inline FRotator operator-=(const FRotator& R)
        {
            Pitch -= R.Pitch; Yaw -= R.Yaw; Roll -= R.Roll;
            return *this;
        }

        /*inline FRotator operator-() const
        {
            return FRotator(-Pitch, -Yaw, -Roll);
        }*/

        inline float ClampAxis(float Angle)
        {
            Angle = std::fmodf(Angle, 360.f);

            if (Angle < 0.f)
            {
                Angle += 360.f;
            }

            return Angle;
        }

        inline FRotator Clamp()
        {
            return FRotator(ClampAxis(Pitch), ClampAxis(Yaw), ClampAxis(Roll));
        }

        inline float NormalizeAxis(float Angle)
        {
            Angle = ClampAxis(Angle);

            if (Angle > 180.f)
            {
                Angle -= 360.f;
            }

            return Angle;
        }

        inline void Normalize()
        {
            Pitch = NormalizeAxis(Pitch);
            Yaw = NormalizeAxis(Yaw);
            Roll = NormalizeAxis(Roll);
        }

        inline FRotator GetNormalized() const
        {
            FRotator Rot = *this;
            Rot.Normalize();
            return Rot;
        }

        struct FVector Vector() const;
        struct FQuat Quaternion() const;
    };
}
