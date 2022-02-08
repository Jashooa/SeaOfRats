#include "SDK/SDK.h"

namespace SDK
{
    // Function Maths.VectorMaths.Distance
    float UVectorMaths::Distance(const struct FVector& A, const struct FVector& B)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Maths.VectorMaths.Distance");

        struct
        {
            struct FVector A;
            struct FVector B;
            float ReturnValue;
        } params{};
        params.A = A;
        params.B = B;

        static auto defaultObj = UObject::FindObject<UClass>("Class Maths.VectorMaths");
        UObject::ProcessEvent(defaultObj, fn, &params);

        return params.ReturnValue;
    }
}
