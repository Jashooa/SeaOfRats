#pragma once

namespace SDK
{
    // Class Kraken.KrakenTentacle
    // 0x0148 (0x0510 - 0x03C8)
    class AKrakenTentacle : public AActor
    {
    public:
        char pad_0x03C8[0x0020];
        class UHealthComponent* HealthComponent; // 0x03E8(0x0008)
        char pad_0x03F0[0x0120];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Kraken.KrakenTentacle");
            return ptr;
        }
    };

    // Class Kraken.Kraken
    // 0x0578 (0x0940 - 0x03C8)
    class AKraken : public AActor
    {
    public:
        char pad_0x03C8[0x0448];
        int NumTentaclesRemaining; // 0x0810(0x0004)
        char pad_0x0814[0x012C];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Kraken.Kraken");
            return ptr;
        }
    };

    // Class Kraken.KrakenService
    // 0x01F8 (0x05C0 - 0x03C8)
    class AKrakenService : public AActor
    {
    public:
        char pad_0x03C8[0x00E8];
        class AKraken* Kraken; // 0x04B0(0x0008)
        char pad_0x04B8[0x0108];
    };
}
