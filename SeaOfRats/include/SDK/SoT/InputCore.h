#pragma once

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

namespace SDK
{
	// ScriptStruct InputCore.Key
	// 0x0020
	struct FKey
	{
		FName KeyName; // 0x0000(0x0008)
		char pad_0x0008[0x0018];
	};
}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
