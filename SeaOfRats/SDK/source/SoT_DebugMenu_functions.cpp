// Sea of Thieves (2.0.16) SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SoT_DebugMenu_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function DebugMenu.DebugMenuTestFunctions.IsDebugMenuReady
// (Final, Native, Static, Public, BlueprintCallable, BlueprintPure)
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UDebugMenuTestFunctions::STATIC_IsDebugMenuReady(class UObject* WorldContextObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function DebugMenu.DebugMenuTestFunctions.IsDebugMenuReady");

	struct
	{
		class UObject*                 WorldContextObject;
		bool                           ReturnValue;
	} params;
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;
	fn->FunctionFlags |= 0x400;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function DebugMenu.DebugMenuTestFunctions.IsDebugMenuOpen
// (Final, Native, Static, Public, BlueprintCallable, BlueprintPure)
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UDebugMenuTestFunctions::STATIC_IsDebugMenuOpen(class UObject* WorldContextObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function DebugMenu.DebugMenuTestFunctions.IsDebugMenuOpen");

	struct
	{
		class UObject*                 WorldContextObject;
		bool                           ReturnValue;
	} params;
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;
	fn->FunctionFlags |= 0x400;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function DebugMenu.DebugMenuTestFunctions.IsDebugMenuAvailable
// (Final, Native, Static, Public, BlueprintCallable)
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UDebugMenuTestFunctions::STATIC_IsDebugMenuAvailable()
{
	static auto fn = UObject::FindObject<UFunction>("Function DebugMenu.DebugMenuTestFunctions.IsDebugMenuAvailable");

	struct
	{
		bool                           ReturnValue;
	} params;

	auto flags = fn->FunctionFlags;
	fn->FunctionFlags |= 0x400;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function DebugMenu.DebugMenuTestFunctions.GetDebugMenuToggleKeyComboBetaKeyboard
// (Final, Native, Static, Public, BlueprintCallable, BlueprintPure)
// Parameters:
// struct FKey                    ReturnValue                    (Parm, OutParm, ReturnParm)

struct FKey UDebugMenuTestFunctions::STATIC_GetDebugMenuToggleKeyComboBetaKeyboard()
{
	static auto fn = UObject::FindObject<UFunction>("Function DebugMenu.DebugMenuTestFunctions.GetDebugMenuToggleKeyComboBetaKeyboard");

	struct
	{
		struct FKey                    ReturnValue;
	} params;

	auto flags = fn->FunctionFlags;
	fn->FunctionFlags |= 0x400;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function DebugMenu.DebugMenuTestFunctions.GetDebugMenuToggleKeyComboAlphaKeyboard
// (Final, Native, Static, Public, BlueprintCallable, BlueprintPure)
// Parameters:
// struct FKey                    ReturnValue                    (Parm, OutParm, ReturnParm)

struct FKey UDebugMenuTestFunctions::STATIC_GetDebugMenuToggleKeyComboAlphaKeyboard()
{
	static auto fn = UObject::FindObject<UFunction>("Function DebugMenu.DebugMenuTestFunctions.GetDebugMenuToggleKeyComboAlphaKeyboard");

	struct
	{
		struct FKey                    ReturnValue;
	} params;

	auto flags = fn->FunctionFlags;
	fn->FunctionFlags |= 0x400;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function DebugMenu.DebugMenuTestFunctions.GetDebugMenuToggleButtonComboBetaGamepad
// (Final, Native, Static, Public, BlueprintCallable, BlueprintPure)
// Parameters:
// struct FKey                    ReturnValue                    (Parm, OutParm, ReturnParm)

struct FKey UDebugMenuTestFunctions::STATIC_GetDebugMenuToggleButtonComboBetaGamepad()
{
	static auto fn = UObject::FindObject<UFunction>("Function DebugMenu.DebugMenuTestFunctions.GetDebugMenuToggleButtonComboBetaGamepad");

	struct
	{
		struct FKey                    ReturnValue;
	} params;

	auto flags = fn->FunctionFlags;
	fn->FunctionFlags |= 0x400;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function DebugMenu.DebugMenuTestFunctions.GetDebugMenuToggleButtonComboAlphaGamepad
// (Final, Native, Static, Public, BlueprintCallable, BlueprintPure)
// Parameters:
// struct FKey                    ReturnValue                    (Parm, OutParm, ReturnParm)

struct FKey UDebugMenuTestFunctions::STATIC_GetDebugMenuToggleButtonComboAlphaGamepad()
{
	static auto fn = UObject::FindObject<UFunction>("Function DebugMenu.DebugMenuTestFunctions.GetDebugMenuToggleButtonComboAlphaGamepad");

	struct
	{
		struct FKey                    ReturnValue;
	} params;

	auto flags = fn->FunctionFlags;
	fn->FunctionFlags |= 0x400;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
