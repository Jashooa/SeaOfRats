#pragma once

// Sea of Thieves (2.4.1) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "Basic_classes.h"
#include "Engine_classes.h"
#include "CoreUObject_classes.h"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct RemoteActorDestruction.DestroyActorData
// 0x0004
struct FDestroyActorData
{
	int                                                ActorNetID;                                               // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct RemoteActorDestruction.DestroyAllExistingActorsByClassData
// 0x0010
struct FDestroyAllExistingActorsByClassData
{
	TArray<class FString>                              ActorClassNames;                                          // 0x0000(0x0010) (ZeroConstructor)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
