#pragma once

#ifdef _MSC_VER
#pragma pack(push, 0x8)
#endif

#include "Engine.h"
#include "GameService.h"
#include "Sessions.h"

namespace SDK
{
    // Enum Athena.ELoadableState
    enum class ELoadableState : uint8_t
    {
        ELoadableState__Unloaded = 0,
        ELoadableState__Unloading = 1,
        ELoadableState__Loading = 2,
        ELoadableState__Loaded = 3,
        ELoadableState__ELoadableState_MAX = 4
    };

    // Enum Athena.EPlayerActivityType
    enum class EPlayerActivityType : uint8_t
    {
        EPlayerActivityType__None = 0,
        EPlayerActivityType__Bailing = 1,
        EPlayerActivityType__Cannon = 2,
        EPlayerActivityType__Cannon_END = 3,
        EPlayerActivityType__Capstan = 4,
        EPlayerActivityType__Capstan_END = 5,
        EPlayerActivityType__CarryingBooty = 6,
        EPlayerActivityType__CarryingBooty_END = 7,
        EPlayerActivityType__Dead = 8,
        EPlayerActivityType__Dead_END = 9,
        EPlayerActivityType__Digging = 10,
        EPlayerActivityType__Dousing = 11,
        EPlayerActivityType__EmptyingBucket = 12,
        EPlayerActivityType__Harpoon = 13,
        EPlayerActivityType__Harpoon_END = 14,
        EPlayerActivityType__LoseHealth = 15,
        EPlayerActivityType__Repairing = 16,
        EPlayerActivityType__Sails = 17,
        EPlayerActivityType__Sails_END = 18,
        EPlayerActivityType__UndoingRepair = 19,
        EPlayerActivityType__Wheel = 20,
        EPlayerActivityType__Wheel_END = 21,
        EPlayerActivityType__MAX = 22,
        EPlayerActivityType__EPlayerActivityType_MAX = 23
    };

    // ScriptStruct Athena.CapstanNetState
    // 0x0008
    struct FCapstanNetState
    {
        float TargetRatio; // 0x0000(0x0004)
        bool IsLocked; // 0x0004(0x0001)
        char pad_0x0005[0x0003];
    };

    // ScriptStruct Athena.Crew
    // 0x0090
    struct FCrew
    {
        char pad_0x0000[0x0020];
        class TArray<class APlayerState*> Players; // 0x0020(0x0010)
        struct FCrewSessionTemplate CrewSessionTemplate; // 0x0030(0x0038)
        char pad_0x0068[0x0028];
    };

    // ScriptStruct Athena.LoadableComponentState
    // 0x0010
    struct FLoadableComponentState
    {
        TEnumAsByte<ELoadableState> LoadableState; // 0x0000(0x0001)
        char pad_0x0001[0x0007]; // 0x0001(0x0007)
        class UObject* LoadedItem; // 0x0008(0x0008)
    };

    // ScriptStruct Athena.WeaponProjectileParams
    // 0x00B0
    struct FWeaponProjectileParams
    {
        char pad_0x0000[0x0010];
        float Velocity; // 0x0010(0x0004)
        char pad_0x0014[0x009C];
    };

    // ScriptStruct Athena.ProjectileWeaponParameters
    // 0x01D8
    struct FProjectileWeaponParameters
    {
        char pad_0x0000[0x0054];
        float ProjectileMaximumRange; // 0x0054(0x0004)
        char pad_0x0058[0x0018];
        struct FWeaponProjectileParams AmmoParams; // 0x0070(0x00B0)
        char pad_0x00120[0x00B8];
    };

    // ScriptStruct Athena.ShipInternalWaterParams
    // 0x0038
    struct FShipInternalWaterParams
    {
        char pad_0x0000[0x0008];
        float MaxWaterAmount; // 0x0008(0x0004)
        float MaxWaterHeight; // 0x000C(0x0004)
        char pad_0x0010[0x0028];
    };

    // Class Athena.InteractableBase
    // 0x0028 (0x03F8 - 0x03D0)
    class AInteractableBase : public AActor
    {
    public:
        char pad_0x03D0[0x0028];
    };

    // Class Athena.ControllableObject
    // 0x0110 (0x0508 - 0x03F8)
    class AControllableObject : public AInteractableBase
    {
    public:
        char pad_0x03F8[0x0110];
    };

    // Class Athena.AthenaCharacter
    // 0x0620 (0x0C00 - 0x05E0)
    class AAthenaCharacter : public ACharacter
    {
    public:
        char pad_0x05E0[0x00250];
        class UWieldedItemComponent* WieldedItemComponent; // 0x0830(0x0008)
        char pad_0x0838[0x0020];
        class UHealthComponent* HealthComponent; // 0x0858(0x0008)
        char pad_0x0860[0x03A0];

        class AActor* GetCurrentShip();
        bool IsDead();
        bool IsInWater();
    };

    // Class Athena.AthenaPlayerCharacter
    // 0x0EC0 (0x1AC0 - 0x0C00)
    class AAthenaPlayerCharacter : public AAthenaCharacter
    {
    public:
        char pad_0x0C00[0x0170];
        class UDrowningComponent* DrowningComponent; // 0x0D70(0x0008)
        char pad_0x0D78[0x0010];
        class UTreasureMapCollectionComponent* TreasureMapCollectionComponent; // 0x0D88(0x0008)
        char pad_0x0D90[0x0D30];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.AthenaPlayerCharacter");
            return ptr;
        }
    };

    // Class Athena.InteractableObject
    // 0x0068 (0x0460 - 0x03F8)
    class AInteractableObject : public AInteractableBase
    {
    public:
        char pad_0x03F8[0x0068];
    };

    // Class Athena.AthenaAICharacter
    // 0x0660 (0x1260 - 0x0C00)
    class AAthenaAICharacter : public AAthenaCharacter
    {
    public:
        char pad_0x0C00[0x0660];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.AthenaAICharacter");
            return ptr;
        }
    };

    // Class Athena.AthenaGameState
    // 0x05B0 (0x0AF8 - 0x0548)
    class AAthenaGameState : public AServiceProviderGameState
    {
    public:
        char pad_0x0548[0x0070];
        char pad_0x05B8[0x0010];
        class AShipService* ShipService; // 0x05C8(0x0008)
        char pad_0x05D0[0x0038];
        class ACrewService* CrewService; // 0x0608(0x0008)
        char pad_0x0610[0x04E8];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.AthenaGameState");
            return ptr;
        }
    };

    // Class Athena.AthenaGameViewportClient
    // 0x0010 (0x0260 - 0x0250)
    class UAthenaGameViewportClient : public UGameViewportClient
    {
    public:
        static UAthenaGameViewportClient* GAthenaGameViewportClient;
        char pad_0x0250[0x0010];
    };

    // Class Athena.AthenaPlayerState
    // 0x0390 (0x07E8 - 0x0458)
    class AAthenaPlayerState : public APlayerState
    {
    public:
        char pad_0x0458[0x0390];

        TEnumAsByte<EPlayerActivityType> GetPlayerActivity();
    };

    // Class Athena.EntitlementDesc
    // 0x00B0 (0x00D8 - 0x0028)
    class UEntitlementDesc : public UDataAsset
    {
    public:
        struct FText Title; // 0x0028(0x0038)
        char pad_0x0060[0x0078];
    };

    // Class Athena.PickupableObject
    // 0x0130 (0x0528 - 0x03F8)
    class APickupableObject : public AInteractableBase
    {
    public:
        char pad_0x03F8[0x0130];
    };

    // Class Athena.ItemProxy
    // 0x0100 (0x0628 - 0x0528)
    class AItemProxy : public APickupableObject
    {
    public:
        char pad_0x0528[0x0090];
        class AItemInfo* ItemInfo; // 0x05B8(0x0008)
        char pad_0x05C0[0x0068];
    };

    // Class Athena.FloatingItemProxy
    // 0x0168 (0x0790 - 0x0628)
    class AFloatingItemProxy : public AItemProxy
    {
    public:
        char pad_0x0628[0x0168];
    };

    // Class Athena.BootyProxy
    // 0x0028 (0x07B8 - 0x0790)
    class ABootyProxy : public AFloatingItemProxy
    {
    public:
        char pad_0x0790[0x0028];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.BootyProxy");
            return ptr;
        }
    };

    // Class Athena.ItemInfo
    // 0x0130 (0x0500 - 0x03D0)
    class AItemInfo : public AActor
    {
    public:
        char pad_0x03D0[0x0060];
        class UItemDesc* Desc; // 0x0430(0x0008)
        char pad_0x0438[0x00C8];
    };

    // Class Athena.NonStorableItemInfo
    // 0x0000 (0x0500 - 0x0500)
    class ANonStorableItemInfo : public AItemInfo
    {
    public:
    };

    // Class Athena.BootyItemInfo
    // 0x0208 (0x0708 - 0x0500)
    class ABootyItemInfo : public ANonStorableItemInfo
    {
    public:
        char pad_0x0500[0x019C];
        struct FName Rarity; // 0x069C(0x0008)
        char pad_0x06A4[0x0064];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.BootyItemInfo");
            return ptr;
        }
    };

    // Class Athena.WieldableItem
    // 0x03C0 (0x0790 - 0x03D0)
    class AWieldableItem : public AActor
    {
    public:
        char pad_0x03D0[0x0348];
        class AItemInfo* ItemInfo; // 0x0718(0x0008)
        char pad_0x0720[0x0070];
    };

    // Class Athena.SkeletalMeshWieldableItem
    // 0x0000 (0x0790 - 0x0790)
    class ASkeletalMeshWieldableItem : public AWieldableItem
    {
    public:
    };

    // Class Athena.ItemDesc
    // 0x0058 (0x0130 - 0x00D8)
    class UItemDesc : public UEntitlementDesc
    {
    public:
        char pad_0x00D8[0x0058];
    };

    // Class Athena.QuestBook
    // 0x0360 (0x0AF0 - 0x0790)
    class AQuestBook : public ASkeletalMeshWieldableItem
    {
    public:
        char pad_0x0790[0x0360];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.QuestBook");
            return ptr;
        }
    };

    // Class Athena.TreasureMap
    // 0x0050 (0x07E0 - 0x0790)
    class ATreasureMap : public ASkeletalMeshWieldableItem
    {
    public:
        char pad_0x0790[0x0050];
    };

    // Class Athena.Cannon
    // 0x0700 (0x0C08 - 0x0508)
    class ACannon : public AControllableObject
    {
    public:
        char pad_0x0508[0x0040];
        class ULoadableComponent* LoadableComponent; // 0x0548(0x0008)
        char pad_0x0550[0x0054];
        float ProjectileSpeed; // 0x05A4(0x0004)
        float ProjectileGravityScale; // 0x05A8(0x0004)
        char pad_0x05Ac[0x01A8];
        float ServerPitch; // 0x0754(0x0004)
        float ServerYaw; // 0x0758(0x0004)
        char pad_0x075C[0x04AC];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.Cannon");
            return ptr;
        }
    };

    // Class Athena.Ship
    // 0x1100 (0x14D0 - 0x03D0)
    class AShip : public AActor
    {
    public:
        char pad_0x03D0[0x1100];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.Ship");
            return ptr;
        }

        class AShipInternalWater* GetInternalWater();
    };

    // Class Athena.Capstan
    // 0x03F8 (0x07C8 - 0x03D0)
    class ACapstan : public AActor
    {
    public:
        char pad_0x03D0[0x0168];
        struct FCapstanNetState NetState; // 0x0538(0x0008)
        char pad_0x0540[0x0288];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.Capstan");
            return ptr;
        }
    };

    // Class Athena.CapstanArm
    // 0x0038 (0x0540 - 0x0508)
    class ACapstanArm : public AControllableObject
    {
    public:
        char pad_0x0508[0x0038];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.CapstanArm");
            return ptr;
        }
    };

    // Class Athena.CrewService
    // 0x01A8 (0x0578 - 0x03D0)
    class ACrewService : public AActor
    {
    public:
        char pad_0x03D0[0x00D8];
        class TArray<struct FCrew> Crews; // 0x04A8(0x0010)
        char pad_0x04B8[0x00C0];
    };

    // Class Athena.ShipService
    // 0x0240 (0x0610 - 0x03D0)
    class AShipService : public AActor
    {
    public:
        char pad_0x03D0[0x0240];

        int GetNumShips();
    };

    // Class Athena.CrewFunctions
    // 0x0000 (0x0028 - 0x0028)
    class UCrewFunctions : public UBlueprintFunctionLibrary
    {
    public:
        static bool AreCharactersInSameCrew(class AAthenaCharacter* Player1, class AAthenaCharacter* Player2);
        static struct FGuid GetCrewIdFromActor(class UObject* WorldContext, class AActor* Actor);
        static bool IsActorMemberOfCharactersCrew(class AActor* Actor, class AAthenaCharacter* Player);
    };

    // Class Athena.HealthComponent
    // 0x0170 (0x0238 - 0x00C8)
    class UHealthComponent : public UActorComponent
    {
    public:
        char pad_0x00C8[0x0170];

        float GetCurrentHealth();
        float GetMaxHealth();
    };

    // Class Athena.LoadableComponent
    // 0x0118 (0x01E0 - 0x00C8)
    class ULoadableComponent : public UActorComponent
    {
    public:
        char pad_0x00C8[0x0008];
        float LoadTime; // 0x00D0(0x0004)
        float UnloadTime; // 0x00D4(0x0004)
        char pad_0x00D8[0x00A0];
        struct FLoadableComponentState LoadableComponentState; // 0x0178(0x0010)
        char pad_0x0188[0x0058];
    };

    // Class Athena.MapTable
    // 0x03A8 (0x0778 - 0x03D0)
    class AMapTable : public AActor
    {
    public:
        char pad_0x03D0[0x0118];
        class TArray<struct FVector2D> MapPins; // 0x04E8(0x0010)
        char pad_0x04F8[0x0280];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.MapTable");
            return ptr;
        }
    };

    // Class Athena.Mermaid
    // 0x0540 (0x09A0 - 0x0460)
    class AMermaid : public AInteractableObject
    {
    public:
        char pad_0x0460[0x0540];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.Mermaid");
            return ptr;
        }

        class TArray<struct FGuid> GetCrewIdsResponsibleForSavingAsCopy();
    };

    // Class Athena.ProjectileWeapon
    // 0x02D0 (0x0A60 - 0x0790)
    class AProjectileWeapon : public ASkeletalMeshWieldableItem
    {
    public:
        char pad_0x0790[0x0040];
        struct FProjectileWeaponParameters WeaponParameters; // 0x07D0(0x01D8)
        char pad_0x09A8[0x00B8];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.ProjectileWeapon");
            return ptr;
        }
    };

    // Class Athena.NetProxy
    // 0x0030 (0x0400 - 0x03D0)
    class ANetProxy : public AActor
    {
    public:
        char pad_0x03D0[0x0030];
    };

    // Class Athena.ShipNetProxy
    // 0x00C0 (0x04C0 - 0x0400)
    class AShipNetProxy : public ANetProxy
    {
    public:
        char pad_0x0400[0x00C0];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.ShipNetProxy");
            return ptr;
        }
    };

    // Class Athena.TreasureMapCollectionComponent
    // 0x00F0 (0x01B8 - 0x00C8)
    class UTreasureMapCollectionComponent : public UActorComponent
    {
    public:
        char pad_0x00C8[0x00C0];
        TArray<class ATreasureMap*> TreasureMaps; // 0x0188(0x0010)
        TArray<struct FName> TreasureMapDestinationIslands; // 0x0198(0x0010)
        char pad_0x01A8[0x0010];
    };

    // Class Athena.WieldedItemComponent
    // 0x0130 (0x03E0 - 0x02B0)
    class UWieldedItemComponent : public USceneComponent
    {
    public:
        char pad_0x02B0[0x0010];
        class AActor* CurrentlyWieldedItem; // 0x02C0(0x0008)
        char pad_0x02C8[0x0118];
    };

    // Class Athena.WieldableInterface
    // 0x0000 (0x0028 - 0x0028)
    class UWieldableInterface : public UInterface
    {
    public:
        class AActor* GetActor();
    };

    // Class Athena.ShipInternalWater
    // 0x0250 (0x0620 - 0x03D0)
    class AShipInternalWater : public AActor
    {
    public:
        char pad_0x03D0[0x0010];
        struct FShipInternalWaterParams InternalWaterParams; // 0x03E0(0x0038)
        float CurrentVisualWaterLevel; // 0x0418(0x0004)
        float WaterAmount; // 0x041C(0x0004)
        char pad_0x0420[0x0200];
    };

    // Class Athena.DrowningComponent
    // 0x00F8 (0x01C0 - 0x00C8)
    class UDrowningComponent : public UActorComponent
    {
    public:
        char pad_0x00C8[0x00F8];

        float GetOxygenLevel();
    };
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif
