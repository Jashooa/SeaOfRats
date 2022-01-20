#pragma once

// Sea of Thieves (2.4.0) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "Basic.h"
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

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
