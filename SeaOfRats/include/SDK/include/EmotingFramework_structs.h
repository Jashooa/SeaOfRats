#pragma once

// Sea of Thieves (2.4.1) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "Basic_classes.h"
#include "EmotingFramework_enums.h"
#include "Engine_classes.h"
#include "CoreUObject_classes.h"
#include "AthenaInput_classes.h"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct EmotingFramework.EmoteId
// 0x0008
struct FEmoteId
{
	struct FName                                       EmoteId;                                                  // 0x0000(0x0008) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct EmotingFramework.EmoteData
// 0x0098
struct FEmoteData
{
	struct FEmoteId                                    EmoteId;                                                  // 0x0000(0x0008) (Edit, BlueprintVisible, BlueprintReadOnly)
	struct FText                                       EmoteDisplayName;                                         // 0x0008(0x0038) (Edit)
	struct FText                                       AudioDescription;                                         // 0x0040(0x0038) (Edit)
	float                                              DelayBeforeAllowingExit;                                  // 0x0078(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              VerticalOffsetFactorWhenZoomed;                           // 0x007C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               HideNameplate;                                            // 0x0080(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0081(0x0007) MISSED OFFSET
	class UEmotePropData*                              EmotePropDataAsset;                                       // 0x0088(0x0008) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               CanPlayInSuccession;                                      // 0x0090(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	bool                                               ShowDescriptionInTextChat;                                // 0x0091(0x0001) (Edit, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x0092(0x0006) MISSED OFFSET
};

// ScriptStruct EmotingFramework.EventEmoteEndRequested
// 0x000C
struct FEventEmoteEndRequested
{
	struct FName                                       EmoteIdentifier;                                          // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	bool                                               EndForcedEmote;                                           // 0x0008(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0009(0x0003) MISSED OFFSET
};

// ScriptStruct EmotingFramework.EventEndEmoteAnimation
// 0x0001
struct FEventEndEmoteAnimation
{
	unsigned char                                      UnknownData00[0x1];                                       // 0x0000(0x0001) MISSED OFFSET
};

// ScriptStruct EmotingFramework.EventEmoteSwapped
// 0x0098
struct FEventEmoteSwapped
{
	struct FEmoteData                                  EmoteData;                                                // 0x0000(0x0098)
};

// ScriptStruct EmotingFramework.EventEmoteCompleted
// 0x000C
struct FEventEmoteCompleted
{
	struct FName                                       EmoteName;                                                // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
	uint32_t                                           EmoteDuration;                                            // 0x0008(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct EmotingFramework.EventEmoteStarted
// 0x0098
struct FEventEmoteStarted
{
	struct FEmoteData                                  EmoteData;                                                // 0x0000(0x0098) (BlueprintVisible, BlueprintReadOnly)
};

// ScriptStruct EmotingFramework.EventEmoteRequested
// 0x00A8
struct FEventEmoteRequested
{
	struct FEmoteData                                  EmoteData;                                                // 0x0000(0x0098)
	struct FName                                       ForcedEmoteIdentifier;                                    // 0x0098(0x0008) (ZeroConstructor, IsPlainOldData)
	bool                                               ForcedEmote;                                              // 0x00A0(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x00A1(0x0007) MISSED OFFSET
};

// ScriptStruct EmotingFramework.EmoteDiceOutcomeTelemetryEvent
// 0x0014
struct FEmoteDiceOutcomeTelemetryEvent
{
	int                                                MaxLimit;                                                 // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                RollNumber;                                               // 0x0004(0x0004) (ZeroConstructor, IsPlainOldData)
	struct FVector                                     OrientationUsed;                                          // 0x0008(0x000C) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct EmotingFramework.EventDisableLookAtEmoteCamera
// 0x0001
struct FEventDisableLookAtEmoteCamera
{
	unsigned char                                      UnknownData00[0x1];                                       // 0x0000(0x0001) MISSED OFFSET
};

// ScriptStruct EmotingFramework.EventEnableLookAtEmoteCamera
// 0x0008
struct FEventEnableLookAtEmoteCamera
{
	TWeakObjectPtr<class AActor>                       LookAtTarget;                                             // 0x0000(0x0008) (ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
