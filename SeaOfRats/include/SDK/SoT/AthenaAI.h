#pragma once

#include "Athena.h"

namespace SDK
{
    // Class AthenaAI.AICreatureCharacter
    // 0x0230 (0x0810 - 0x05E0)
    class AAICreatureCharacter : public ACharacter
    {
    public:
        char pad_0x05E0[0x0230];
    };

    // Class AthenaAI.Fauna
    // 0x03D0 (0x0BE0 - 0x0810)
    class AFauna : public AAICreatureCharacter
    {
    public:
        char pad_0x0810[0x0008];
        struct FText DisplayName; // 0x0818(0x0038)
        char pad_0x0850[0x0390];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class AthenaAI.Fauna");
            return ptr;
        }
    };
}
