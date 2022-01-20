#pragma once

// Sea of Thieves (2.4.1) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "Basic_classes.h"
#include "Tales_classes.h"
#include "Athena_classes.h"
#include "CoreUObject_classes.h"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct TaleMaps.TaleQuestVariableMapMarkType
// 0x0000 (0x0010 - 0x0010)
struct FTaleQuestVariableMapMarkType : public FQuestVariable
{

};

// ScriptStruct TaleMaps.TaleQuestChecklistItem
// 0x0050
struct FTaleQuestChecklistItem
{
	struct FText                                       Description;                                              // 0x0000(0x0038) (Edit, BlueprintVisible)
	int                                                NumCurrentCompletions;                                    // 0x0038(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int                                                NumRequiredCompletions;                                   // 0x003C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UTexture*                                    UnfulfilledIcon;                                          // 0x0040(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	class UTexture*                                    FulfilledIcon;                                            // 0x0048(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
