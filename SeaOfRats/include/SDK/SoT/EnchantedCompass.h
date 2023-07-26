#pragma once

namespace SDK
{
	// Class EnchantedCompass.MultiTargetEnchantedCompass
	// 0x0030 (0x0910 - 0x08E0)
	class AMultiTargetEnchantedCompass : public ACompass
	{
	public:
		char pad_0x08E0[0x0008];
		TArray<struct FGuid> LocationIds; // 0x08E8(0x0010)
		char pad_0x08F8[0x0018];

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindObject<UClass>("Class EnchantedCompass.MultiTargetEnchantedCompass");
			return ptr;
		}
	};
}
