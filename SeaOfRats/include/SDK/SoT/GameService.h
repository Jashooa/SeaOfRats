#pragma once

#ifdef _MSC_VER
    #pragma pack(push, 0x8)
#endif

namespace SDK
{
    // Class GameService.ServiceProviderGameState
    // 0x0120 (0x0548 - 0x0428)
    class AServiceProviderGameState : public AGameState
    {
    public:
        char pad_0x0428[0x0120];
    };
}

#ifdef _MSC_VER
    #pragma pack(pop)
#endif
