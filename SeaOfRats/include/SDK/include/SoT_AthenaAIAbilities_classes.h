#pragma once

// Sea of Thieves (2.0.16) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SoT_AthenaAIAbilities_structs.h"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class AthenaAIAbilities.AshenFireStatus
// 0x0000 (0x0028 - 0x0028)
class UAshenFireStatus : public UStatusBase
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass(_xor_("Class AthenaAIAbilities.AshenFireStatus"));
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
