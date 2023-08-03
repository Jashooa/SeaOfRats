#include "SDK/SDK.h"

namespace SDK
{
    UAthenaGameViewportClient* UAthenaGameViewportClient::GAthenaGameViewportClient = nullptr;

    // Function Athena.Mast.IsMastFullyDamaged
    bool AMast::IsMastFullyDamaged()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.Mast.IsMastFullyDamaged");

        struct
        {
            bool ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.AthenaCharacter.GetCurrentShip
    class AActor* AAthenaCharacter::GetCurrentShip()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaCharacter.GetCurrentShip");

        struct
        {
            class AActor* ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.AthenaCharacter.IsDead
    bool AAthenaCharacter::IsDead()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaCharacter.IsDead");

        struct
        {
            bool ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.AthenaCharacter.IsInWater
    bool AAthenaCharacter::IsInWater()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaCharacter.IsInWater");

        struct
        {
            bool ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.AthenaPlayerState.GetHumanReadableName
    class FString AAthenaPlayerState::GetHumanReadableName()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaPlayerState.GetHumanReadableName");

        struct
        {
            class FString ReturnValue;
        } parms;

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.AthenaPlayerState.GetPlayerActivity
    TEnumAsByte<EPlayerActivityType> AAthenaPlayerState::GetPlayerActivity()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AthenaPlayerState.GetPlayerActivity");

        struct
        {
            TEnumAsByte<EPlayerActivityType> ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.OnlineAthenaPlayerController.IsClientAndInActiveGameplay
    bool AOnlineAthenaPlayerController::IsClientAndInActiveGameplay()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.OnlineAthenaPlayerController.IsClientAndInActiveGameplay");

        struct
        {
            bool ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.OnlineAthenaPlayerController.ModifyActiveState
    void AOnlineAthenaPlayerController::ModifyActiveState(bool IsActive)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.OnlineAthenaPlayerController.ModifyActiveState");

        struct
        {
            bool IsActive;
        } parms{};
        parms.IsActive = IsActive;

        UObject::ProcessEvent(this, fn, &parms);
    }

    // Function Athena.Cannon.Fire
    void ACannon::Fire()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.Cannon.Fire");

        struct
        {
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);
    }

    // Function Athena.Cannon.ForceAimCannon
    void ACannon::ForceAimCannon(float Pitch, float Yaw)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.Cannon.ForceAimCannon");

        struct
        {
            float Pitch;
            float Yaw;
        } parms{};
        parms.Pitch = Pitch;
        parms.Yaw = Yaw;

        UObject::ProcessEvent(this, fn, &parms);
    }

    // Function Athena.Ship.GetHullDamage
    class AHullDamage* AShip::GetHullDamage()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.Ship.GetHullDamage");

        struct
        {
            class AHullDamage* ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.Ship.GetInternalWater
    class AShipInternalWater* AShip::GetInternalWater()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.Ship.GetInternalWater");

        struct
        {
            class AShipInternalWater* ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.ShipService.GetNumShips
    int AShipService::GetNumShips()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.ShipService.GetNumShips");

        struct
        {
            int ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
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
        } parms{};
        parms.Player1 = Player1;
        parms.Player2 = Player2;

        static auto defaultObj = UObject::FindObject<UClass>("Class Athena.CrewFunctions");
        UObject::ProcessEvent(defaultObj, fn, &parms);

        return parms.ReturnValue;
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
        } parms{};
        parms.WorldContext = WorldContext;
        parms.Actor = Actor;

        static auto defaultObj = UObject::FindObject<UClass>("Class Athena.CrewFunctions");
        UObject::ProcessEvent(defaultObj, fn, &parms);

        return parms.ReturnValue;
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
        } parms{};
        parms.Actor = Actor;
        parms.Player = Player;

        static auto defaultObj = UObject::FindObject<UClass>("Class Athena.CrewFunctions");
        UObject::ProcessEvent(defaultObj, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.HealthComponent.GetCurrentHealth
    float UHealthComponent::GetCurrentHealth()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.HealthComponent.GetCurrentHealth");

        struct
        {
            float ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.HealthComponent.GetMaxHealth
    float UHealthComponent::GetMaxHealth()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.HealthComponent.GetMaxHealth");

        struct
        {
            float ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.HullDamage.IsShipSinking
    bool AHullDamage::IsShipSinking()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.HullDamage.IsShipSinking");

        struct
        {
            bool ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.Mermaid.GetCrewIdsResponsibleForSavingAsCopy
    TArray<struct FGuid> AMermaid::GetCrewIdsResponsibleForSavingAsCopy()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.Mermaid.GetCrewIdsResponsibleForSavingAsCopy");

        struct
        {
            TArray<struct FGuid> ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.WieldableInterface.GetActor
    class AActor* UWieldableInterface::GetActor()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.WieldableInterface.GetActor");

        struct
        {
            class AActor* ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
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
        } parms{};
        parms.WorldContext = WorldContext;
        parms.ActorName = ActorName;

        static auto defaultObj = UObject::FindObject<UClass>("Class Athena.ActorFunctionLibrary");
        UObject::ProcessEvent(defaultObj, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.DrowningComponent.GetOxygenLevel
    float UDrowningComponent::GetOxygenLevel()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.DrowningComponent.GetOxygenLevel");

        struct
        {
            float ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.ShipInternalWater.GetNormalizedWaterAmount
    float AShipInternalWater::GetNormalizedWaterAmount()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.ShipInternalWater.GetNormalizedWaterAmount");

        struct
        {
            float ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.AggressiveGhostShip.GetNumShotsLeftToKill
    int AAggressiveGhostShip::GetNumShotsLeftToKill()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AggressiveGhostShip.GetNumShotsLeftToKill");

        struct
        {
            int ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Athena.AggressiveGhostShip.GetShipType
    TEnumAsByte<EAggressiveGhostShipType> AAggressiveGhostShip::GetShipType()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Athena.AggressiveGhostShip.GetShipType");

        struct
        {
            TEnumAsByte<EAggressiveGhostShipType> ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }
}
