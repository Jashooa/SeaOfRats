#pragma once

// Sea of Thieves (2.4.0) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "Basic.h"
#include "CoreUObject_classes.h"
#include "Engine_classes.h"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct GameService.GameServiceMap
// 0x0070
struct FGameServiceMap
{
	unsigned char                                      UnknownData00[0x70];                                      // 0x0000(0x0070) MISSED OFFSET
};

// ScriptStruct GameService.GameServiceCoordinatorUnit
// 0x0018
struct FGameServiceCoordinatorUnit
{
	class UObject*                                     Service;                                                  // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0008(0x0010) MISSED OFFSET
};

// ScriptStruct GameService.GameServiceCoordinator
// 0x0020
struct FGameServiceCoordinator
{
	TArray<struct FGameServiceCoordinatorUnit>         Services;                                                 // 0x0000(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0010(0x0010) MISSED OFFSET
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
