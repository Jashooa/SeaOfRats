#pragma once

#ifdef _MSC_VER
    #pragma pack(push, 0x8)
#endif

#include "SoT_Basic.hpp"
#include "SoT_AIModule_enums.hpp"
#include "SoT_Athena_enums.hpp"
#include "SoT_AthenaAI_enums.hpp"
#include "SoT_AthenaEngine_enums.hpp"
#include "SoT_AthenaInput_enums.hpp"
#include "SoT_CoreUObject_classes.hpp"
#include "SoT_Interaction_enums.hpp"
#include "SoT_ItemQuality_enums.hpp"
#include "SoT_ObjectMessaging_structs.hpp"
#include "SoT_Maths_structs.hpp"

namespace SDK
{
	// ScriptStruct Athena.ItemLoadoutCapacity
	// 0x0010
	struct FItemLoadoutCapacity
	{
		class UClass* ItemCategory;                                             // 0x0000(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		int                                                Capacity;                                                 // 0x0008(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x4];                                       // 0x000C(0x0004) MISSED OFFSET
	};

	// ScriptStruct Athena.ItemLoadout
	// 0x0020
	struct FItemLoadout
	{
		TArray<struct FItemLoadoutCapacity>                Capacities;                                               // 0x0000(0x0010) (Edit, ZeroConstructor)
		TArray<class UClass*>                              Items;                                                    // 0x0010(0x0010) (Edit, ZeroConstructor)
	};

	// ScriptStruct Athena.PlayerStat
	// 0x000C
	struct FPlayerStat
	{
		struct FName                                       Name;                                                     // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x4];                                       // 0x0008(0x0004) MISSED OFFSET
	};

	// ScriptStruct Athena.BaseLightData
	// 0x0080
	struct FBaseLightData
	{
		float                                              Intensity;                                                // 0x0000(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		struct FColor                                      LightColor;                                               // 0x0004(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		unsigned char                                      bAffectsWorld : 1;                                        // 0x0008(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
		unsigned char                                      CastShadows : 1;                                          // 0x0008(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
		unsigned char                                      CastStaticShadows : 1;                                    // 0x0008(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
		unsigned char                                      CastDynamicShadows : 1;                                   // 0x0008(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
		unsigned char                                      bAffectTranslucentLighting : 1;                           // 0x0008(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
		unsigned char                                      bPrecomputedLightingIsValid : 1;                          // 0x0008(0x0001)
		unsigned char                                      RainOcclusion : 1;                                        // 0x0008(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
		unsigned char                                      UnknownData00[0x3];                                       // 0x0009(0x0003) MISSED OFFSET
		float                                              IndirectLightingIntensity;                                // 0x000C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              ScaleForTranslucency;                                     // 0x0010(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              CapForTranslucency;                                       // 0x0014(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              Temperature;                                              // 0x0018(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		unsigned char                                      bUseTemperature : 1;                                      // 0x001C(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
		unsigned char                                      UnknownData01[0x3];                                       // 0x001D(0x0003) MISSED OFFSET
		float                                              MinRoughness;                                             // 0x0020(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              ShadowBias;                                               // 0x0024(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              ShadowSharpen;                                            // 0x0028(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              ShadowResMaxDynamicDegradation;                           // 0x002C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		unsigned char                                      CastTranslucentShadows : 1;                               // 0x0030(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
		unsigned char                                      bCastShadowsFromCinematicObjectsOnly : 1;                 // 0x0030(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
		unsigned char                                      bAffectDynamicIndirectLighting : 1;                       // 0x0030(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
		unsigned char                                      UnknownData02[0x7];                                       // 0x0031(0x0007) MISSED OFFSET
		class UMaterialInterface* LightFunctionMaterial;                                    // 0x0038(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		struct FVector                                     LightFunctionScale;                                       // 0x0040(0x000C) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData03[0x4];                                       // 0x004C(0x0004) MISSED OFFSET
		class UTextureLightProfile* IESTexture;                                               // 0x0050(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		unsigned char                                      bUseIESBrightness : 1;                                    // 0x0058(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
		unsigned char                                      UnknownData04[0x3];                                       // 0x0059(0x0003) MISSED OFFSET
		float                                              IESBrightnessScale;                                       // 0x005C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              LightFunctionFadeDistance;                                // 0x0060(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              DisabledBrightness;                                       // 0x0064(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		unsigned char                                      bEnableLightShaftBloom : 1;                               // 0x0068(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
		unsigned char                                      UnknownData05[0x3];                                       // 0x0069(0x0003) MISSED OFFSET
		float                                              BloomScale;                                               // 0x006C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              BloomThreshold;                                           // 0x0070(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		struct FColor                                      BloomTint;                                                // 0x0074(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		bool                                               bUseRayTracedDistanceFieldShadows;                        // 0x0078(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData06[0x3];                                       // 0x0079(0x0003) MISSED OFFSET
		float                                              RayStartOffsetDepthScale;                                 // 0x007C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	};

	// ScriptStruct Athena.PointLightData
	// 0x003C
	struct FPointLightData
	{
		float                                              AttenuationRadius;                                        // 0x0000(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		unsigned char                                      bUseInverseSquaredFalloff : 1;                            // 0x0004(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly)
		unsigned char                                      UnknownData00[0x3];                                       // 0x0005(0x0003) MISSED OFFSET
		float                                              LightFalloffExponent;                                     // 0x0008(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              IntensityScaleForWater;                                   // 0x000C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              MinDistanceToLightAssumed;                                // 0x0010(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              SourceRadius;                                             // 0x0014(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              SourceLength;                                             // 0x0018(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		TEnumAsByte<ESimpleLightFunctionType>              SimpleFunctionType;                                       // 0x001C(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData01[0x3];                                       // 0x001D(0x0003) MISSED OFFSET
		float                                              ScaleOffset;                                              // 0x0020(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              PulsePhase;                                               // 0x0024(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              FlickerFrequency;                                         // 0x0028(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		int                                                FlickerPerlinRow;                                         // 0x002C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		struct FLightmassPointLightSettings                LightmassSettings;                                        // 0x0030(0x000C) (Edit, BlueprintVisible, BlueprintReadOnly)
	};

	// ScriptStruct Athena.SpotLightData
	// 0x000C
	struct FSpotLightData
	{
		float                                              InnerConeAngle;                                           // 0x0000(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              OuterConeAngle;                                           // 0x0004(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		float                                              KickBackRatio;                                            // 0x0008(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	};

	// ScriptStruct Athena.GenericLightTemplate
	// 0x00D0
	struct FGenericLightTemplate
	{
		TEnumAsByte<ELightTemplateType>                    LightType;                                                // 0x0000(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x7];                                       // 0x0001(0x0007) MISSED OFFSET
		struct FBaseLightData                              BaseLightData;                                            // 0x0008(0x0080) (Edit)
		struct FPointLightData                             PointLightData;                                           // 0x0088(0x003C) (Edit)
		struct FSpotLightData                              SpotLightData;                                            // 0x00C4(0x000C) (Edit)
	};

	// ScriptStruct AthenaEngine.BoxedRpc
	// 0x0010
	struct FBoxedRpc
	{
		unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
		class UScriptStruct* Type;                                                     // 0x0008(0x0008) (ZeroConstructor, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	};

	// ScriptStruct Athena.NetworkEventStruct
	// 0x0000 (0x0010 - 0x0010)
	struct FNetworkEventStruct : public FBoxedRpc
	{

	};

	// ScriptStruct Athena.QuestVariable
	// 0x0010
	struct FQuestVariable
	{
		unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
		struct FName                                       ParamName;                                                // 0x0008(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	};

	// ScriptStruct Athena.TelemetryFragmentInput
	// 0x0001
	struct FTelemetryFragmentInput
	{
		unsigned char                                      UnknownData00[0x1];                                       // 0x0000(0x0001) MISSED OFFSET
	};

	// ScriptStruct Athena.ImpactDamageEvent
	// 0x0058
	struct FImpactDamageEvent
	{
		struct FGuid                                       AttackId;                                                 // 0x0000(0x0010) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		class UClass* DamagerType;                                              // 0x0010(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
		class AActor* DirectInstigator;                                         // 0x0018(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
		class AActor* RootInstigator;                                           // 0x0020(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
		struct FVector                                     Location;                                                 // 0x0028(0x000C) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
		struct FVector                                     SurfaceNormal;                                            // 0x0034(0x000C) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
		struct FVector                                     Velocity;                                                 // 0x0040(0x000C) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              DamageAmount;                                             // 0x004C(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
		int                                                DamageSpread;                                             // 0x0050(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
		TEnumAsByte<EHealthChangedReason>                  Reason;                                                   // 0x0054(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
		bool                                               DealFriendlyFireDamage;                                   // 0x0055(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x2];                                       // 0x0056(0x0002) MISSED OFFSET
	};

	// ScriptStruct Athena.EncounterParams
	// 0x000C
	struct FEncounterParams
	{
		TEnumAsByte<EEncounterType>                        EncounterType;                                            // 0x0000(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		unsigned char                                      UnknownData00[0x3];                                       // 0x0001(0x0003) MISSED OFFSET
		float                                              EncounterRadius;                                          // 0x0004(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		TEnumAsByte<EEncounterDimensions>                  EncounterDimensions;                                      // 0x0008(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		TEnumAsByte<EEncounterMobility>                    EncounterMobility;                                        // 0x0009(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		unsigned char                                      UnknownData01[0x2];                                       // 0x000A(0x0002) MISSED OFFSET
	};

	// Class AthenaAI.AthenaAIFormComponent
	// 0x0070 (0x0138 - 0x00C8)
	class UAthenaAIFormComponent : public UActorComponent
	{
	public:
		unsigned char                                      UnknownData00[0x8];                                       // 0x00C8(0x0008) MISSED OFFSET
		TArray<struct FAthenaAIFormComponentVfxCustomisation> VfxCustomisations;                                        // 0x00D0(0x0010) (Edit, ZeroConstructor)
		class UAthenaAIFormDataAsset* FormData;                                                 // 0x00E0(0x0008) (Net, ZeroConstructor, IsPlainOldData)
		class UCharacterHitReactionDamagerTypeToAnimTypeLayer* HitReactionsLayer;                                        // 0x00E8(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
		unsigned char                                      UnknownData01[0x48];                                      // 0x00F0(0x0048) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AthenaAIFormComponent");
			return ptr;
		}


		void OnRep_FormData();
	};

	// Class Athena.EntitlementDesc
	// 0x00B0 (0x00D8 - 0x0028)
	class UEntitlementDesc : public UDataAsset
	{
	public:
		struct FText                                       Title;                                                    // 0x0028(0x0018) (Edit, DisableEditOnInstance)
		unsigned char                                      UnknownData00[0x20];                                      // 0x0028(0x0020) FIX WRONG TYPE SIZE OF PREVIOUS PROPERTY
		struct FText                                       Description;                                              // 0x0060(0x0018) (Edit, DisableEditOnInstance)
		unsigned char                                      UnknownData01[0x20];                                      // 0x0060(0x0020) FIX WRONG TYPE SIZE OF PREVIOUS PROPERTY
		struct FStringAssetReference                       IconPath;                                                 // 0x0098(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		struct FStringAssetReference                       IconInvPath;                                              // 0x00A8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		struct FStringAssetReference                       IconPrvPath;                                              // 0x00B8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		class UClass* Category;                                                 // 0x00C8(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		class UClass* Company;                                                  // 0x00D0(0x0008) (Edit, ZeroConstructor, IsPlainOldData)

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.EntitlementDesc");
			return ptr;
		}

	};

	// Class Athena.DamagerType
	// 0x0000 (0x0028 - 0x0028)
	class UDamagerType : public UObject
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.DamagerType");
			return ptr;
		}

	};

	// Class Athena.StatCondition
	// 0x0000 (0x0028 - 0x0028)
	class UStatCondition : public UObject
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.StatCondition");
			return ptr;
		}

	};

	// Class Athena.ItemDesc
	// 0x0058 (0x0130 - 0x00D8)
	class UItemDesc : public UEntitlementDesc
	{
	public:
		unsigned char                                      CanBeAddedToLoadout : 1;                                  // 0x00D8(0x0001) (Edit, DisableEditOnInstance)
		unsigned char                                      IsTransient : 1;                                          // 0x00D8(0x0001) (Edit, DisableEditOnInstance)
		unsigned char                                      UnknownData00[0x7];                                       // 0x00D9(0x0007) MISSED OFFSET
		struct FString                                     PreviousItem;                                             // 0x00E0(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		struct FString                                     NextItem;                                                 // 0x00F0(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		struct FStringAssetReference                       IconRadPath;                                              // 0x0100(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		struct FStringClassReference                       InstanceClassType;                                        // 0x0110(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FItemInfoTogglePair>                 ItemInfoOverrides;                                        // 0x0120(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.ItemDesc");
			return ptr;
		}

	};

	// Class Athena.CategoryBase
	// 0x0050 (0x0078 - 0x0028)
	class UCategoryBase : public UObject
	{
	public:
		struct FText                                       Name;                                                     // 0x0028(0x0018) (Edit, DisableEditOnInstance)
		unsigned char                                      UnknownData00[0x20];                                      // 0x0028(0x0020) FIX WRONG TYPE SIZE OF PREVIOUS PROPERTY
		struct FName                                       UniqueTextIdentifier;                                     // 0x0060(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		struct FStringAssetReference                       IconPath;                                                 // 0x0068(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.CategoryBase");
			return ptr;
		}

	};

	// Class Athena.ItemCategory
	// 0x0008 (0x0080 - 0x0078)
	class UItemCategory : public UCategoryBase
	{
	public:
		class UClass* NotificationInputId;                                      // 0x0078(0x0008) (ZeroConstructor, IsPlainOldData)

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.ItemCategory");
			return ptr;
		}

	};

	// Class Athena.ItemSpawnData
	// 0x0000 (0x0028 - 0x0028)
	class UItemSpawnData : public UObject
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.ItemSpawnData");
			return ptr;
		}

	};

	// Class AthenaAI.AIInteractableType
	// 0x0000 (0x0028 - 0x0028)
	class UAIInteractableType : public UObject
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AIInteractableType");
			return ptr;
		}

	};

	// Class AthenaAI.AIInteractableComponent
	// 0x0038 (0x0100 - 0x00C8)
	class UAIInteractableComponent : public UActorComponent
	{
	public:
		unsigned char                                      UnknownData00[0x8];                                       // 0x00C8(0x0008) MISSED OFFSET
		class UClass* Type;                                                     // 0x00D0(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		struct FVector                                     DetachOffsetFromOwner;                                    // 0x00D8(0x000C) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		bool                                               CanHaveTarget;                                            // 0x00E4(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		unsigned char                                      UnknownData01[0x1B];                                      // 0x00E5(0x001B) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AIInteractableComponent");
			return ptr;
		}

	};

	// Class AthenaAI.AIAnimationStateId
	// 0x0000 (0x0028 - 0x0028)
	class UAIAnimationStateId : public UObject
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AIAnimationStateId");
			return ptr;
		}

	};

	// Class AthenaAI.AIStrategyId
	// 0x0000 (0x0028 - 0x0028)
	class UAIStrategyId : public UObject
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AIStrategyId");
			return ptr;
		}

	};

	// ScriptStruct AthenaAI.AIPartId
	// 0x0008
	struct FAIPartId
	{
		struct FName                                       PartId;                                                   // 0x0000(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	};

	// Class AthenaAI.AIPartsDesc
	// 0x0008 (0x0030 - 0x0028)
	class UAIPartsDesc : public UDataAsset
	{
	public:
		struct FAIPartId                                   AIPartId;                                                 // 0x0028(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly)

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AIPartsDesc");
			return ptr;
		}

	};

	// Class Athena.NameplateComponent
	// 0x0030 (0x02C0 - 0x0290)
	class UNameplateComponent : public USceneComponent
	{
	public:
		class USkeletalMeshSocket* NameplateSocket;                                          // 0x0290(0x0008) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x28];                                      // 0x0298(0x0028) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.NameplateComponent");
			return ptr;
		}


		struct FVector GetWorldPosition();
	};

	// Class AIModule.BTNode
	// 0x0030 (0x0058 - 0x0028)
	class UBTNode : public UObject
	{
	public:
		unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
		struct FString                                     NodeName;                                                 // 0x0030(0x0010) (Edit, ZeroConstructor)
		class UBehaviorTree* TreeAsset;                                                // 0x0040(0x0008) (ZeroConstructor, IsPlainOldData)
		class UBTCompositeNode* ParentNode;                                               // 0x0048(0x0008) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData01[0x8];                                       // 0x0050(0x0008) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AIModule.BTNode");
			return ptr;
		}

	};


	// Class AIModule.BTAuxiliaryNode
	// 0x0008 (0x0060 - 0x0058)
	class UBTAuxiliaryNode : public UBTNode
	{
	public:
		unsigned char                                      UnknownData00[0x8];                                       // 0x0058(0x0008) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AIModule.BTAuxiliaryNode");
			return ptr;
		}

	};


	// Class AIModule.BTDecorator
	// 0x0008 (0x0068 - 0x0060)
	class UBTDecorator : public UBTAuxiliaryNode
	{
	public:
		unsigned char                                      UnknownData00 : 7;                                        // 0x0060(0x0001)
		unsigned char                                      bInverseCondition : 1;                                    // 0x0060(0x0001) (Edit)
		unsigned char                                      UnknownData01[0x3];                                       // 0x0061(0x0003) MISSED OFFSET
		TEnumAsByte<EBTFlowAbortMode>                      FlowAbortMode;                                            // 0x0064(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData02[0x3];                                       // 0x0065(0x0003) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AIModule.BTDecorator");
			return ptr;
		}

	};

	// Class AthenaAI.BTDecorator_BaseConditional
	// 0x0000 (0x0068 - 0x0068)
	class UBTDecorator_BaseConditional : public UBTDecorator
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.BTDecorator_BaseConditional");
			return ptr;
		}

	};

	// ScriptStruct AthenaAI.AISpawnTypeParams
	// 0x00E8
	struct FAISpawnTypeParams
	{
		TAssetPtr<class UClass>                            AIClass;                                                  // 0x0000(0x0020) (Edit)
		struct FStringAssetReference                       SkillsetOverride;                                         // 0x0020(0x0010) (Edit, ZeroConstructor)
		struct FStringAssetReference                       LoadoutOverride;                                          // 0x0030(0x0010) (Edit, ZeroConstructor)
		struct FStringAssetReference                       FormOverride;                                             // 0x0040(0x0010) (Edit, ZeroConstructor)
		struct FStringAssetReference                       AmmoOverride;                                             // 0x0050(0x0010) (Edit, ZeroConstructor)
		TAssetPtr<class UClass>                            ItemDropComponentClassOverride;                           // 0x0060(0x0020) (Edit)
		class UClass* AIClassIdOverride;                                        // 0x0080(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		struct FStringAssetReference                       TeamColorOverride;                                        // 0x0088(0x0010) (Edit, ZeroConstructor)
		struct FEncounterParams                            EncounterTrackingParams;                                  // 0x0098(0x000C) (Edit)
		struct FName                                       DioramaRole;                                              // 0x00A4(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x4];                                       // 0x00AC(0x0004) MISSED OFFSET
		struct FText                                       LocalisableName;                                          // 0x00B0(0x0018) (Edit)
		unsigned char                                      UnknownData01[0x20];                                      // 0x00AC(0x0020) FIX WRONG TYPE SIZE OF PREVIOUS PROPERTY
	};

	// ScriptStruct AthenaAI.WeightedAISpawnTypeParams
	// 0x00F0
	struct FWeightedAISpawnTypeParams
	{
		float                                              Weight;                                                   // 0x0000(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		int                                                MaxTimesCanBeSelected;                                    // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		struct FAISpawnTypeParams                          Params;                                                   // 0x0008(0x00E8) (Edit)
	};

	// ScriptStruct AthenaAI.AISpawnTypeParamsCollection
	// 0x0048
	struct FAISpawnTypeParamsCollection
	{
		unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
		TArray<struct FWeightedAISpawnTypeParams>          SpawnParams;                                              // 0x0008(0x0010) (Edit, ZeroConstructor)
		unsigned char                                      UnknownData01[0x30];                                      // 0x0018(0x0030) MISSED OFFSET
	};

	// Class AthenaAI.AISpawner
	// 0x03E0 (0x0408 - 0x0028)
	class UAISpawner : public UDataAsset
	{
	public:
		unsigned char                                      UnknownData00[0x10];                                      // 0x0028(0x0010) MISSED OFFSET
		bool                                               HasSpawnerLevelEncounters;                                // 0x0038(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData01[0x7];                                       // 0x0039(0x0007) MISSED OFFSET
		struct FAISpawnTypeParamsCollection                SpawnTypeParamsCollection;                                // 0x0040(0x0048) (Edit)
		class UAIEncounterSettings* DefaultEncounterSettings;                                 // 0x0088(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		class UAISpawnWaveSequenceRankProgression* DefaultSpawnWaveProgression;                              // 0x0090(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		TArray<struct FAISpawnContextIdEncounterSettingsPair> SpawnContextSpecificEncounterSettings;                    // 0x0098(0x0010) (Edit, ZeroConstructor)
		class UEnvQuery* FindSpawnPosQuery;                                        // 0x00A8(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		TEnumAsByte<EEnvQueryRunMode>                      FindSpawnPosQueryRunMode;                                 // 0x00B0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData02[0x3];                                       // 0x00B1(0x0003) MISSED OFFSET
		struct FName                                       SpawnLocationType;                                        // 0x00B4(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		int                                                MaxNumOfSpawnedPawns;                                     // 0x00BC(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		int                                                PriorityForSpawnedPawns;                                  // 0x00C0(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData03[0x214];                                     // 0x00C4(0x0214) MISSED OFFSET
		class UAthenaAISettings* AthenaAISettings;                                         // 0x02D8(0x0008) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData04[0x128];                                     // 0x02E0(0x0128) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AISpawner");
			return ptr;
		}


		int GetNumOfSpawnRequests();
	};


	// Class AthenaAI.AIPerCrewSpawner
	// 0x0138 (0x0540 - 0x0408)
	class UAIPerCrewSpawner : public UAISpawner
	{
	public:
		class UAIWeightedProbabilityRangeOfRangesRankProgression* DefaultRespawnTimerRanges;                                // 0x0408(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		int                                                MaxNumOfCrewsToSpawnFor;                                  // 0x0410(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               ActivateBySettingFootOnIsland;                            // 0x0414(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               UseRespawnTimerForFirstSpawn;                             // 0x0415(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               AssociateSpawnsWithSpecificCrews;                         // 0x0416(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               PerceiveTriggerActorOnSpawn;                              // 0x0417(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               EnforceRespawnTimeAfterCrewLeaves;                        // 0x0418(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               IgnoreSpawningGracePeriodForNewCrew;                      // 0x0419(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x126];                                     // 0x041A(0x0126) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AIPerCrewSpawner");
			return ptr;
		}

	};


	// Class AthenaAI.AIPlayerTracker
	// 0x0000 (0x0028 - 0x0028)
	class UAIPlayerTracker : public UObject
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AIPlayerTracker");
			return ptr;
		}

	};


	// Class AthenaAI.AISpawnerPlayerTracker
	// 0x0020 (0x0048 - 0x0028)
	class UAISpawnerPlayerTracker : public UAIPlayerTracker
	{
	public:
		unsigned char                                      UnknownData00[0x20];                                      // 0x0028(0x0020) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AISpawnerPlayerTracker");
			return ptr;
		}

	};


	// Class AthenaAI.AthenaAIAbilityType
	// 0x0000 (0x0028 - 0x0028)
	class UAthenaAIAbilityType : public UObject
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AthenaAIAbilityType");
			return ptr;
		}

	};


	// Class AthenaAI.AthenaAIAbilityStageParams
	// 0x0018 (0x0040 - 0x0028)
	class UAthenaAIAbilityStageParams : public UObject
	{
	public:
		float                                              AbilityCooldownSpeedMultiplier;                           // 0x0028(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              DamageRequiredForNextIntervalMultiplier;                  // 0x002C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               OverrideParams;                                           // 0x0030(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               AutoActivateOnStageTransition;                            // 0x0031(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x6];                                       // 0x0032(0x0006) MISSED OFFSET
		class UClass* TypeClass;                                                // 0x0038(0x0008) (ZeroConstructor, IsPlainOldData)

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AthenaAIAbilityStageParams");
			return ptr;
		}

	};


	// Class AthenaAI.AthenaAIAbility
	// 0x0048 (0x0070 - 0x0028)
	class UAthenaAIAbility : public UObject
	{
	public:
		class UAthenaAIAbilityParams* AbilityParams;                                            // 0x0028(0x0008) (ZeroConstructor, IsPlainOldData)
		class APawn* Pawn;                                                     // 0x0030(0x0008) (ZeroConstructor, IsPlainOldData)
		class AAthenaAIController* Controller;                                               // 0x0038(0x0008) (ZeroConstructor, IsPlainOldData)
		TScriptInterface<class UAIPawnInterface>           AIPawnInterface;                                          // 0x0040(0x0010) (ZeroConstructor, IsPlainOldData)
		class UAthenaAIAbilityStageParams* CurrentAbilityStageParams;                                // 0x0050(0x0008) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x18];                                      // 0x0058(0x0018) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AthenaAIAbility");
			return ptr;
		}

	};

	// ScriptStruct AthenaAI.AthenaAIAbilityPlayerBasedRange
	// 0x0038
	struct FAthenaAIAbilityPlayerBasedRange
	{
		int                                                MaxPlayers;                                               // 0x0000(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x4];                                       // 0x0004(0x0004) MISSED OFFSET
		struct FWeightedProbabilityRangeOfRanges           WeightedArray;                                            // 0x0008(0x0030) (Edit)
	};

	// ScriptStruct AthenaAI.AthenaAIAbilityPlayerBasedRanges
	// 0x0010
	struct FAthenaAIAbilityPlayerBasedRanges
	{
		TArray<struct FAthenaAIAbilityPlayerBasedRange>    AbilityRanges;                                            // 0x0000(0x0010) (Edit, ZeroConstructor)
	};

	// ScriptStruct AthenaAI.MinMaxAbilityRange
	// 0x0008
	struct FMinMaxAbilityRange
	{
		float                                              MinDistanceToTarget;                                      // 0x0000(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              MaxDistanceToTarget;                                      // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	};

	// Class AthenaAI.AthenaAIAbilityParams
	// 0x0068 (0x0090 - 0x0028)
	class UAthenaAIAbilityParams : public UObject
	{
	public:
		TEnumAsByte<EAIAbilityDamageIntervalCounterMode>   DamageIntervalCountingMode;                               // 0x0028(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               UseTimeBetweenAbility;                                    // 0x0029(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x6];                                       // 0x002A(0x0006) MISSED OFFSET
		struct FAthenaAIAbilityPlayerBasedRanges           ActivationTimerCooldown;                                  // 0x0030(0x0010) (Edit)
		struct FAthenaAIAbilityPlayerBasedRanges           TimeBetweenAbility;                                       // 0x0040(0x0010) (Edit)
		bool                                               UseDamageBetweenAbility;                                  // 0x0050(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData01[0x7];                                       // 0x0051(0x0007) MISSED OFFSET
		struct FAthenaAIAbilityPlayerBasedRanges           DamageBetweenAbility;                                     // 0x0058(0x0010) (Edit)
		float                                              AbilityRadius;                                            // 0x0068(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               UseMinMaxAttackRange;                                     // 0x006C(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData02[0x3];                                       // 0x006D(0x0003) MISSED OFFSET
		struct FMinMaxAbilityRange                         MinMaxAttackRange;                                        // 0x0070(0x0008) (Edit)
		TArray<struct FAIAbilityFollowUp>                  FollowUpAbilities;                                        // 0x0078(0x0010) (Edit, ZeroConstructor)
		class UClass* AIAbilityTypeClass;                                       // 0x0088(0x0008) (ZeroConstructor, IsPlainOldData)

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AthenaAIAbilityParams");
			return ptr;
		}

	};

	// ScriptStruct Athena.KnockBackInfo
	// 0x0044
	struct FKnockBackInfo
	{
		struct FName                                       FeatureName;                                              // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              HorizontalVelocity;                                       // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              VerticalVelocity;                                         // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              MinHorizontalVelocity;                                    // 0x0010(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              MinVerticalVelocity;                                      // 0x0014(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              SwimmingVelocity;                                         // 0x0018(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              DockedHorizontalVelocity;                                 // 0x001C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              DockedVerticalVelocity;                                   // 0x0020(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		bool                                               UseDockedVelocitiesWhenDocked;                            // 0x0024(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x3];                                       // 0x0025(0x0003) MISSED OFFSET
		struct FName                                       RumbleTag;                                                // 0x0028(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              StunDuration;                                             // 0x0030(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              AIKnockbackDistance;                                      // 0x0034(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              AIKnockbackSpeed;                                         // 0x0038(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              AIKnockbackAcceleration;                                  // 0x003C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		TEnumAsByte<EAIKnockbackStrengthType>              AIKnockbackStrengthType;                                  // 0x0040(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData01[0x3];                                       // 0x0041(0x0003) MISSED OFFSET
	};

	// ScriptStruct Athena.DetailAppearenceDesc
	// 0x0020
	struct FDetailAppearenceDesc
	{
		struct FStringAssetReference                       Mesh;                                                     // 0x0000(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor)
		TArray<struct FDetailAppearenceMaterialDesc>       Materials;                                                // 0x0010(0x0010) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor)
	};

	// Class Athena.WieldableItem
	// 0x03A0 (0x07B0 - 0x0410)
	class AWieldableItem : public AActor
	{
	public:
		unsigned char                                      UnknownData00[0x50];                                      // 0x0410(0x0050) MISSED OFFSET
		class UPrimitiveComponent* FirstPersonMesh;                                          // 0x0460(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
		class UPrimitiveComponent* ThirdPersonMesh;                                          // 0x0468(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
		class UActionRulesComponent* ActionRulesComponent;                                     // 0x0470(0x0008) (Edit, BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
		class UClass* AnimationKey;                                             // 0x0478(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		struct FObjectMessagingDispatcher                  MessagingDispatcher;                                      // 0x0480(0x00A0) (BlueprintVisible)
		struct FTransform                                  AnimationOffset;                                          // 0x0520(0x0030) (Edit, BlueprintVisible, DisableEditOnInstance, IsPlainOldData)
		class UWwiseEvent* EquipSfx;                                                 // 0x0550(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		class UWwiseEvent* UnequipSfx;                                               // 0x0558(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		class UWwiseEvent* WielderLandedJumpSfx;                                     // 0x0560(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		class UWwiseEvent* WielderFootstepLayerOneshot;                              // 0x0568(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		struct FName                                       PlayerWalkSpeedRtpc;                                      // 0x0570(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		TEnumAsByte<EWieldableItemSize>                    ItemSize;                                                 // 0x0578(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData01[0x7];                                       // 0x0579(0x0007) MISSED OFFSET
		struct FDetailAppearenceDesc                       DetailAppearence;                                         // 0x0580(0x0020) (Edit, BlueprintVisible, BlueprintReadOnly, DisableEditOnInstance)
		bool                                               PropagateVisibilityToChildren;                            // 0x05A0(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		unsigned char                                      UnknownData02[0x3];                                       // 0x05A1(0x0003) MISSED OFFSET
		struct FName                                       AINoiseTag;                                               // 0x05A4(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		unsigned char                                      UnknownData03[0x4];                                       // 0x05AC(0x0004) MISSED OFFSET
		class UClass* ItemCategory;                                             // 0x05B0(0x0008) (Net, ZeroConstructor, IsPlainOldData)
		class AItemInfo* ItemInfo;                                                 // 0x05B8(0x0008) (Net, ZeroConstructor, IsPlainOldData)
		TArray<struct FName>                               ThirdPersonExtraMeshNames;                                // 0x05C0(0x0010) (Edit, ZeroConstructor)
		TArray<struct FName>                               StashedExtraMeshNames;                                    // 0x05D0(0x0010) (Edit, ZeroConstructor)
		class UMeshComponent* StashedMeshComponent;                                     // 0x05E0(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
		struct FName                                       StashedMeshAttachSocket;                                  // 0x05E8(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		struct FName                                       ServerWieldAttachSocket;                                  // 0x05F0(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		class UPhrasesRadialDataAsset* Phrases;                                                  // 0x05F8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		class UObject* CachedFirstPersonProxyMesh;                               // 0x0600(0x0008) (BlueprintVisible, ZeroConstructor, Transient, IsPlainOldData)
		class UObject* CachedThirdPersonProxyMesh;                               // 0x0608(0x0008) (BlueprintVisible, ZeroConstructor, Transient, IsPlainOldData)
		unsigned char                                      UnknownData04[0x128];                                     // 0x0610(0x0128) MISSED OFFSET
		class AInterpolatingItem* InterpolatingItem;                                        // 0x0738(0x0008) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData05[0x18];                                      // 0x0740(0x0018) MISSED OFFSET
		TWeakObjectPtr<class AActor>                       LastKnownWielder;                                         // 0x0758(0x0008) (ZeroConstructor, IsPlainOldData)
		class UWieldableItemVfxComponent* WieldableItemVfxComponent;                                // 0x0760(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
		TArray<class UMeshComponent*>                      ThirdPersonExtraMeshes;                                   // 0x0768(0x0010) (ExportObject, ZeroConstructor, Transient)
		TArray<class UMeshComponent*>                      StashedExtraMeshes;                                       // 0x0778(0x0010) (ExportObject, ZeroConstructor, Transient)
		unsigned char                                      UnknownData06[0x19];                                      // 0x0788(0x0019) MISSED OFFSET
		bool                                               OfferingEnabled;                                          // 0x07A1(0x0001) (Net, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData07[0xE];                                       // 0x07A2(0x000E) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.WieldableItem");
			return ptr;
		}


		void SetItemWwiseSwitch(const struct FName& SwitchGroup, const struct FName& SwitchOption);
		void SetItemWwiseRTPC(float Value, struct FName* RTPCName);
		void PostItemWwiseEvent(class UWwiseEvent* Event);
		void OnWielderHasLandedFromJumpBPImpl();
		bool IsUnderwater();
		class AActor* GetWielder();
		struct FTransform GetWieldedItemAnimationOffset();
		TEnumAsByte<EWieldableItemSize> GetWieldableItemSize();
		class AActor* GetLastKnownWielder();
		bool GetIsFirstPerson();
	};


	// Class Athena.SkeletalMeshWieldableItem
	// 0x0000 (0x07B0 - 0x07B0)
	class ASkeletalMeshWieldableItem : public AWieldableItem
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.SkeletalMeshWieldableItem");
			return ptr;
		}

	};


	// Class Athena.ItemInfo
	// 0x0128 (0x0538 - 0x0410)
	class AItemInfo : public AActor
	{
	public:
		unsigned char                                      UnknownData00[0x20];                                      // 0x0410(0x0020) MISSED OFFSET
		bool                                               CanBeStoredInInventory;                                   // 0x0430(0x0001) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData01[0x7];                                       // 0x0431(0x0007) MISSED OFFSET
		struct FScriptMulticastDelegate                    OnItemPickedUpDelegate;                                   // 0x0438(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
		class UClass* WieldableType;                                            // 0x0448(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		class UClass* ProxyType;                                                // 0x0450(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		class UClass* ProjectileType;                                           // 0x0458(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		class UParticleSystem* LoadedItemParticleTemplate;                               // 0x0460(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		class UItemDesc* Desc;                                                     // 0x0468(0x0008) (Net, ZeroConstructor, IsPlainOldData)
		TEnumAsByte<EItemRepresentation>                   CurrentRepresentation;                                    // 0x0470(0x0001) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData02[0x7];                                       // 0x0471(0x0007) MISSED OFFSET
		class AActor* CurrentRepresentationInstance;                            // 0x0478(0x0008) (Edit, Net, ZeroConstructor, EditConst, IsPlainOldData)
		class AActor* CurrentOwner;                                             // 0x0480(0x0008) (Edit, ZeroConstructor, EditConst, IsPlainOldData)
		class AActor* TutorialOwner;                                            // 0x0488(0x0008) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData03[0xA1];                                      // 0x0490(0x00A1) MISSED OFFSET
		bool                                               DoNotConsiderForMigrationGather;                          // 0x0531(0x0001) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData04[0x6];                                       // 0x0532(0x0006) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.ItemInfo");
			return ptr;
		}


		void SwitchNetworkClusterToLevel(class ULevel* Level);
		void SwitchNetworkClusterToGlobal();
		void SwitchNetworkClusterToActorOrItsLevel(class AActor* NewOwner);
		void SwitchNetworkClusterTo(class AActor* NewOwner);
		void OnRep_CurrentRepresentationInstance();
		class UClass* GetItemType();
		class UClass* GetItemCategory();
		class AActor* GetItem();
		class AWieldableItem* GetAsWieldable();
		class AWieldableItem* CreateWieldableItem(class AActor* InNewOwner, const struct FTransform& InTransform);
		class AActor* CreateProxyItem(const struct FTransform& InTransform, TEnumAsByte<EItemLifetimeManagement> LifetimeManagement);
	};


	// Class Athena.NonStorableItemInfo
	// 0x0000 (0x0538 - 0x0538)
	class ANonStorableItemInfo : public AItemInfo
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.NonStorableItemInfo");
			return ptr;
		}

	};


	// Class AIModule.AIController
	// 0x0090 (0x0500 - 0x0470)
	class AAIController : public AController
	{
	public:
		unsigned char                                      UnknownData00[0x28];                                      // 0x0470(0x0028) MISSED OFFSET
		unsigned char                                      bLOSflag : 1;                                             // 0x0498(0x0001)
		unsigned char                                      bSkipExtraLOSChecks : 1;                                  // 0x0498(0x0001)
		unsigned char                                      bAllowStrafe : 1;                                         // 0x0498(0x0001)
		unsigned char                                      bWantsPlayerState : 1;                                    // 0x0498(0x0001)
		unsigned char                                      bDisableControlRotation : 1;                              // 0x0498(0x0001)
		unsigned char                                      UnknownData01[0x7];                                       // 0x0499(0x0007) MISSED OFFSET
		class UPathFollowingComponent* PathFollowingComponent;                                   // 0x04A0(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
		class UBrainComponent* BrainComponent;                                           // 0x04A8(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
		class UAIPerceptionComponent* PerceptionComponent;                                      // 0x04B0(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, EditConst, InstancedReference, IsPlainOldData)
		class UPawnActionsComponent* ActionsComp;                                              // 0x04B8(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)
		class UBlackboardComponent* Blackboard;                                               // 0x04C0(0x0008) (BlueprintVisible, ExportObject, BlueprintReadOnly, ZeroConstructor, InstancedReference, IsPlainOldData)
		class UGameplayTasksComponent* CachedGameplayTasksComponent;                             // 0x04C8(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
		unsigned char                                      UnknownData02[0x10];                                      // 0x04D0(0x0010) MISSED OFFSET
		struct FScriptMulticastDelegate                    ReceiveMoveCompleted;                                     // 0x04E0(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
		unsigned char                                      UnknownData03[0x10];                                      // 0x04F0(0x0010) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AIModule.AIController");
			return ptr;
		}


		bool UseBlackboard(class UBlackboardData* BlackboardAsset, class UBlackboardComponent** BlackboardComponent);
		void SetMoveBlockDetection(bool bEnable);
		bool RunBehaviorTree(class UBehaviorTree* BTAsset);
		void OnUsingBlackBoard(class UBlackboardComponent* BlackboardComp, class UBlackboardData* BlackboardAsset);
		void OnPossess(class APawn* PossessedPawn);
		void OnGameplayTaskResourcesClaimed(const struct FGameplayResourceSet& NewlyClaimed, const struct FGameplayResourceSet& FreshlyReleased);
		TEnumAsByte<EPathFollowingRequestResult> MoveToLocation(const struct FVector& Dest, float AcceptanceRadius, bool bStopOnOverlap, bool bUsePathfinding, bool bProjectDestinationToNavigation, bool bCanStrafe, class UClass* FilterClass, bool bAllowPartialPath);
		TEnumAsByte<EPathFollowingRequestResult> MoveToActor(class AActor* Goal, float AcceptanceRadius, bool bStopOnOverlap, bool bUsePathfinding, bool bCanStrafe, class UClass* FilterClass, bool bAllowPartialPath);
		void K2_SetFocus(class AActor* NewFocus);
		void K2_SetFocalPoint(const struct FVector& FP);
		void K2_ClearFocus();
		bool HasPartialPath();
		class UPathFollowingComponent* GetPathFollowingComponent();
		TEnumAsByte<EPathFollowingStatus> GetMoveStatus();
		struct FVector GetImmediateMoveDestination();
		class AActor* GetFocusActor();
		struct FVector GetFocalPointOnActor(class AActor* Actor);
		struct FVector GetFocalPoint();
		class UAIPerceptionComponent* GetAIPerceptionComponent();
	};


	// Class AthenaAI.AthenaAIControllerBase
	// 0x0158 (0x0658 - 0x0500)
	class AAthenaAIControllerBase : public AAIController
	{
	public:
		unsigned char                                      UnknownData00[0x158];                                     // 0x0500(0x0158) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AthenaAIControllerBase");
			return ptr;
		}


		void SetNamedControllerParam(const struct FName& ParamName, float Value);
		struct FWeightedProbabilityRangeOfRanges FindNamedWeightedRangesControllerParam(const struct FName& ParamName);
		float FindNamedControllerParam(const struct FName& ParamName);
		void ApplyControllerParams(class UAthenaAIControllerParamsDataAsset* ParamsAsset, class APawn* InPawn);
	};

	// Class Athena.PoseableMeshWieldableItem
	// 0x0000 (0x07B0 - 0x07B0)
	class APoseableMeshWieldableItem : public AWieldableItem
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.PoseableMeshWieldableItem");
			return ptr;
		}

	};

	// Class Athena.Compass
	// 0x00D0 (0x0880 - 0x07B0)
	class ACompass : public APoseableMeshWieldableItem
	{
	public:
		class UUsableWieldableComponent* UsableWieldableComponent;                                 // 0x07B0(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
		class UCompassSpinComponent* SpinComponent;                                            // 0x07B8(0x0008) (Edit, ExportObject, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
		class UPoseableMeshComponent* MeshToUse;                                                // 0x07C0(0x0008) (ExportObject, ZeroConstructor, Transient, InstancedReference, IsPlainOldData)
		unsigned char                                      UnknownData00[0xB8];                                      // 0x07C8(0x00B8) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.Compass");
			return ptr;
		}

	};

	// ScriptStruct Athena.EmissaryBootyItemStats
	// 0x0018
	struct FEmissaryBootyItemStats
	{
		class UClass* EmissaryCompany;                                          // 0x0000(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		TArray<struct FPlayerStat>                         Stats;                                                    // 0x0008(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	};

	// ScriptStruct Athena.BootyItemStats
	// 0x0090
	struct FBootyItemStats
	{
		TArray<struct FPlayerStat>                         HandInPlayerStats;                                        // 0x0000(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FPlayerStat>                         HandInStolenPlayerStats;                                  // 0x0010(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FPlayerStat>                         HandInAsPirateLegendPlayerStats;                          // 0x0020(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FPlayerStat>                         HandInOnSchedulePlayerStats;                              // 0x0030(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FPlayerStat>                         HandInAsPirateLegendOnSchedulePlayerStats;                // 0x0040(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FEmissaryBootyItemStats>             HandInAsEmissaryPlayerStats;                              // 0x0050(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FEmissaryBootyItemStats>             HandInAsMaxLevelEmissaryPlayerStats;                      // 0x0060(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FEmissaryBootyItemStats>             HandInStolenAsEmissaryPlayerStats;                        // 0x0070(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FEmissaryBootyItemStats>             HandInStolenAsMaxLevelEmissaryPlayerStats;                // 0x0080(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	};

	// ScriptStruct Athena.CompanyBootyStats
	// 0x0098
	struct FCompanyBootyStats
	{
		class UClass* CompanyId;                                                // 0x0000(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		struct FBootyItemStats                             Stats;                                                    // 0x0008(0x0090) (Edit, DisableEditOnInstance)
	};

	// ScriptStruct Athena.CompanyBootyStatList
	// 0x0010
	struct FCompanyBootyStatList
	{
		TArray<struct FCompanyBootyStats>                  CompanyList;                                              // 0x0000(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	};

	// ScriptStruct Athena.BootyItemSellPrerequisites
	// 0x0010
	struct FBootyItemSellPrerequisites
	{
		TArray<class UClass*>                              Entitlements;                                             // 0x0000(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
	};

	// ScriptStruct Athena.RewardId
	// 0x0008
	struct FRewardId
	{
		struct FName                                       RewardId;                                                 // 0x0000(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	};

	// Class Athena.BootyItemInfo
	// 0x01F0 (0x0728 - 0x0538)
	class ABootyItemInfo : public ANonStorableItemInfo
	{
	public:
		unsigned char                                      UnknownData00[0x18];                                      // 0x0538(0x0018) MISSED OFFSET
		TEnumAsByte<EBootyTypes>                           BootyType;                                                // 0x0550(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		unsigned char                                      UnknownData01[0x3];                                       // 0x0551(0x0003) MISSED OFFSET
		struct FGuid                                       Id;                                                       // 0x0554(0x0010) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData02[0x4];                                       // 0x0564(0x0004) MISSED OFFSET
		TArray<struct FPlayerStat>                         HandInPlayerStats;                                        // 0x0568(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FPlayerStat>                         HandInStolenPlayerStats;                                  // 0x0578(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FPlayerStat>                         HandInGiftPlayerStats;                                    // 0x0588(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FPlayerStat>                         HandInAsPirateLegendPlayerStats;                          // 0x0598(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FPlayerStat>                         HandInOnSchedulePlayerStats;                              // 0x05A8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FPlayerStat>                         HandInAsPirateLegendOnSchedulePlayerStats;                // 0x05B8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FEmissaryBootyItemStats>             HandInAsEmissaryPlayerStats;                              // 0x05C8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FEmissaryBootyItemStats>             HandInAsMaxLevelEmissaryPlayerStats;                      // 0x05D8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FEmissaryBootyItemStats>             HandInStolenAsEmissaryPlayerStats;                        // 0x05E8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FEmissaryBootyItemStats>             HandInStolenAsMaxLevelEmissaryPlayerStats;                // 0x05F8(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FPlayerStat>                         UsePlayerStats;                                           // 0x0608(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		TArray<struct FPlayerStat>                         UseStolenPlayerStats;                                     // 0x0618(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		struct FCompanyBootyStatList                       CompanySpecificStats;                                     // 0x0628(0x0010) (Edit, DisableEditOnInstance)
		class UPopUpMessageDesc* DiscoveredPopupDesc;                                      // 0x0638(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		struct FBootyItemSellPrerequisites                 SellPrerequisites;                                        // 0x0640(0x0010) (Edit, DisableEditOnInstance)
		class UTrackedOwnerComponent* TrackedOwnerComponent;                                    // 0x0650(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
		class UItemQualityComponent* ItemQualityComponent;                                     // 0x0658(0x0008) (Edit, ExportObject, ZeroConstructor, EditConst, InstancedReference, IsPlainOldData)
		TEnumAsByte<EEmissaryQualityLevel>                 ItemQualityLevel;                                         // 0x0660(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, EditConst, IsPlainOldData)
		unsigned char                                      UnknownData03[0x7];                                       // 0x0661(0x0007) MISSED OFFSET
		TArray<struct FPerComanyItemQualityEntry>          CompanySpecificItemQualityLevel;                          // 0x0668(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance, EditConst)
		struct FRewardId                                   HandInRewardId;                                           // 0x0678(0x0008) (Edit, DisableEditOnInstance)
		TArray<struct FCompanySpecificBootyReward>         HandInRewardIdCompanySpecific;                            // 0x0680(0x0010) (Edit, ZeroConstructor, DisableEditOnInstance)
		bool                                               RewardToOwnCrewOnly;                                      // 0x0690(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		unsigned char                                      UnknownData04[0x3];                                       // 0x0691(0x0003) MISSED OFFSET
		struct FName                                       Rarity;                                                   // 0x0694(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		unsigned char                                      UnknownData05[0x1C];                                      // 0x069C(0x001C) MISSED OFFSET
		class UDeliverableComponent* DeliverableComponent;                                     // 0x06B8(0x0008) (Edit, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
		class UCrewOwnershipTrackingComponent* CrewOwnershipTrackingComponent;                           // 0x06C0(0x0008) (Edit, ExportObject, Net, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
		TEnumAsByte<ESpawnedItemSource>                    SpawnSource;                                              // 0x06C8(0x0001) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData06[0x5F];                                      // 0x06C9(0x005F) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.BootyItemInfo");
			return ptr;
		}

	};

	// Class AthenaAI.AIDioramaCategory
	// 0x0000 (0x0028 - 0x0028)
	class UAIDioramaCategory : public UObject
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AIDioramaCategory");
			return ptr;
		}

	};

	// ScriptStruct Athena.ItemSpawnParams
	// 0x0028
	struct FItemSpawnParams
	{
		struct FWeightedProbabilityRange                   Total;                                                    // 0x0000(0x0020) (Edit)
		float                                              AllowedAngleDeviation;                                    // 0x0020(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              MaxZ;                                                     // 0x0024(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	};

	// ScriptStruct Athena.ItemSpawnWeightedType
	// 0x0028
	struct FItemSpawnWeightedType
	{
		class UClass* Type;                                                     // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		struct FName                                       Feature;                                                  // 0x0008(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		int                                                Weight;                                                   // 0x0010(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x4];                                       // 0x0014(0x0004) MISSED OFFSET
		TArray<class USpawnRequirement*>                   Requirements;                                             // 0x0018(0x0010) (Edit, ExportObject, ZeroConstructor)
	};

	// ScriptStruct Athena.ItemSpawnDistribution
	// 0x0010
	struct FItemSpawnDistribution
	{
		TArray<struct FItemSpawnWeightedType>              WeightedList;                                             // 0x0000(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	};

	// Class Athena.ItemSpawnComponent
	// 0x01A0 (0x0430 - 0x0290)
	class UItemSpawnComponent : public USceneComponent
	{
	public:
		struct FItemSpawnParams                            SpawnParams;                                              // 0x0290(0x0028) (Edit)
		class UWeightedItemDescSpawnDataAsset* ReferencedSpawnDistributionAsset;                         // 0x02B8(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		class UItemSpawnDistributionAsset* ReferencedSpawnDistribution;                              // 0x02C0(0x0008) (ZeroConstructor, IsPlainOldData)
		struct FItemSpawnDistribution                      SpawnDistribution;                                        // 0x02C8(0x0010)
		TArray<struct FItemSpawnTransform>                 SpawnTransforms;                                          // 0x02D8(0x0010) (Edit, ZeroConstructor)
		struct FName                                       FeatureToggle;                                            // 0x02E8(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		TEnumAsByte<ESpawnedItemSource>                    SpawnSource;                                              // 0x02F0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x3];                                       // 0x02F1(0x0003) MISSED OFFSET
		float                                              SpawnRate;                                                // 0x02F4(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               DestroyProxiesOnEndPlay;                                  // 0x02F8(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               SpawnWithPhysicsEnabled;                                  // 0x02F9(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               DoNotAttachToOwnerWhenSpawned;                            // 0x02FA(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               DropItemsOnSpawn;                                         // 0x02FB(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               DropItemsUsingPriorityAIDropParams;                       // 0x02FC(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData01[0xB];                                       // 0x02FD(0x000B) MISSED OFFSET
		TArray<struct FSpawnInstance>                      SpawnList;                                                // 0x0308(0x0010) (ZeroConstructor)
		TArray<struct FSpawnInstance>                      SingleItemInstances;                                      // 0x0318(0x0010) (ZeroConstructor)
		unsigned char                                      UnknownData02[0x10];                                      // 0x0328(0x0010) MISSED OFFSET
		TArray<struct FSpawnedItem>                        SpawnedItems;                                             // 0x0338(0x0010) (ZeroConstructor)
		unsigned char                                      UnknownData03[0x8];                                       // 0x0348(0x0008) MISSED OFFSET
		TArray<class ACluster*>                            Clusters;                                                 // 0x0350(0x0010) (ZeroConstructor, Transient)
		int                                                NumberOfInteractablesToSpawn;                             // 0x0360(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
		unsigned char                                      UnknownData04[0xCC];                                      // 0x0364(0x00CC) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.ItemSpawnComponent");
			return ptr;
		}

	};

	// Class AIModule.EnvQueryContext
	// 0x0000 (0x0028 - 0x0028)
	class UEnvQueryContext : public UObject
	{
	public:

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AIModule.EnvQueryContext");
			return ptr;
		}

	};

	// Class AthenaAI.EnvQueryContext_PositionFromBlackboard
	// 0x0008 (0x0030 - 0x0028)
	class UEnvQueryContext_PositionFromBlackboard : public UEnvQueryContext
	{
	public:
		unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.EnvQueryContext_PositionFromBlackboard");
			return ptr;
		}

	};

	// Class AthenaInput.CompositeInputHandler
	// 0x00B0 (0x00D8 - 0x0028)
	class UCompositeInputHandler : public UObject
	{
	public:
		unsigned char                                      UnknownData00[0xB0];                                      // 0x0028(0x00B0) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaInput.CompositeInputHandler");
			return ptr;
		}


		void SetNotificationInputHandler(class UClass* Id, const struct FScriptDelegate& Handler);
		void SetAnalogInputHandler(class UClass* Id, const struct FScriptDelegate& Handler);
	};

	// Class Athena.LookAtOffsetCompositeInputHandler
	// 0x0048 (0x0120 - 0x00D8)
	class ULookAtOffsetCompositeInputHandler : public UCompositeInputHandler
	{
	public:
		class AActor* Controller;                                               // 0x00D8(0x0008) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x40];                                      // 0x00E0(0x0040) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.LookAtOffsetCompositeInputHandler");
			return ptr;
		}


		TEnumAsByte<EInputHandlerResult> OnYawRate(float Value);
		TEnumAsByte<EInputHandlerResult> OnYaw(float Value);
		TEnumAsByte<EInputHandlerResult> OnPitchRate(float Value);
		TEnumAsByte<EInputHandlerResult> OnPitch(float Value);
	};


	// Class Athena.VoteConsumerInlineBase
	// 0x0008 (0x0030 - 0x0028)
	class UVoteConsumerInlineBase : public UObject
	{
	public:
		unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.VoteConsumerInlineBase");
			return ptr;
		}

	};

	// Class Athena.VoteValidatorInlineBase
	// 0x0008 (0x0030 - 0x0028)
	class UVoteValidatorInlineBase : public UObject
	{
	public:
		unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.VoteValidatorInlineBase");
			return ptr;
		}

	};

	// Class Athena.InteractableBase
	// 0x0028 (0x0438 - 0x0410)
	class AInteractableBase : public AActor
	{
	public:
		unsigned char                                      UnknownData00[0x10];                                      // 0x0410(0x0010) MISSED OFFSET
		bool                                               RequiresFacingFront;                                      // 0x0420(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		bool                                               RequiresNotBeingAirborne;                                 // 0x0421(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		bool                                               RequiresNotSwimming;                                      // 0x0422(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               InteractionsCanBeDisabled;                                // 0x0423(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		bool                                               CanSetInteractionState;                                   // 0x0424(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData01[0x3];                                       // 0x0425(0x0003) MISSED OFFSET
		class UActionRulesComponent* ActionRulesComponent;                                     // 0x0428(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
		TEnumAsByte<EInteractableIdentifier>               InteractableIdentifier;                                   // 0x0430(0x0001) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData02[0x1];                                       // 0x0431(0x0001) MISSED OFFSET
		TEnumAsByte<EInteractableState>                    CurrentInteractionState;                                  // 0x0432(0x0001) (ZeroConstructor, Transient, IsPlainOldData)
		unsigned char                                      UnknownData03[0x5];                                       // 0x0433(0x0005) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.InteractableBase");
			return ptr;
		}

	};

	// Class AthenaAI.AthenaAIController
	// 0x02D8 (0x0930 - 0x0658)
	class AAthenaAIController : public AAthenaAIControllerBase
	{
	public:
		unsigned char                                      UnknownData00[0x24];                                      // 0x0658(0x0024) MISSED OFFSET
		float                                              CurrentTargetPerceivedNotVisibleAge;                      // 0x067C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData01[0x40];                                      // 0x0680(0x0040) MISSED OFFSET
		class UAISenseConfig_Sight* SightConfig;                                              // 0x06C0(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		class UAISenseConfig_Hearing* HearingConfig;                                            // 0x06C8(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		class UAISenseConfig_Damage* DamageSenseConfig;                                        // 0x06D0(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData02[0x48];                                      // 0x06D8(0x0048) MISSED OFFSET
		TArray<struct FAthenaAIControllerSenseSettingOverride> AIStrategySenseSettingOverrides;                          // 0x0720(0x0010) (ZeroConstructor)
		unsigned char                                      UnknownData03[0x1D8];                                     // 0x0730(0x01D8) MISSED OFFSET
		class AActor* CurrentNotSeenPerceivedActor;                             // 0x0908(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
		class AActor* PendingSpawnTriggerActor;                                 // 0x0910(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
		unsigned char                                      UnknownData04[0x18];                                      // 0x0918(0x0018) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AthenaAIController");
			return ptr;
		}


		void StopBehaviourLogic();
		void SetPerceptionExpirationAgeForActor(class AActor* Actor, float ExpirationAge, class UClass* Sense);
		void RegisterSpawnTriggerActorAsStimulus(class AActor* TriggerActor);
		void OnPerceptionUpdated(TArray<class AActor*> ChangedPerceivedActors);
		void OnNewlySpawned();
		void OnFinishDespawn();
		bool IsActorPerceived(class AActor* TargetActor);
		class AActor* GetTargetActor();
		class UAthenaAIPerceptionComponent* GetAthenaAIPerceptionComponent();
		void GetAllSeenActors(TArray<class AActor*>* SeenActors);
		void ApplyControllerParams(class UAthenaAIControllerParamsDataAsset* ParamsAsset, class APawn* InPawn);
	};

	// ScriptStruct AthenaAI.AIEncounterSpecification
	// 0x00C8
	struct FAIEncounterSpecification
	{
		TAssetPtr<class UClass>                            PawnClass;                                                // 0x0000(0x0020) (Edit, BlueprintVisible, BlueprintReadOnly)
		class UAthenaAIControllerParamsDataAsset* Skillset;                                                 // 0x0020(0x0008) (ZeroConstructor, IsPlainOldData)
		class ULoadoutAsset* Loadout;                                                  // 0x0028(0x0008) (ZeroConstructor, IsPlainOldData)
		class UAthenaAIFormDataAsset* Form;                                                     // 0x0030(0x0008) (ZeroConstructor, IsPlainOldData)
		class UAthenaAIAmmoDataAsset* Ammo;                                                     // 0x0038(0x0008) (ZeroConstructor, IsPlainOldData)
		class UClass* AIClass;                                                  // 0x0040(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, EditConst, IsPlainOldData)
		class UAIPartsCategory* PartsCategory;                                            // 0x0048(0x0008) (ZeroConstructor, IsPlainOldData)
		TAssetPtr<class UClass>                            ItemDropComponentClass;                                   // 0x0050(0x0020)
		int                                                TeamColorIndex;                                           // 0x0070(0x0004) (ZeroConstructor, IsPlainOldData)
		struct FName                                       DioramaRole;                                              // 0x0074(0x0008) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x4];                                       // 0x007C(0x0004) MISSED OFFSET
		struct FText                                       LocalisableName;                                          // 0x0080(0x0018)
		unsigned char                                      UnknownData01[0x20];                                      // 0x007C(0x0020) FIX WRONG TYPE SIZE OF PREVIOUS PROPERTY
		struct FEncounterParams                            EncounterTrackingParams;                                  // 0x00B8(0x000C)
		bool                                               ShowNameplate;                                            // 0x00C4(0x0001) (ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData02[0x3];                                       // 0x00C5(0x0003) MISSED OFFSET
	};

	// ScriptStruct Athena.StandardAnchorDynamicsParameters
	// 0x0028
	struct FStandardAnchorDynamicsParameters
	{
		float                                              AnchorForce;                                              // 0x0000(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              VelocityDeadZoneThreshold;                                // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		class UCurveFloat* UnaryWheelAngleBasedTorque;                               // 0x0008(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		class UCurveFloat* ForwardSpeedBasedTorque;                                  // 0x0010(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              BaseHandbrakeTorque;                                      // 0x0018(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              TimeAfterAnchorDownToGrabWantedYaw;                       // 0x001C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		class UCurveFloat* YawDeltaVsCorrectiveTorquePerKgMass;                      // 0x0020(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	};

	// ScriptStruct AthenaAI.TinySharkWorldSettingsParams
	// 0x0001
	struct FTinySharkWorldSettingsParams
	{
		bool                                               TinySharkEnabled;                                         // 0x0000(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	};

	// ScriptStruct Athena.CompanySpecificBootyReward
// 0x0018
	struct FCompanySpecificBootyReward
	{
		class UClass* CompanyId;                                                // 0x0000(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		struct FRewardId                                   RewardId;                                                 // 0x0008(0x0008) (Edit, DisableEditOnInstance)
		bool                                               RequirePirateLegend;                                      // 0x0010(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		unsigned char                                      UnknownData00[0x7];                                       // 0x0011(0x0007) MISSED OFFSET
	};

	// ScriptStruct Athena.StartPickupObjectActionRuleParams
	// 0x0010
	struct FStartPickupObjectActionRuleParams
	{
		TArray<TEnumAsByte<EWieldableItemSize>>            WieldableItemSizesDisablePickup;                          // 0x0000(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	};

	// ScriptStruct Athena.PetAnimationDataPreview
	// 0x0010
	struct FPetAnimationDataPreview
	{
		struct FStringAssetReference                       MontageData;                                              // 0x0000(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	};

	// ScriptStruct Athena.GhostPlayModeParameters
	// 0x000C
	struct FGhostPlayModeParameters
	{
		TEnumAsByte<EPlayMode>                             PlayMode;                                                 // 0x0000(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		unsigned char                                      UnknownData00[0x3];                                       // 0x0001(0x0003) MISSED OFFSET
		float                                              RotationPerSecond;                                        // 0x0004(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		float                                              DisplacementPerSecond;                                    // 0x0008(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	};

	// ScriptStruct AthenaAI.AIBountySpawnerParams
	// 0x00A8
	struct FAIBountySpawnerParams
	{
		TArray<struct FAIEncounterWave>                    AISpawnerCreationDesc;                                    // 0x0000(0x0010) (ZeroConstructor)
		struct FStringAssetReference                       TeamColor;                                                // 0x0010(0x0010) (ZeroConstructor)
		TArray<int>                                        NumTargetsInWave;                                         // 0x0020(0x0010) (ZeroConstructor)
		TArray<int>                                        NumCaptainsInWave;                                        // 0x0030(0x0010) (ZeroConstructor)
		float                                              MinTimeBetweenSpawns;                                     // 0x0040(0x0004) (ZeroConstructor, IsPlainOldData)
		float                                              MaxTimeBetweenSpawns;                                     // 0x0044(0x0004) (ZeroConstructor, IsPlainOldData)
		float                                              MinTimeBetweenWaves;                                      // 0x0048(0x0004) (ZeroConstructor, IsPlainOldData)
		float                                              MaxTimeBetweenWaves;                                      // 0x004C(0x0004) (ZeroConstructor, IsPlainOldData)
		struct FWeightedProbabilityRange                   WavesPerRelocate;                                         // 0x0050(0x0020)
		struct FWeightedProbabilityRange                   WaveSplitChance;                                          // 0x0070(0x0020)
		TArray<float>                                      WaveSuicideTime;                                          // 0x0090(0x0010) (ZeroConstructor)
		float                                              WaveSuicideMinDist;                                       // 0x00A0(0x0004) (ZeroConstructor, IsPlainOldData)
		int                                                NumAdditionalWaves;                                       // 0x00A4(0x0004) (ZeroConstructor, IsPlainOldData)
	};

	// ScriptStruct AthenaAI.TargetSkillsetProgressionPair
	// 0x0020
	struct FTargetSkillsetProgressionPair
	{
		struct FStringAssetReference                       CrewSkillset;                                             // 0x0000(0x0010) (Edit, ZeroConstructor)
		struct FStringAssetReference                       CaptainSkillset;                                          // 0x0010(0x0010) (Edit, ZeroConstructor)
	};

	// ScriptStruct AthenaAI.AIAbilityDebugReplicatedIntervals
	// 0x000C
	struct FAIAbilityDebugReplicatedIntervals
	{
		float                                              ActivationTimerCooldown;                                  // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
		float                                              TimeBeforeNextExecution;                                  // 0x0004(0x0004) (ZeroConstructor, IsPlainOldData)
		float                                              DamageBeforeNextExecution;                                // 0x0008(0x0004) (ZeroConstructor, IsPlainOldData)
	};

	// ScriptStruct Athena.WeightedPetAnimationSelector
	// 0x00A0
	struct FWeightedPetAnimationSelector
	{
		TArray<struct FPetAnimationWeighting>              Weightings;                                               // 0x0000(0x0010) (Edit, ZeroConstructor)
		unsigned char                                      UnknownData00[0x90];                                      // 0x0010(0x0090) MISSED OFFSET
	};

	// Class AthenaAI.AthenaAIFormDataAsset
	// 0x0070 (0x0098 - 0x0028)
	class UAthenaAIFormDataAsset : public UDataAsset
	{
	public:
		TArray<TEnumAsByte<EHealthChangedReason>>          PreventHealthChangedReasons;                              // 0x0028(0x0010) (Edit, ZeroConstructor)
		TArray<struct FAIFormDamageResponse>               DamageResponses;                                          // 0x0038(0x0010) (Edit, ZeroConstructor)
		class UStatusRecipientResponseList* OverrideStatusRecipientResponseList;                      // 0x0048(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		class UPhysicalMaterial* SurfaceMaterial;                                          // 0x0050(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		class UObject* KilledVfxTemplate;                                        // 0x0058(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		class UClass* AICharacterAudioComponent;                                // 0x0060(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		class UClass* AnimNotifyEmitterWithObservers;                           // 0x0068(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		bool                                               HighPriorityFootstepAudio;                                // 0x0070(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		unsigned char                                      UnknownData00[0x3];                                       // 0x0071(0x0003) MISSED OFFSET
		float                                              MovementSpeedMultipler;                                   // 0x0074(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		struct FPlayerStat                                 StatToFireOnDeath;                                        // 0x0078(0x000C) (Edit, DisableEditOnInstance)
		struct FName                                       FeatureName;                                              // 0x0084(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData01[0x4];                                       // 0x008C(0x0004) MISSED OFFSET
		class UClass* FormComponentClass;                                       // 0x0090(0x0008) (Edit, ZeroConstructor, IsPlainOldData)

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AthenaAIFormDataAsset");
			return ptr;
		}

	};

	// ScriptStruct AthenaAI.AthenaAIControllerSenseSettings
	// 0x0014
	struct FAthenaAIControllerSenseSettings
	{
		bool                                               EnableSight;                                              // 0x0000(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               EnableHearing;                                            // 0x0001(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               EnableDamage;                                             // 0x0002(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x1];                                       // 0x0003(0x0001) MISSED OFFSET
		float                                              SightRadius;                                              // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              LoseSightRadius;                                          // 0x0008(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              PeripheralVisionAngleDegrees;                             // 0x000C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              MaxHearingRange;                                          // 0x0010(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	};

	// ScriptStruct AthenaAI.AthenaAIControllerDamageTargetScoreFromPerceivedTarget
	// 0x0014
	struct FAthenaAIControllerDamageTargetScoreFromPerceivedTarget
	{
		float                                              MinDamageTargetScore;                                     // 0x0000(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              MaxDamageTargetScore;                                     // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              DamageForMinDamageTargetScore;                            // 0x0008(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              DamageForMaxDamageTargetScore;                            // 0x000C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              RateToDecayDamagedFromTarget;                             // 0x0010(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	};

	// ScriptStruct AthenaAI.AthenaAIControllerHealthCustomisation
	// 0x000C
	struct FAthenaAIControllerHealthCustomisation
	{
		bool                                               OverrideMaxHealth;                                        // 0x0000(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               OverrideMaxHealthWithMinMax;                              // 0x0001(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x2];                                       // 0x0002(0x0002) MISSED OFFSET
		float                                              MinHealth;                                                // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              MaxHealth;                                                // 0x0008(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	};

	// Class AthenaAI.AthenaAIControllerParamsDataAsset
	// 0x00D8 (0x0100 - 0x0028)
	class UAthenaAIControllerParamsDataAsset : public UDataAsset
	{
	public:
		struct FAthenaAIControllerSenseSettings            DefaultSenseSettings;                                     // 0x0028(0x0014) (Edit)
		float                                              AutoSuccessRangeFromLastSeenLocation;                     // 0x003C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              DefaultPerceivedNotVisibleAge;                            // 0x0040(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               OverrideTeamID;                                           // 0x0044(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		TEnumAsByte<EAthenaAITeam>                         TeamID;                                                   // 0x0045(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x2];                                       // 0x0046(0x0002) MISSED OFFSET
		float                                              TargetSwitchScoreTolerance;                               // 0x0048(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData01[0x4];                                       // 0x004C(0x0004) MISSED OFFSET
		TArray<float>                                      TargetLoadWeightingBias;                                  // 0x0050(0x0010) (Edit, ZeroConstructor)
		float                                              DistanceToStartTargetPickingDecrease;                     // 0x0060(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              TargetPickingDistScoreAtMaxSightRange;                    // 0x0064(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              VisionAngleToStartTargetPickingDecrease;                  // 0x0068(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              TargetPickingFacingScoreAtMaxPeripheralVisionAngle;       // 0x006C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		bool                                               UseDamageAsFactorInTargetScore;                           // 0x0070(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData02[0x3];                                       // 0x0071(0x0003) MISSED OFFSET
		struct FAthenaAIControllerDamageTargetScoreFromPerceivedTarget DamageTargetScores;                                       // 0x0074(0x0014) (Edit)
		TArray<class UAthenaAIControllerSharedParamValuesDataAsset*> SharedParamValues;                                        // 0x0088(0x0010) (Edit, ZeroConstructor)
		bool                                               IndividualOverrideMeshScale;                              // 0x0098(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData03[0x3];                                       // 0x0099(0x0003) MISSED OFFSET
		float                                              IndividualMeshScale;                                      // 0x009C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		struct FAthenaAIControllerHealthCustomisation      IndividualHealthCustomisationValues;                      // 0x00A0(0x000C) (Edit)
		unsigned char                                      UnknownData04[0x4];                                       // 0x00AC(0x0004) MISSED OFFSET
		TArray<struct FAthenaAIControllerParamValue>       IndividualInitialBlackboardValues;                        // 0x00B0(0x0010) (Edit, ZeroConstructor)
		TArray<struct FAthenaAIControllerParamValue>       IndividualNamedControllerParams;                          // 0x00C0(0x0010) (Edit, ZeroConstructor)
		TArray<struct FAthenaAIControllerWeightedRangesParamValue> IndividualNamedWeightedRangesControllerParams;            // 0x00D0(0x0010) (Edit, ZeroConstructor)
		TArray<struct FAthenaAIControllerSenseSettingOverride> IndividualAIStrategySenseSettingOverrides;                // 0x00E0(0x0010) (Edit, ZeroConstructor)
		bool                                               IndividualOverrideCurrentTargetPerceivedNotVisibleAge;    // 0x00F0(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData05[0x3];                                       // 0x00F1(0x0003) MISSED OFFSET
		float                                              IndividualCurrentTargetPerceivedNotVisibleAge;            // 0x00F4(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		struct FName                                       FeatureName;                                              // 0x00F8(0x0008) (Edit, ZeroConstructor, IsPlainOldData)

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class AthenaAI.AthenaAIControllerParamsDataAsset");
			return ptr;
		}

	};

	// ScriptStruct Athena.QuestVariableName
	// 0x0000 (0x0010 - 0x0010)
	struct FQuestVariableName : public FQuestVariable
	{

	};

	// ScriptStruct Athena.QuestVariableVector
	// 0x0000 (0x0010 - 0x0010)
	struct FQuestVariableVector : public FQuestVariable
	{

	};

	// ScriptStruct Athena.QuestVariableActor
	// 0x0000 (0x0010 - 0x0010)
	struct FQuestVariableActor : public FQuestVariable
	{

	};

	// ScriptStruct Athena.QuestVariableInt
	// 0x0000 (0x0010 - 0x0010)
	struct FQuestVariableInt : public FQuestVariable
	{

	};

	// ScriptStruct Athena.DamageInstance
	// 0x0028
	struct FDamageInstance
	{
		struct FGuid                                       AttackId;                                                 // 0x0000(0x0010) (ZeroConstructor, IsPlainOldData)
		class AActor* DirectInstigator;                                         // 0x0010(0x0008) (ZeroConstructor, IsPlainOldData)
		class AActor* RootInstigator;                                           // 0x0018(0x0008) (ZeroConstructor, IsPlainOldData)
		float                                              Amount;                                                   // 0x0020(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
		TEnumAsByte<EHealthChangedReason>                  Reason;                                                   // 0x0024(0x0001) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
		unsigned char                                      UnknownData00[0x3];                                       // 0x0025(0x0003) MISSED OFFSET
	};

	// ScriptStruct AthenaAI.AIStrategyMovementProperties
	// 0x0018
	struct FAIStrategyMovementProperties
	{
		class UClass* AIStrategy;                                               // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              MaxSpeedAmp;                                              // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              MaxAccelAmp;                                              // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
		float                                              OverrideRVOAvoidanceRadius;                               // 0x0010(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
		float                                              OverrideBlendSpeed;                                       // 0x0014(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	};

	// Class Athena.DitherComponent
	// 0x00E0 (0x01A8 - 0x00C8)
	class UDitherComponent : public UActorComponent
	{
	public:
		unsigned char                                      UnknownData00[0x8];                                       // 0x00C8(0x0008) MISSED OFFSET
		bool                                               FindMeshOnOwner;                                          // 0x00D0(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		unsigned char                                      UnknownData01[0x3];                                       // 0x00D1(0x0003) MISSED OFFSET
		float                                              FadeTime;                                                 // 0x00D4(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
		unsigned char                                      UnknownData02[0x10];                                      // 0x00D8(0x0010) MISSED OFFSET
		TMap<class UMeshComponent*, struct FDynamicMaterialsList> DynamicMaterialsPerMeshComponent;                         // 0x00E8(0x0050) (ZeroConstructor, Transient)
		unsigned char                                      UnknownData03[0x70];                                      // 0x0138(0x0070) MISSED OFFSET

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindClass("Class Athena.DitherComponent");
			return ptr;
		}


		void SetCurrentTransparency(float Val);
		void FadeOut();
		void FadeIn();
	};

	// ScriptStruct Athena.PartDesc
	// 0x0020
	struct FPartDesc
	{
		struct FString                                     Name;                                                     // 0x0000(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
		TArray<struct FPartCustomisation>                  Customisations;                                           // 0x0010(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	};

	// ScriptStruct Athena.QuestVariableTextArray
	// 0x0000 (0x0010 - 0x0010)
	struct FQuestVariableTextArray : public FQuestVariable
	{

	};

	// ScriptStruct Athena.QuestVariableText
	// 0x0000 (0x0010 - 0x0010)
	struct FQuestVariableText : public FQuestVariable
	{

	};

	// ScriptStruct Athena.QuestVariableGuid
	// 0x0000 (0x0010 - 0x0010)
	struct FQuestVariableGuid : public FQuestVariable
	{

	};
}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif