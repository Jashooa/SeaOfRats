#pragma once

// Sea of Thieves (2.0.16) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum Sessions.ESessionGrouping
enum class ESessionGrouping : uint8_t
{
	ESessionGrouping__Invalid      = 0,
	ESessionGrouping__Default      = 1,
	ESessionGrouping__MediumLargeShip = 2,
	ESessionGrouping__ESessionGrouping_MAX = 3
};


// Enum Sessions.ECrewSessionType
enum class ECrewSessionType : uint8_t
{
	ECrewSessionType__Invalid      = 0,
	ECrewSessionType__SmallShip    = 1,
	ECrewSessionType__MediumShip   = 2,
	ECrewSessionType__LargeShip    = 3,
	ECrewSessionType__ServerLarge  = 4,
	ECrewSessionType__SloopSolo    = 5,
	ECrewSessionType__Lobby        = 6,
	ECrewSessionType__ECrewSessionType_MAX = 7
};


// Enum Sessions.ESessionVisibility
enum class ESessionVisibility : uint8_t
{
	ESessionVisibility__Invalid    = 0,
	ESessionVisibility__Open       = 1,
	ESessionVisibility__Closed     = 2,
	ESessionVisibility__ESessionVisibility_MAX = 3
};



}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
