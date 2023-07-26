#pragma once

namespace SDK
{
    // Class Watercrafts.Watercraft
    // 0x0368 (0x0730 - 0x03C8)
    class AWatercraft : public AActor
    {
    public:
        char pad_0x03C8[0x0368];
    };

    // Class Watercrafts.Rowboat
    // 0x0350 (0x0A80 - 0x0730)
    class ARowboat : public AWatercraft
    {
    public:
        char pad_0x0730[0x0350];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Watercrafts.Rowboat");
            return ptr;
        }
    };
}
