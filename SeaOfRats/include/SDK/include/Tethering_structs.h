#pragma once

// Sea of Thieves (2.4.1) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "Basic_classes.h"
#include "Tethering_enums.h"
#include "Engine_classes.h"
#include "CoreUObject_classes.h"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct Tethering.TetherProjectileImpact
// 0x0008
struct FTetherProjectileImpact
{
	class AActor*                                      HitActor;                                                 // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
