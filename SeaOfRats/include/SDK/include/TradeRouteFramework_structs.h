#pragma once

// Sea of Thieves (2.4.1) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "Basic_classes.h"
#include "TradeRouteFramework_enums.h"
#include "Engine_classes.h"
#include "CoreUObject_classes.h"
#include "Athena_classes.h"
#include "Tales_classes.h"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct TradeRouteFramework.QuestVariableTradeRouteData
// 0x0000 (0x0010 - 0x0010)
struct FQuestVariableTradeRouteData : public FQuestVariable
{

};

// ScriptStruct TradeRouteFramework.TradeRouteMapping
// 0x0020
struct FTradeRouteMapping
{
	struct FIslandSelectionType                        StartIsland;                                              // 0x0000(0x0008) (Edit)
	class UClass*                                      DifficultyBand;                                           // 0x0008(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	struct FStringAssetReference                       TradeRouteReference;                                      // 0x0010(0x0010) (Edit, ZeroConstructor)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
