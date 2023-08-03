#include "UE4.h"

namespace SDK
{
    const FVector FVector::ZeroVector(0.f);
    const FVector FVector::OneVector(1.f);
    const FVector FVector::UpVector(0.f, 0.f, 1.f);
    const FVector FVector::DownVector(0.f, 0.f, -1.f);
    const FVector FVector::ForwardVector(1.f, 0.f, 0.f);
    const FVector FVector::BackwardVector(-1.f, 0.f, 0.f);
    const FVector FVector::RightVector(0.f, 1.f, 0.f);
    const FVector FVector::LeftVector(0.f, -1.f, 0.f);

    const FVector2D FVector2D::ZeroVector(0.f, 0.f);
    const FVector2D FVector2D::UnitVector(1.f, 1.f);

    const FRotator FRotator::ZeroRotator(0.f, 0.f, 0.f);

    alignas(16) const FMatrix FMatrix::Identity(FPlane(1.f, 0.f, 0.f, 0.f), FPlane(0.f, 1.f, 0.f, 0.f), FPlane(0.f, 0.f, 1.f, 0.f), FPlane(0.f, 0.f, 0.f, 1.f));

    const FQuat FQuat::Identity(0.f, 0.f, 0.f, 1.f);

    FRotator FVector::Rotation() const
    {
        FRotator R;

        R.Yaw = FMath::Atan2(Y, X) * (180.f / PI);

        R.Pitch = FMath::Atan2(Z, std::sqrtf(X * X + Y * Y)) * (180.f / PI);

        R.Roll = 0.f;

        return R;
    }

    FVector FRotator::Vector() const
    {
        float CP, SP, CY, SY;

        FMath::SinCos(&SP, &CP, FMath::DegreesToRadians(Pitch));
        FMath::SinCos(&SY, &CY, FMath::DegreesToRadians(Yaw));
        FVector V = FVector(CP * CY, CP * SY, SP);

        return V;
    }

    FQuat FRotator::Quaternion() const
    {
        float SP, SY, SR;
        float CP, CY, CR;

        FMath::SinCos(&SP, &CP, Pitch * RADS_DIVIDED_BY_2);
        FMath::SinCos(&SY, &CY, Yaw * RADS_DIVIDED_BY_2);
        FMath::SinCos(&SR, &CR, Roll * RADS_DIVIDED_BY_2);

        FQuat RotationQuat;
        RotationQuat.X = CR * SP * SY - SR * CP * CY;
        RotationQuat.Y = -CR * SP * CY - SR * CP * SY;
        RotationQuat.Z = CR * CP * SY - SR * SP * CY;
        RotationQuat.W = CR * CP * CY + SR * SP * SY;

        return RotationQuat;
    }

    /*FRotator FMatrix::Rotator() const
    {
        const FVector XAxis = GetScaledAxis(EAxis::X);
        const FVector YAxis = GetScaledAxis(EAxis::Y);
        const FVector ZAxis = GetScaledAxis(EAxis::Z);

        FRotator Rotator = FRotator(
            FMath::Atan2(XAxis.Z, std::sqrtf(FMath::Square(XAxis.X) + FMath::Square(XAxis.Y))) * 180.f / PI,
            FMath::Atan2(XAxis.Y, XAxis.X) * 180.f / PI,
            0
        );

        const FVector SYAxis = FMatrix(Rotator).GetScaledAxis(EAxis::Y);
        Rotator.Roll = FMath::Atan2(ZAxis | SYAxis, YAxis | SYAxis) * 180.f / PI;

        return Rotator;
    }*/
}
