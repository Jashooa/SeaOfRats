#pragma once

#ifdef _MSC_VER
    #pragma pack(push, 0x8)
#endif

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

#ifdef _MSC_VER
    #pragma pack(pop)
#endif
