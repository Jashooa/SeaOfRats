#pragma once

namespace SDK
{
	// Class PirateGenerator.ColorTexture
	// 0x0010 (0x0148 - 0x0138)
	class UColorTexture : public UTexture
	{
	public:
		struct FLinearColor Color; // 0x0138(0x0010)
	};
}
