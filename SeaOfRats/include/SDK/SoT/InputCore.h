#pragma once

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
