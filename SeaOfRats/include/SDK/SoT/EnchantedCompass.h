#pragma once

namespace SDK
{
	// Class EnchantedCompass.MultiTargetEnchantedCompass
	// 0x0030 (0x08A0 - 0x0870)
	class AMultiTargetEnchantedCompass : public ACompass
	{
	public:
		TArray<struct FVector> Locations; // 0x0870(0x0010)
		char pad_0x00880[0x0020];

		static UClass* StaticClass()
		{
			static auto ptr = UObject::FindObject<UClass>("Class EnchantedCompass.MultiTargetEnchantedCompass");
			return ptr;
		}
	};
}
