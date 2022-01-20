#pragma once

// Sea of Thieves (2.4.0) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "Basic_classes.h"
#include "NetworkRegions_enums.h"
#include "Engine_classes.h"
#include "CoreUObject_classes.h"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct NetworkRegions.RegionAssetsList
// 0x0018
struct FRegionAssetsList
{
	TEnumAsByte<ENetworkRegion>                        Region;                                                   // 0x0000(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0001(0x0007) MISSED OFFSET
	TArray<struct FStringAssetReference>               CachedAssetsForRegion;                                    // 0x0008(0x0010) (ZeroConstructor)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
