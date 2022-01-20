#pragma once

// Sea of Thieves (2.4.0) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "Basic.h"
#include "InputCore_enums.h"
#include "CoreUObject_classes.h"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct InputCore.Key
// 0x0020
struct FKey
{
	struct FName                                       KeyName;                                                  // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x18];                                      // 0x0008(0x0018) MISSED OFFSET
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
