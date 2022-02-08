#pragma once

namespace SDK
{
    // Class Maths.VectorMaths
    // 0x0000 (0x0028 - 0x0028)
    class UVectorMaths : public UBlueprintFunctionLibrary
    {
    public:
        static float Distance(const FVector& A, const FVector& B);
    };
}
