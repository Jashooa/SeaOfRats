#include "SDK/SDK.h"

namespace SDK
{
    UAthenaGameViewportClient* UAthenaGameViewportClient::GAthenaGameViewportClient = nullptr;

    // Function Athena.AthenaCharacter.GetCurrentShip
    class AActor* AAthenaCharacter::GetCurrentShip()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaCharacter.GetCurrentShip");

        struct
        {
            class AActor* ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.AthenaCharacter.IsDead
    bool AAthenaCharacter::IsDead()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaCharacter.IsDead");

        struct
        {
            bool ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.AthenaCharacter.IsInWater
    bool AAthenaCharacter::IsInWater()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaCharacter.IsInWater");

        struct
        {
            bool ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.AthenaPlayerState.GetHumanReadableName
    class FString AAthenaPlayerState::GetHumanReadableName()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaPlayerState.GetHumanReadableName");

        struct
        {
            class FString ReturnValue;
        } params;

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.AthenaPlayerState.GetPlayerActivity
    TEnumAsByte<EPlayerActivityType> AAthenaPlayerState::GetPlayerActivity()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaPlayerState.GetPlayerActivity");

        struct
        {
            TEnumAsByte<EPlayerActivityType> ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.OnlineAthenaPlayerController.IsClientAndInActiveGameplay
    bool AOnlineAthenaPlayerController::IsClientAndInActiveGameplay()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.OnlineAthenaPlayerController.IsClientAndInActiveGameplay");

        struct
        {
            bool ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.OnlineAthenaPlayerController.ModifyActiveState
    void AOnlineAthenaPlayerController::ModifyActiveState(bool IsActive)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.OnlineAthenaPlayerController.ModifyActiveState");

        struct
        {
            bool IsActive;
        } params{};
        params.IsActive = IsActive;

        UObject::ProcessEvent(this, fn, &params);
    }

    // Function Athena.Ship.GetInternalWater
    class AShipInternalWater* AShip::GetInternalWater()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.Ship.GetInternalWater");

        struct
        {
            class AShipInternalWater* ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.ShipService.GetNumShips
    int AShipService::GetNumShips()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.ShipService.GetNumShips");

        struct
        {
            int ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.CrewFunctions.AreCharactersInSameCrew
    bool UCrewFunctions::AreCharactersInSameCrew(class AAthenaCharacter* Player1, class AAthenaCharacter* Player2)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.CrewFunctions.AreCharactersInSameCrew");

        struct
        {
            class AAthenaCharacter* Player1;
            class AAthenaCharacter* Player2;
            bool ReturnValue;
        } params{};
        params.Player1 = Player1;
        params.Player2 = Player2;

        static auto defaultObj = UObject::FindObject<UClass>("Class Athena.CrewFunctions");
        UObject::ProcessEvent(defaultObj, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.CrewFunctions.GetCrewIdFromActor
    struct FGuid UCrewFunctions::GetCrewIdFromActor(class UObject* WorldContext, class AActor* Actor)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.CrewFunctions.GetCrewIdFromActor");

        struct
        {
            class UObject* WorldContext;
            class AActor* Actor;
            struct FGuid ReturnValue;
        } params{};
        params.WorldContext = WorldContext;
        params.Actor = Actor;

        static auto defaultObj = UObject::FindObject<UClass>("Class Athena.CrewFunctions");
        UObject::ProcessEvent(defaultObj, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.CrewFunctions.IsActorMemberOfCharactersCrew
    bool UCrewFunctions::IsActorMemberOfCharactersCrew(class AActor* Actor, class AAthenaCharacter* Player)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.CrewFunctions.IsActorMemberOfCharactersCrew");

        struct
        {
            class AActor* Actor;
            class AAthenaCharacter* Player;
            bool ReturnValue;
        } params{};
        params.Actor = Actor;
        params.Player = Player;

        static auto defaultObj = UObject::FindObject<UClass>("Class Athena.CrewFunctions");
        UObject::ProcessEvent(defaultObj, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.HealthComponent.GetCurrentHealth
    float UHealthComponent::GetCurrentHealth()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.HealthComponent.GetCurrentHealth");

        struct
        {
            float ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.HealthComponent.GetMaxHealth
    float UHealthComponent::GetMaxHealth()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.HealthComponent.GetMaxHealth");

        struct
        {
            float ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.Mermaid.GetCrewIdsResponsibleForSavingAsCopy
    TArray<struct FGuid> AMermaid::GetCrewIdsResponsibleForSavingAsCopy()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.Mermaid.GetCrewIdsResponsibleForSavingAsCopy");

        struct
        {
            TArray<struct FGuid> ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.WieldableInterface.GetActor
    class AActor* UWieldableInterface::GetActor()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.WieldableInterface.GetActor");

        struct
        {
            class AActor* ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.ActorFunctionLibrary.FindActorByName
    class AActor* UActorFunctionLibrary::FindActorByName(class UObject* WorldContext, const class FString& ActorName)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.ActorFunctionLibrary.FindActorByName");

        struct
        {
            class UObject* WorldContext;
            class FString ActorName;
            class AActor* ReturnValue;
        } params{};
        params.WorldContext = WorldContext;
        params.ActorName = ActorName;

        static auto defaultObj = UObject::FindObject<UClass>("Class Athena.ActorFunctionLibrary");
        UObject::ProcessEvent(defaultObj, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.DrowningComponent.GetOxygenLevel
    float UDrowningComponent::GetOxygenLevel()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.DrowningComponent.GetOxygenLevel");

        struct
        {
            float ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.AggressiveGhostShip.GetNumShotsLeftToKill
    int AAggressiveGhostShip::GetNumShotsLeftToKill()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AggressiveGhostShip.GetNumShotsLeftToKill");

        struct
        {
            int ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Athena.AggressiveGhostShip.GetShipType
    TEnumAsByte<EAggressiveGhostShipType> AAggressiveGhostShip::GetShipType()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AggressiveGhostShip.GetShipType");

        struct
        {
            TEnumAsByte<EAggressiveGhostShipType> ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }
}
