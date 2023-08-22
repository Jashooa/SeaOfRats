#pragma once

namespace SDK
{
    // ScriptStruct GameService.GameServiceCoordinatorUnit
    // 0x0018
    struct FGameServiceCoordinatorUnit
    {
        class UObject* Service; // 0x0000(0x0008)
        char pad_0x0008[0x0010];
    };

    // ScriptStruct GameService.GameServiceCoordinator
    // 0x0020
    struct FGameServiceCoordinator
    {
        TArray<struct FGameServiceCoordinatorUnit> Services; // 0x0000(0x0010)
        char pad_0x0010[0x0010];
    };

    // Class GameService.ServiceProviderGameState
    // 0x0120 (0x0540 - 0x0420)
    class AServiceProviderGameState : public AGameState
    {
    public:
        char pad_0x0420[0x0120];
    };
}
