#pragma once

// Sea of Thieves (2.4.1) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "Basic_classes.h"
#include "AthenaAIAbilities_enums.h"
#include "Athena_classes.h"
#include "AthenaAI_classes.h"
#include "StatusEffects_classes.h"
#include "CoreUObject_classes.h"
#include "Engine_classes.h"
#include "Maths_classes.h"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct AthenaAIAbilities.MeleeAttackIdWeights
// 0x0010
struct FMeleeAttackIdWeights
{
	class UClass*                                      MeleeAttackType;                                          // 0x0000(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              Weight;                                                   // 0x0008(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x000C(0x0004) MISSED OFFSET
};

// ScriptStruct AthenaAIAbilities.AshenLordFireShroudParams
// 0x0018
struct FAshenLordFireShroudParams
{
	class UClass*                                      FireShroudZoneClass;                                      // 0x0000(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FVector                                     FireShroudCollisionVolume;                                // 0x0008(0x000C) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0014(0x0004) MISSED OFFSET
};

// ScriptStruct AthenaAIAbilities.AshenLordFireShroud
// 0x0020
struct FAshenLordFireShroud
{
	class AStatusEffectOverlapZone*                    FireShroudOverlapZone;                                    // 0x0000(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	struct FAshenLordFireShroudParams                  Params;                                                   // 0x0008(0x0018)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
