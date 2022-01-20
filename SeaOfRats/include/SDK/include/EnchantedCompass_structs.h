#pragma once

// Sea of Thieves (2.4.1) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "Basic_classes.h"
#include "EnchantedCompass_enums.h"
#include "CoreUObject_classes.h"
#include "Engine_classes.h"
#include "Athena_classes.h"
#include "Tales_classes.h"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct EnchantedCompass.CompassTargetSet
// 0x000C
struct FCompassTargetSet
{
	struct FVector                                     TargetLocation;                                           // 0x0000(0x000C) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
