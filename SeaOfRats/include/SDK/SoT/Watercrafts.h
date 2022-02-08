#pragma once

namespace SDK
{
    // Class Watercrafts.Watercraft
    // 0x0348 (0x0718 - 0x03D0)
    class AWatercraft : public AActor
    {
    public:
        char pad_0x03D0[0x0348];
    };

    // Class Watercrafts.Rowboat
    // 0x02F0 (0x0A08 - 0x0718)
    class ARowboat : public AWatercraft
    {
    public:
        char pad_0x0718[0x02F0];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Watercrafts.Rowboat");
            return ptr;
        }
    };
}
