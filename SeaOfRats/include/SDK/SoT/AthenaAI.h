#pragma once

#ifdef _MSC_VER
    #pragma pack(push, 0x8)
#endif

#include "Athena.h"

namespace SDK
{
    // Class AthenaAI.AICreatureCharacter
    // 0x0220 (0x0800 - 0x05E0)
    class AAICreatureCharacter : public ACharacter
    {
    public:
        char pad_0x05E0[0x0220];
    };

    // Class AthenaAI.Fauna
    // 0x03B0 (0x0BB0 - 0x0800)
    class AFauna : public AAICreatureCharacter
    {
    public:
        char pad_0x0800[0x0008];
        struct FText DisplayName; // 0x0808(0x0038)
        char pad_0x0840[0x0370];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class AthenaAI.Fauna");
            return ptr;
        }
    };
}

#ifdef _MSC_VER
    #pragma pack(pop)
#endif
