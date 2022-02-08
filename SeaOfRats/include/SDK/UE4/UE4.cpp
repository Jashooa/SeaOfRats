#include "UE4.h"

namespace SDK
{
    const FVector FVector::ZeroVector(0.0f, 0.0f, 0.0f);
    const FQuat FQuat::Identity(0, 0, 0, 1);

    FQuat FRotator::Quaternion() const
    {
        float SP, SY, SR;
        float CP, CY, CR;

        FMath::SinCos(&SP, &CP, Pitch * DIVIDE_BY_2);
        FMath::SinCos(&SY, &CY, Yaw * DIVIDE_BY_2);
        FMath::SinCos(&SR, &CR, Roll * DIVIDE_BY_2);

        FQuat RotationQuat;
        RotationQuat.X = CR * SP * SY - SR * CP * CY;
        RotationQuat.Y = -CR * SP * CY - SR * CP * SY;
        RotationQuat.Z = CR * CP * SY - SR * SP * CY;
        RotationQuat.W = CR * CP * CY + SR * SP * SY;

        return RotationQuat;
    }
}
