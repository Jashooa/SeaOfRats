#pragma once

namespace SDK
{
    // Class Kraken.KrakenTentacle
    // 0x0138 (0x0508 - 0x03D0)
    class AKrakenTentacle : public AActor
    {
    public:
        char pad_0x03D0[0x0020];
        class UHealthComponent* HealthComponent; // 0x03F0(0x0008)
        char pad_0x03F8[0x0110];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Kraken.KrakenTentacle");
            return ptr;
        }
    };

    // Class Kraken.Kraken
    // 0x0560 (0x0930 - 0x03D0)
    class AKraken : public AActor
    {
    public:
        char pad_0x03D0[0x0430];
        int NumTentaclesRemaining; // 0x0800(0x0004)
        char pad_0x0804[0x012C];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Kraken.Kraken");
            return ptr;
        }
    };

    // Class Kraken.KrakenService
    // 0x0220 (0x05F0 - 0x03D0)
    class AKrakenService : public AActor
    {
    public:
        char pad_0x03D0[0x0148];
        class AKraken* Kraken; // 0x0518(0x0008)
        char pad_0x0520[0x00D0];
    };
}
