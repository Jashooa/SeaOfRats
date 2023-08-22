#pragma once

#include <cmath>

namespace SDK
{
    constexpr auto PI = 3.1415926535897932f;
    constexpr auto INV_PI = 0.31830988618f;
    constexpr auto HALF_PI = 1.57079632679f;
    constexpr auto DEG_TO_RAD = PI / 180.f;
    constexpr auto RADS_DIVIDED_BY_2 = DEG_TO_RAD / 2.f;
    constexpr auto SMALL_NUMBER = 1.e-8f;
    constexpr auto KINDA_SMALL_NUMBER = 1.e-4f;

    struct FMath
    {
        template<class T>
        static const inline T Abs(const T A)
        {
            return (A >= (T)0) ? A : -A;
        }

        static inline float InvSqrt(float F)
        {
            return 1.0f / std::sqrt(F);
        }

        template<class T>
        static inline T Square(const T A)
        {
            return A * A;
        }

        template <class T>
        static inline T Clamp(const T X, const T Min, const T Max)
        {
            return X < Min ? Min : X < Max ? X : Max;
        }

        static inline void SinCos(float* ScalarSin, float* ScalarCos, float Value)
        {
            // Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
            float quotient = (INV_PI * 0.5f) * Value;
            if (Value >= 0.0f)
            {
                quotient = (float) ((int) (quotient + 0.5f));
            }
            else
            {
                quotient = (float) ((int) (quotient - 0.5f));
            }
            float y = Value - (2.0f * PI) * quotient;

            // Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
            float sign;
            if (y > HALF_PI)
            {
                y = PI - y;
                sign = -1.0f;
            }
            else if (y < -HALF_PI)
            {
                y = -PI - y;
                sign = -1.0f;
            }
            else
            {
                sign = +1.0f;
            }

            float y2 = y * y;

            // 11-degree minimax approximation
            *ScalarSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

            // 10-degree minimax approximation
            float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
            *ScalarCos = sign * p;
        }

        template<class T>
        static inline auto RadiansToDegrees(T const& RadVal) -> decltype(RadVal* (180.f / PI))
        {
            return RadVal * (180.f / PI);
        }

        template<class T>
        static inline auto DegreesToRadians(T const& DegVal) -> decltype(DegVal* (PI / 180.f))
        {
            return DegVal * (PI / 180.f);
        }

        static inline float Atan2(float Y, float X)
        {
            //return atan2f(Y,X);
            // atan2f occasionally returns NaN with perfectly valid input (possibly due to a compiler or library bug).
            // We are replacing it with a minimax approximation with a max relative error of 7.15255737e-007 compared to the C library function.
            // On PC this has been measured to be 2x faster than the std C version.

            const float absX = FMath::Abs(X);
            const float absY = FMath::Abs(Y);
            const bool yAbsBigger = (absY > absX);
            float t0 = yAbsBigger ? absY : absX; // Max(absY, absX)
            float t1 = yAbsBigger ? absX : absY; // Min(absX, absY)

            if (t0 == 0.f)
                return 0.f;

            float t3 = t1 / t0;
            float t4 = t3 * t3;

            static const float c[7] = {
                +7.2128853633444123e-03f,
                -3.5059680836411644e-02f,
                +8.1675882859940430e-02f,
                -1.3374657325451267e-01f,
                +1.9856563505717162e-01f,
                -3.3324998579202170e-01f,
                +1.0f
            };

            t0 = c[0];
            t0 = t0 * t4 + c[1];
            t0 = t0 * t4 + c[2];
            t0 = t0 * t4 + c[3];
            t0 = t0 * t4 + c[4];
            t0 = t0 * t4 + c[5];
            t0 = t0 * t4 + c[6];
            t3 = t0 * t3;

            t3 = yAbsBigger ? (0.5f * PI) - t3 : t3;
            t3 = (X < 0.0f) ? PI - t3 : t3;
            t3 = (Y < 0.0f) ? -t3 : t3;

            return t3;
        }
    };
}
