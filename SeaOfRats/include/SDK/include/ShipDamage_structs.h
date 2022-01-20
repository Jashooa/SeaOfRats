#pragma once

// Sea of Thieves (2.4.1) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "Basic_classes.h"
#include "ShipDamage_enums.h"
#include "CoreUObject_classes.h"
#include "Athena_classes.h"
#include "Repair_classes.h"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct ShipDamage.DistanceAndLevelOfDamage
// 0x0008
struct FDistanceAndLevelOfDamage
{
	float                                              DistanceLimit;                                            // 0x0000(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	int                                                LevelOfDamage;                                            // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct ShipDamage.ShipPartLevelsOfDamage
// 0x0030
struct FShipPartLevelsOfDamage
{
	TAssetPtr<class UClass>                            ActorClass;                                               // 0x0000(0x0020) (Edit)
	TArray<struct FDistanceAndLevelOfDamage>           DamagePerDistance;                                        // 0x0020(0x0010) (Edit, ZeroConstructor)
};

// ScriptStruct ShipDamage.ShipDamageParams
// 0x0010
struct FShipDamageParams
{
	TArray<struct FShipPartLevelsOfDamage>             DamageParams;                                             // 0x0000(0x0010) (Edit, ZeroConstructor)
};

// ScriptStruct ShipDamage.EventShipDamageApplied
// 0x0070
struct FEventShipDamageApplied
{
	class AActor*                                      Ship;                                                     // 0x0000(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FName                                       DamagedShipPartIdentifier;                                // 0x0008(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                NewDamageLevel;                                           // 0x0010(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0014(0x0004) MISSED OFFSET
	struct FImpactDamageEvent                          ImpactDamageEvent;                                        // 0x0018(0x0058) (BlueprintVisible)
};

// ScriptStruct ShipDamage.EventShipDamaged
// 0x0060
struct FEventShipDamaged
{
	class AActor*                                      Ship;                                                     // 0x0000(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FImpactDamageEvent                          ImpactDamageEvent;                                        // 0x0008(0x0058) (BlueprintVisible)
};

// ScriptStruct ShipDamage.DamageZoneDamageLevelChanged
// 0x0010
struct FDamageZoneDamageLevelChanged
{
	class AActor*                                      DamageZone;                                               // 0x0000(0x0008) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                DamageLevel;                                              // 0x0008(0x0004) (BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x000C(0x0004) MISSED OFFSET
};

// ScriptStruct ShipDamage.AppliedDamageToShipEvent
// 0x0010
struct FAppliedDamageToShipEvent
{
	class UClass*                                      ShipType;                                                 // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	class AActor*                                      Ship;                                                     // 0x0008(0x0008) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct ShipDamage.HullDamageHit
// 0x0024
struct FHullDamageHit
{
	struct FVector                                     HitPosition;                                              // 0x0000(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FVector                                     HitNormal;                                                // 0x000C(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              HitStrength;                                              // 0x0018(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                HitLevel;                                                 // 0x001C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               HasDecal;                                                 // 0x0020(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0021(0x0003) MISSED OFFSET
};

// ScriptStruct ShipDamage.HullDamageZoneInfo
// 0x0028
struct FHullDamageZoneInfo
{
	class FString                                      DamageZoneId;                                             // 0x0000(0x0010) (ZeroConstructor)
	int                                                DamageLevel;                                              // 0x0010(0x0004) (ZeroConstructor, IsPlainOldData)
	TEnumAsByte<ERepairableState>                      RepairableState;                                          // 0x0014(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0015(0x0003) MISSED OFFSET
	TArray<struct FHullDamageHit>                      ExternalHitList;                                          // 0x0018(0x0010) (ZeroConstructor)
};

// ScriptStruct ShipDamage.HullDamagePersistenceModel
// 0x000F (0x0010 - 0x0001)
struct FHullDamagePersistenceModel : public FPersistenceModel
{
	TArray<struct FHullDamageZoneInfo>                 DamageZones;                                              // 0x0000(0x0010) (ZeroConstructor)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
