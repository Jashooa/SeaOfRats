#pragma once

#include "Engine.h"
#include "GameService.h"
#include "Sessions.h"

namespace SDK
{
    // Enum Athena.ESwimmingCreatureType
    enum class ESwimmingCreatureType : uint8_t
    {
        ESwimmingCreatureType__SwimmingCreature = 0,
        ESwimmingCreatureType__Shark = 1,
        ESwimmingCreatureType__TinyShark = 2,
        ESwimmingCreatureType__Siren = 3,
        ESwimmingCreatureType__ESwimmingCreatureType_MAX = 4
    };

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

    // Enum Athena.ERiddleActions
    enum class ERiddleActions : uint8_t
    {
        ERiddleActions__RaiseLanternAnyone = 0,
        ERiddleActions__PlayAnyInstrumentAnyone = 1,
        ERiddleActions__Dig = 2,
        ERiddleActions__LookAtMap = 3,
        ERiddleActions__NumActions = 4,
        ERiddleActions__ERiddleActions_MAX = 5
    };

    // Enum Athena.EAggressiveGhostShipType
    enum class EAggressiveGhostShipType : uint8_t
    {
        EAggressiveGhostShipType__Grunt = 0,
        EAggressiveGhostShipType__FormationGrunt = 1,
        EAggressiveGhostShipType__FormationLeader = 2,
        EAggressiveGhostShipType__CaptainFormationGrunt = 3,
        EAggressiveGhostShipType__Captain = 4,
        EAggressiveGhostShipType__EAggressiveGhostShipType_MAX = 5
    };

    // ScriptStruct Athena.TreasureMapTextEntry
    // 0x0048
    struct FTreasureMapTextEntry
    {
        class FString Name; // 0x0000(0x0010)
        struct FText Substitution; // 0x0010(0x0038)
    };

    // ScriptStruct Athena.TreasureMapTextDesc
    // 0x0048
    struct FTreasureMapTextDesc
    {
        struct FText Pattern; // 0x0000(0x0038)
        TArray<struct FTreasureMapTextEntry> Substitutions; // 0x0038(0x0010)
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
    // 0x0098
    struct FCrew
    {
        char pad_0x0000[0x0020];
        class TArray<class APlayerState*> Players; // 0x0020(0x0010)
        struct FCrewSessionTemplate CrewSessionTemplate; // 0x0030(0x0038)
        char pad_0x0068[0x0030];
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
    // 0x00C0
    struct FWeaponProjectileParams
    {
        char pad_0x0000[0x0010];
        float Velocity; // 0x0010(0x0004)
        char pad_0x0014[0x00AC];
    };

    // ScriptStruct Athena.ProjectileWeaponParameters
    // 0x0208
    struct FProjectileWeaponParameters
    {
        char pad_0x0000[0x005C];
        float ProjectileMaximumRange; // 0x005C(0x0004)
        char pad_0x0060[0x0020];
        struct FWeaponProjectileParams AmmoParams; // 0x0080(0x00C0)
        char pad_0x00140[0x00C8];
    };

    // ScriptStruct Athena.StorageContainerNode
    // 0x0010
    struct FStorageContainerNode
    {
        class UClass* ItemDesc; // 0x0000(0x0008)
        int NumItems; // 0x0008(0x0004)
        char pad_0x000C[0x0004];
    };

    // ScriptStruct Athena.RiddleMapContents
    // 0x0018
    struct FRiddleMapContents
    {
        TArray<struct FTreasureMapTextDesc> Text; // 0x0000(0x0010)
        int Progress; // 0x0010(0x0004)
        char pad_0x0014[0x0004];
    };

    // ScriptStruct Athena.XMarksTheSpotMapMark
    // 0x0010
    struct FXMarksTheSpotMapMark
    {
        struct FVector2D Position; // 0x0000(0x0008)
        float Rotation; // 0x0008(0x0004)
        bool IsUnderground; // 0x000C(0x0001)
        char pad_0x000D[0x0003];
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

    // ScriptStruct Athena.LandmarkReaction
    // 0x0038
    struct FLandmarkReaction
    {
        bool Enabled; // 0x0000(0x0001)
        char pad_0x0001[0x0003];
        float RelevantRadiusInMetres; // 0x0004(0x0004)
        TArray<TEnumAsByte<ERiddleActions>> ActionsThatTriggerThisReaction; // 0x0008(0x0010)
        char pad_0x0018[0x0020];
    };

    // ScriptStruct Athena.StorageContainerBackingStore
    // 0x0040
    struct FStorageContainerBackingStore
    {
        char pad_0x0000[0x0010];
        int MaxCapacityPerNode; // 0x0010(0x0004)
        int MaxNumNodes; // 0x0014(0x0004)
        int MaxCapacityTotal; // 0x0018(0x0004)
        char pad_0x001C[0x0004];
        TArray<struct FStorageContainerNode> ContainerNodes; // 0x0020(0x0010)
        bool AllowedItemsAreCached; // 0x0030(0x0001)
        char pad_0x0031[0x000F];
    };

    // ScriptStruct Athena.WorldMapIslandDataCaptureParams
    // 0x0040
    struct FWorldMapIslandDataCaptureParams
    {
        struct FVector CameraPosition; // 0x0000(0x000C)
        struct FRotator CameraOrientation; // 0x000C(0x000C)
        struct FVector WorldSpaceCameraPosition; // 0x0018(0x000C)
        float CameraFOV; // 0x0024(0x0004)
        float CameraAspect; // 0x0028(0x0004)
        float CameraOrthoWidth; // 0x002C(0x0004)
        float CameraNearClip; // 0x0030(0x0004)
        float CameraFarClip; // 0x0034(0x0004)
        int TextureWidth; // 0x0038(0x0004)
        int TextureHeight; // 0x003C(0x0004)
    };

    // ScriptStruct Athena.AggressiveGhostShipState
    // 0x0008
    struct FAggressiveGhostShipState
    {
        bool IsShipVisible; // 0x0000(0x0001)
        bool IsShipDead; // 0x0001(0x0001)
        char pad_0x0002[0x0002];
        float ShipSpeed; // 0x0004(0x0004)
    };

    // ScriptStruct Athena.EnchantedCompassTarget
    // 0x0018
    struct FEnchantedCompassTarget
    {
        int TargetID; // 0x0000(0x0004)
        struct FVector TargetLocation; // 0x0004(0x000C)
        TWeakObjectPtr<class AActor> TargetActor; // 0x0010(0x0008)
    };

    // Class Athena.EntitlementDesc
    // 0x00A0 (0x00C8 - 0x0028)
    class UEntitlementDesc : public UDataAsset
    {
    public:
        struct FText Title; // 0x0028(0x0038)
        char pad_0x0060[0x0068];
    };

    // Class Athena.InteractableBase
    // 0x0038 (0x0400 - 0x03C8)
    class AInteractableBase : public AActor
    {
    public:
        char pad_0x03C8[0x0038];
    };

    // Class Athena.ControllableObject
    // 0x0110 (0x0510 - 0x0400)
    class AControllableObject : public AInteractableBase
    {
    public:
        char pad_0x0400[0x0110];
    };

    // Class Athena.Mast
    // 0x0600 (0x09C8 - 0x03C8)
    class AMast : public AActor
    {
    public:
        char pad_0x03C8[0x0600];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.Mast");
            return ptr;
        }

        bool IsMastFullyDamaged();
    };

    // Class Athena.AthenaCharacter
    // 0x0640 (0x0C20 - 0x05E0)
    class AAthenaCharacter : public ACharacter
    {
    public:
        char pad_0x05E0[0x002A0];
        class UWieldedItemComponent* WieldedItemComponent; // 0x0880(0x0008)
        char pad_0x0888[0x0020];
        class UHealthComponent* HealthComponent; // 0x08A8(0x0008)
        char pad_0x08B0[0x0370];

        class AActor* GetCurrentShip();
        bool IsDead();
        bool IsInWater();
    };

    // Class Athena.AthenaPlayerCharacter
    // 0x1320 (0x1F40 - 0x0C20)
    class AAthenaPlayerCharacter : public AAthenaCharacter
    {
    public:
        char pad_0x0C20[0x01C8];
        class UDrowningComponent* DrowningComponent; // 0x0DE8(0x0008)
        char pad_0x0DF0[0x0010];
        class UTreasureMapCollectionComponent* TreasureMapCollectionComponent; // 0x0E00(0x0008)
        char pad_0x0E08[0x1138];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.AthenaPlayerCharacter");
            return ptr;
        }
    };

    // Class Athena.InteractableObject
    // 0x0068 (0x0468 - 0x0400)
    class AInteractableObject : public AInteractableBase
    {
    public:
        char pad_0x0400[0x0068];
    };

    // Class Athena.AthenaAICharacter
    // 0x0770 (0x1390 - 0x0C20)
    class AAthenaAICharacter : public AAthenaCharacter
    {
    public:
        char pad_0x0C20[0x01D0];
        class USkeletalMesh* AssignedMesh; // 0x0DF0(0x0008)
        class UColorTexture* TeamColorTexture; // 0x0DF8(0x0008)
        char pad_0x0E00[0x0590];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.AthenaAICharacter");
            return ptr;
        }
    };

    // Class Athena.AthenaGameState
    // 0x06F0 (0x0C30 - 0x0540)
    class AAthenaGameState : public AServiceProviderGameState
    {
    public:
        char pad_0x0540[0x0088];
        class AShipService* ShipService; // 0x05C8(0x0008)
        char pad_0x05D0[0x0030];
        class AStormService* StormService; // 0x0600(0x0008)
        class ACrewService* CrewService; // 0x0608(0x0008)
        char pad_0x0610[0x0010];
        class AIslandService* IslandService; // 0x0620(0x0008)
        char pad_0x0628[0x0078];
        class AKrakenService* KrakenService; // 0x06A0(0x0008)
        char pad_0x06A8[0x0588];

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
    // 0x03B0 (0x0800 - 0x0450)
    class AAthenaPlayerState : public APlayerState
    {
    public:
        char pad_0x0450[0x03B0];

        class FString GetHumanReadableName();
        TEnumAsByte<EPlayerActivityType> GetPlayerActivity();
    };

    // Class Athena.AthenaPlayerController
    // 0x0FB8 (0x1728 - 0x0770)
    class AAthenaPlayerController : public APlayerController
    {
    public:
        char pad_0x0770[0x0FB8];
    };

    // Class Athena.OnlineAthenaPlayerController
    // 0x00E8 (0x1810 - 0x1728)
    class AOnlineAthenaPlayerController : public AAthenaPlayerController
    {
    public:
        char pad_0x1728[0x0029];
        bool IdleDisconnectEnabled; // 0x1751(0x0001)
        char pad_0x1752[0x00BE];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.OnlineAthenaPlayerController");
            return ptr;
        }

        void ModifyActiveState(bool IsActive);
        bool IsClientAndInActiveGameplay();
    };

    // Class Athena.PickupableObject
    // 0x0210 (0x0610 - 0x0400)
    class APickupableObject : public AInteractableBase
    {
    public:
        char pad_0x0400[0x0210];
    };

    // Class Athena.ItemProxy
    // 0x0138 (0x0748 - 0x0610)
    class AItemProxy : public APickupableObject
    {
    public:
        char pad_0x0610[0x00B8];
        class AItemInfo* ItemInfo; // 0x06C8(0x0008)
        char pad_0x06D0[0x0078];
    };

    // Class Athena.FloatingItemProxy
    // 0x01B0 (0x08F8 - 0x0748)
    class AFloatingItemProxy : public AItemProxy
    {
    public:
        char pad_0x0748[0x01B0];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.FloatingItemProxy");
            return ptr;
        }
    };

    // Class Athena.BootyProxy
    // 0x0020 (0x0918 - 0x08F8)
    class ABootyProxy : public AFloatingItemProxy
    {
    public:
        char pad_0x08F8[0x0020];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.BootyProxy");
            return ptr;
        }
    };

    // Class Athena.ItemInfo
    // 0x0148 (0x0510 - 0x03C8)
    class AItemInfo : public AActor
    {
    public:
        char pad_0x03C8[0x0078];
        class UItemDesc* Desc; // 0x0440(0x0008)
        char pad_0x0448[0x00C8];
    };

    // Class Athena.NonStorableItemInfo
    // 0x0000 (0x0510 - 0x0510)
    class ANonStorableItemInfo : public AItemInfo
    {
    public:
    };

    // Class Athena.BootyItemInfo
    // 0x0218 (0x0728 - 0x0510)
    class ABootyItemInfo : public ANonStorableItemInfo
    {
    public:
        char pad_0x0510[0x01A4];
        struct FName Rarity; // 0x06B4(0x0008)
        char pad_0x06BC[0x006C];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.BootyItemInfo");
            return ptr;
        }
    };

    // Class Athena.WieldableItem
    // 0x0418 (0x07E0 - 0x03C8)
    class AWieldableItem : public AActor
    {
    public:
        char pad_0x03C8[0x0390];
        class AItemInfo* ItemInfo; // 0x0758(0x0008)
        char pad_0x0760[0x0080];
    };

    // Class Athena.SkeletalMeshWieldableItem
    // 0x0000 (0x0790 - 0x0790)
    class ASkeletalMeshWieldableItem : public AWieldableItem
    {
    public:
    };

    // Class Athena.ItemDesc
    // 0x0058 (0x0120 - 0x00C8)
    class UItemDesc : public UEntitlementDesc
    {
    public:
        char pad_0x00C8[0x0058];
    };

    // Class Athena.QuestBook
    // 0x03A0 (0x0B80 - 0x07E0)
    class AQuestBook : public ASkeletalMeshWieldableItem
    {
    public:
        char pad_0x07E0[0x03A0];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.QuestBook");
            return ptr;
        }
    };

    // Class Athena.TreasureMap
    // 0x0050 (0x0830 - 0x07E0)
    class ATreasureMap : public ASkeletalMeshWieldableItem
    {
    public:
        char pad_0x07E0[0x0050];
    };

    // Class Athena.Cannon
    // 0x0898 (0x0DA8 - 0x0510)
    class ACannon : public AControllableObject
    {
    public:
        char pad_0x0510[0x0050];
        class ULoadableComponent* LoadableComponent; // 0x0560(0x0008)
        char pad_0x0568[0x0054];
        float ProjectileSpeed; // 0x05BC(0x0004)
        float ProjectileGravityScale; // 0x05C0(0x0004)
        struct FFloatRange PitchRange; // 0x05C4(0x0010)
        struct FFloatRange YawRange; // 0x05D4(0x0010)
        char pad_0x05E4[0x018C];
        class AItemInfo* LoadedItemInfo; // 0x0770(0x0008)
        char pad_0x0778[0x0040];
        float ServerPitch; // 0x07B8(0x0004)
        float ServerYaw; // 0x07BC(0x0004)
        char pad_0x07C0[0x05E8];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.Cannon");
            return ptr;
        }

        void Fire();
        void ForceAimCannon(float Pitch, float Yaw);
    };

    // Class Athena.Ship
    // 0x14C8 (0x1890 - 0x03C8)
    class AShip : public AActor
    {
    public:
        char pad_0x03C8[0x14C8];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.Ship");
            return ptr;
        }

        class AHullDamage* GetHullDamage();
        class AShipInternalWater* GetInternalWater();
    };

    // Class Athena.Capstan
    // 0x04E8 (0x08B0 - 0x03C8)
    class ACapstan : public AActor
    {
    public:
        char pad_0x03C8[0x0190];
        struct FCapstanNetState NetState; // 0x0558(0x0008)
        char pad_0x0560[0x0350];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.Capstan");
            return ptr;
        }
    };

    // Class Athena.CapstanArm
    // 0x0050 (0x0560 - 0x0510)
    class ACapstanArm : public AControllableObject
    {
    public:
        char pad_0x0510[0x0050];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.CapstanArm");
            return ptr;
        }
    };

    // Class Athena.CrewService
    // 0x0210 (0x05D8 - 0x03C8)
    class ACrewService : public AActor
    {
    public:
        char pad_0x03C8[0x00D8];
        class TArray<struct FCrew> Crews; // 0x04A0(0x0010)
        char pad_0x04B0[0x0128];
    };

    // Class Athena.ModalInteractionProxy
    // 0x0120 (0x0520 - 0x0400)
    class AModalInteractionProxy : public AInteractableBase
    {
    public:
        char pad_0x0400[0x0040];
        struct FText DefaultTooltip; // 0x0440(0x0038)
        struct FText DefaultDisplayName; // 0x0478(0x0038)
        char pad_0x04B0[0x0070];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.ModalInteractionProxy");
            return ptr;
        }
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

    // Class Athena.DamageZone
    // 0x0420 (0x0820 - 0x0400)
    class ADamageZone : public AInteractableBase
    {
    public:
        char pad_0x0400[0x0254];
        int DamageLevel; // 0x0654(0x0004)
        char pad_0x0658[0x01C8];
    };

    // Class Athena.HealthComponent
    // 0x0180 (0x0248 - 0x00C8)
    class UHealthComponent : public UActorComponent
    {
    public:
        char pad_0x00C8[0x0180];

        float GetCurrentHealth();
        float GetMaxHealth();
    };

    // Class Athena.HullDamage
    // 0x0208 (0x05D0 - 0x03C8)
    class AHullDamage : public AActor
    {
    public:
        char pad_0x03C8[0x0048];
        TArray<class ADamageZone*> DamageZones; // 0x0410(0x0010)
        TArray<class ADamageZone*> ActiveHullDamageZones; // 0x0420(0x0010)
        TArray<class ADamageZone*> BottomDeckDamageZones; // 0x0430(0x0010)
        TArray<class ADamageZone*> MiddleDeckDamageZones; // 0x0440(0x0010)
        char pad_0x0450[0x0180];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.HullDamage");
            return ptr;
        }

        bool IsShipSinking();
    };

    // Class Athena.IslandService
    // 0x0220 (0x05E8 - 0x03C8)
    class AIslandService : public AActor
    {
    public:
        char pad_0x03C8[0x0090];
        class UIslandDataAsset* IslandDataAsset; // 0x0458(0x0008)
        char pad_0x0460[0x0188];
    };

    // Class Athena.LoadableComponent
    // 0x0128 (0x01F0 - 0x00C8)
    class ULoadableComponent : public UActorComponent
    {
    public:
        char pad_0x00C8[0x0008];
        float LoadTime; // 0x00D0(0x0004)
        float UnloadTime; // 0x00D4(0x0004)
        char pad_0x00D8[0x00B0];
        struct FLoadableComponentState LoadableComponentState; // 0x0188(0x0010)
        char pad_0x0198[0x0058];
    };

    // Class Athena.MapTable
    // 0x03E0 (0x07A8 - 0x03C8)
    class AMapTable : public AActor
    {
    public:
        char pad_0x03C8[0x0118];
        class TArray<struct FVector2D> MapPins; // 0x04E0(0x0010)
        char pad_0x04F0[0x02B8];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.MapTable");
            return ptr;
        }
    };

    // Class Athena.Mermaid
    // 0x0548 (0x09B0 - 0x0468)
    class AMermaid : public AInteractableObject
    {
    public:
        char pad_0x0468[0x0548];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.Mermaid");
            return ptr;
        }

        class TArray<struct FGuid> GetCrewIdsResponsibleForSavingAsCopy();
    };

    // Class Athena.NPCDialogComponent
    // 0x0450 (0x0518 - 0x00C8)
    class UNPCDialogComponent : public UActorComponent
    {
    public:
        char pad_0x00C8[0x0018];
        struct FText WelcomeMessage; // 0x00E0(0x0038)
        char pad_0x0118[0x0400];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.NPCDialogComponent");
            return ptr;
        }
    };

    // Class Athena.ProjectileWeapon
    // 0x0340 (0x0B20 - 0x07E0)
    class AProjectileWeapon : public ASkeletalMeshWieldableItem
    {
    public:
        char pad_0x07E0[0x0048];
        struct FProjectileWeaponParameters WeaponParameters; // 0x0828(0x0208)
        char pad_0x0A30[0x00F0];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.ProjectileWeapon");
            return ptr;
        }
    };

    // Class Athena.RiddleMap
    // 0x0140 (0x0970 - 0x0830)
    class ARiddleMap : public ATreasureMap
    {
    public:
        char pad_0x0830[0x0068];
        struct FRiddleMapContents Contents; // 0x0898(0x0018)
        struct FStringAssetReference MapInventoryTexturePath; // 0x08B0(0x0010)
        char pad_0x08C0[0x00B0];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.RiddleMap");
            return ptr;
        }
    };

    // Class Athena.NetProxy
    // 0x0030 (0x03F8 - 0x03C8)
    class ANetProxy : public AActor
    {
    public:
        char pad_0x03C8[0x0030];
    };

    // Class Athena.ShipNetProxy
    // 0x00B8 (0x04B0 - 0x03F8)
    class AShipNetProxy : public ANetProxy
    {
    public:
        char pad_0x03F8[0x00B8];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.ShipNetProxy");
            return ptr;
        }
    };

    // Class Athena.ShipService
    // 0x02D0 (0x0698 - 0x03C8)
    class AShipService : public AActor
    {
    public:
        char pad_0x03C8[0x02D0];

        int GetNumShips();
    };

    // Class Athena.SkeletonThrone
    // 0x0050 (0x0418 - 0x03C8)
    class ASkeletonThrone : public AActor
    {
    public:
        char pad_0x03C8[0x0050];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.SkeletonThrone");
            return ptr;
        }
    };

    // Class Athena.StorageContainer
    // 0x0060 (0x04C8 - 0x0468)
    class AStorageContainer : public AInteractableObject
    {
    public:
        char pad_0x0468[0x0060];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.StorageContainer");
            return ptr;
        }
    };


    // Class Athena.BuoyantStorageContainer
    // 0x0268 (0x0730 - 0x04C8)
    class ABuoyantStorageContainer : public AStorageContainer
    {
    public:
        char pad_0x04C8[0x0268];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.BuoyantStorageContainer");
            return ptr;
        }
    };

    // Class Athena.Storm
    // 0x0260 (0x0628 - 0x03C8)
    class AStorm : public AActor
    {
    public:
        char pad_0x03C8[0x0130];
        class FString SubjectName; // 0x04F8(0x0010)
        char pad_0x0508[0x0120];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.Storm");
            return ptr;
        }
    };

    // Class Athena.StormService
    // 0x0068 (0x0430 - 0x03C8)
    class AStormService : public AActor
    {
    public:
        char pad_0x03C8[0x0050];
        TArray<class AActor*> StormList; // 0x0418(0x0010)
        char pad_0x0428[0x0008];
    };

    // Class Athena.SwimmingCreaturePawn
    // 0x0500 (0x0940 - 0x0440)
    class ASwimmingCreaturePawn : public APawn
    {
    public:
        char pad_0x0440[0x0080];
        class USkeletalMeshMemoryConstraintComponent* Mesh; // 0x04C0(0x0008)
        char pad_0x04C8[0x0018];
        class UHealthComponent* HealthComponent; // 0x04E0(0x0008)
        char pad_0x04E8[0x003C];
        TEnumAsByte<ESwimmingCreatureType> SwimmingCreatureType; // 0x0524(0x0001)
        char pad_0x0525[0x041B];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.SwimmingCreaturePawn");
            return ptr;
        }
    };

    // Class Athena.SharkPawn
    // 0x0070 (0x09B0 - 0x0940)
    class ASharkPawn : public ASwimmingCreaturePawn
    {
    public:
        char pad_0x0940[0x0070];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.SharkPawn");
            return ptr;
        }
    };

    // Class Athena.TinyShark
    // 0x0060 (0x0A10 - 0x09B0)
    class ATinyShark : public ASharkPawn
    {
    public:
        char pad_0x09B0[0x0060];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.TinyShark");
            return ptr;
        }
    };

    // Class Athena.SirenPawn
    // 0x00E0 (0x0A20 - 0x0940)
    class ASirenPawn : public ASwimmingCreaturePawn
    {
    public:
        char pad_0x0940[0x0058];
        class UWieldedItemComponent* WieldedItemComponent; // 0x0998(0x0008)
        char pad_0x09A0[0x0080];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.SirenPawn");
            return ptr;
        }
    };

    // Class Athena.XMarksTheSpotMap
    // 0x0120 (0x0950 - 0x0830)
    class AXMarksTheSpotMap : public ATreasureMap
    {
    public:
        char pad_0x0830[0x0038];
        class FString MapTexturePath; // 0x0868(0x0010)
        struct FStringAssetReference MapInventoryTexturePath; // 0x0878(0x0010)
        char pad_0x0888[0x0070];
        TArray<struct FXMarksTheSpotMapMark> Marks; // 0x08F8(0x0010)
        char pad_0x0908[0x0018];
        float Rotation; // 0x0920(0x0004)
        char pad_0x0924[0x002C];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.XMarksTheSpotMap");
            return ptr;
        }
    };

    // Class Athena.TreasureMapCollectionComponent
    // 0x00F8 (0x01C0 - 0x00C8)
    class UTreasureMapCollectionComponent : public UActorComponent
    {
    public:
        char pad_0x00C8[0x00C8];
        TArray<class ATreasureMap*> TreasureMaps; // 0x0190(0x0010)
        TArray<struct FName> TreasureMapDestinationIslands; // 0x01A0(0x0010)
        char pad_0x01B0[0x0010];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.TreasureMapCollectionComponent");
            return ptr;
        }
    };

    // Class Athena.WieldedItemComponent
    // 0x0160 (0x0440 - 0x02E0)
    class UWieldedItemComponent : public USceneComponent
    {
    public:
        char pad_0x02E0[0x0010];
        class AActor* CurrentlyWieldedItem; // 0x02F0(0x0008)
        char pad_0x02F8[0x0148];
    };

    // Class Athena.RenderToTextureMapBase
    // 0x0060 (0x0890 - 0x0830)
    class ARenderToTextureMapBase : public ATreasureMap
    {
    public:
        char pad_0x0830[0x0060];
    };

    // Class Athena.ActorFunctionLibrary
    // 0x0000 (0x0028 - 0x0028)
    class UActorFunctionLibrary : public UBlueprintFunctionLibrary
    {
    public:
        static class AActor* FindActorByName(class UObject* WorldContext, const class FString& ActorName);
    };

    // Class Athena.SkeletalMeshMemoryConstraintComponent
    // 0x0090 (0x0A50 - 0x09C0)
    class USkeletalMeshMemoryConstraintComponent : public USkeletalMeshComponent
    {
    public:
        char pad_0x09C0[0x0040];
        struct FStringAssetReference MeshReference; // 0x0A00(0x0010)
        char pad_0x0A10[0x0040];
    };

    // Class Athena.WieldableInterface
    // 0x0000 (0x0028 - 0x0028)
    class UWieldableInterface : public UInterface
    {
    public:
        class AActor* GetActor();
    };

    // Class Athena.PoseableMeshWieldableItem
    // 0x0000 (0x07E0 - 0x07E0)
    class APoseableMeshWieldableItem : public AWieldableItem
    {
    public:
    };

    // Class Athena.ShipInternalWater
    // 0x0258 (0x0620 - 0x03C8)
    class AShipInternalWater : public AActor
    {
    public:
        char pad_0x03C8[0x0018];
        struct FShipInternalWaterParams InternalWaterParams; // 0x03E0(0x0038)
        float CurrentVisualWaterLevel; // 0x0418(0x0004)
        float WaterAmount; // 0x041C(0x0004)
        char pad_0x0420[0x0200];

        float GetNormalizedWaterAmount();
    };

    // Class Athena.Landmark
    // 0x0288 (0x0650 - 0x03C8)
    class ALandmark : public AActor
    {
    public:
        char pad_0x03C8[0x0218];
        TArray<struct FLandmarkReaction> Reactions; // 0x05E0(0x0010)
        char pad_0x05F0[0x0060];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.Landmark");
            return ptr;
        }
    };

    // Class Athena.StorageContainerComponent
    // 0x02F8 (0x03C0 - 0x00C8)
    class UStorageContainerComponent : public UActorComponent
    {
    public:
        char pad_0x00C8[0x0018];
        struct FText ContainerDisplayName; // 0x00E0(0x0038)
        char pad_0x0118[0x0038];
        struct FStorageContainerBackingStore ContainerNodes; // 0x0150(0x0040)
        char pad_0x0190[0x0230];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.StorageContainerComponent");
            return ptr;
        }
    };

    // Class Athena.IslandDataAssetEntry
    // 0x00F0 (0x0118 - 0x0028)
    class UIslandDataAssetEntry : public UDataAsset
    {
    public:
        struct FName IslandName; // 0x0028(0x0008)
        char pad_0x0030[0x0010];
        class UWorldMapIslandDataAsset* WorldMapData; // 0x0040(0x0008)
        char pad_0x0048[0x0068];
        struct FText LocalisedName; // 0x00B0(0x0038)
        char pad_0x00E8[0x0030];
    };

    // Class Athena.IslandDataAsset
    // 0x0030 (0x0058 - 0x0028)
    class UIslandDataAsset : public UDataAsset
    {
    public:
        char pad_0x0028[0x0020];
        TArray<class UIslandDataAssetEntry*> IslandDataEntries; // 0x0048(0x0010)
    };

    // Class Athena.WorldMapIslandDataAsset
    // 0x0050 (0x0078 - 0x0028)
    class UWorldMapIslandDataAsset : public UDataAsset
    {
    public:
        char pad_0x0028[0x0008];
        struct FWorldMapIslandDataCaptureParams CaptureParams; // 0x0030(0x0040)
        char pad_0x0070[0x0008];
    };

    // Class Athena.Compass
    // 0x0100 (0x08E0 - 0x07E0)
    class ACompass : public APoseableMeshWieldableItem
    {
    public:
        char pad_0x07E0[0x0100];
    };

    // Class Athena.DrowningComponent
    // 0x0100 (0x01C8 - 0x00C8)
    class UDrowningComponent : public UActorComponent
    {
    public:
        char pad_0x00C8[0x0100];

        float GetOxygenLevel();
    };

    // Class Athena.AggressiveGhostShip
    // 0x04B8 (0x0880 - 0x03C8)
    class AAggressiveGhostShip : public AActor
    {
    public:
        char pad_0x03C8[0x0158];
        struct FAggressiveGhostShipState ShipState; // 0x0520(0x0008)
        bool HasMadeShipAppear; // 0x0528(0x0001)
        char pad_0x0529[0x0357];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.AggressiveGhostShip");
            return ptr;
        }

        int GetNumShotsLeftToKill();
        TEnumAsByte<EAggressiveGhostShipType> GetShipType();
    };

    // Class Athena.TornMap
    // 0x00B0 (0x0940 - 0x0890)
    class ATornMap : public ARenderToTextureMapBase
    {
    public:
        char pad_0x0890[0x0038];
        TArray<struct FVector> TargetVisibility; // 0x08C8(0x0010)
        char pad_0x08D8[0x0028];
        int NumPieces; // 0x0900(0x0004)
        char pad_0x0904[0x003C];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.TornMap");
            return ptr;
        }
    };

    // Class Athena.EnchantedCompass
    // 0x00F0 (0x09D0 - 0x08E0)
    class AEnchantedCompass : public ACompass
    {
    public:
        char pad_0x08E0[0x0014];
        struct FEnchantedCompassTarget Target; // 0x08F4(0x0018)
        char pad_0x090C[0x00C4];

        static UClass* StaticClass()
        {
            static auto ptr = UObject::FindObject<UClass>("Class Athena.EnchantedCompass");
            return ptr;
        }
    };
}
