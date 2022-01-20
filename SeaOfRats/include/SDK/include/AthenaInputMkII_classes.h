#pragma once

// Sea of Thieves (2.4.0) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "AthenaInputMkII_structs.h"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------



// Class AthenaInputMkII.MovementInterferenceComponent
// 0x0070 (0x01C0 - 0x0150)
class UMovementInterferenceComponent : public UInputComponent
{
public:
	unsigned char                                      UnknownData00[0x70];                                      // 0x0150(0x0070) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindObject<UClass>(_xor_("Class AthenaInputMkII.MovementInterferenceComponent"));
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
