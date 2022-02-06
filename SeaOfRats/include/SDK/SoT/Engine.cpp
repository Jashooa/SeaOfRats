#ifdef _MSC_VER
#pragma pack(push, 0x8)
#endif

#include "SDK/SDK.h"

namespace SDK
{
    UWorld** UWorld::GWorld = nullptr;

    // Function Engine.ActorComponent.GetOwner
    class AActor* UActorComponent::GetOwner()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.ActorComponent.GetOwner");

        struct
        {
            class AActor* ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.Actor.GetActorBounds
    void AActor::GetActorBounds(bool bOnlyCollidingComponents, struct FVector* Origin, struct FVector* BoxExtent)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetActorBounds");

        struct
        {
            bool bOnlyCollidingComponents;
            struct FVector Origin;
            struct FVector BoxExtent;
        } params{};
        params.bOnlyCollidingComponents = bOnlyCollidingComponents;

        UObject::ProcessEvent(this, fn, &params);

        if (Origin != nullptr)
        {
            *Origin = params.Origin;
        }
        if (BoxExtent != nullptr)
        {
            *BoxExtent = params.BoxExtent;
        }
    }

    // Function Engine.Actor.GetAttachParentActor
    class AActor* AActor::GetAttachParentActor()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetAttachParentActor");

        struct
        {
            class AActor* ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.Actor.GetComponentByClass
    class UActorComponent* AActor::GetComponentByClass(class UClass* ComponentClass)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetComponentByClass");

        struct
        {
            class UClass* ComponentClass;
            class UActorComponent* ReturnValue;
        } params{};
        params.ComponentClass = ComponentClass;

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.Actor.GetDistanceTo
    float AActor::GetDistanceTo(class AActor* OtherActor)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetDistanceTo");

        struct
        {
            class AActor* OtherActor;
            float ReturnValue;
        } params{};
        params.OtherActor = OtherActor;

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.Actor.GetParentActor
    class AActor* AActor::GetParentActor()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetParentActor");

        struct
        {
            class AActor* ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.Actor.GetVelocity
    struct FVector AActor::GetVelocity()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetVelocity");

        struct
        {
            struct FVector ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.Actor.K2_GetActorLocation
    struct FVector AActor::K2_GetActorLocation()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.K2_GetActorLocation");

        struct
        {
            struct FVector ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.Actor.K2_GetActorRotation
    struct FRotator AActor::K2_GetActorRotation()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.K2_GetActorRotation");

        struct
        {
            struct FRotator ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.SceneComponent.IsVisible
    bool USceneComponent::IsVisible()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.SceneComponent.IsVisible");

        struct
        {
            bool ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.SceneComponent.K2_GetComponentLocation
    struct FVector USceneComponent::K2_GetComponentLocation()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.SceneComponent.K2_GetComponentLocation");

        struct
        {
            struct FVector ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.SceneComponent.K2_GetComponentRotation
    struct FRotator USceneComponent::K2_GetComponentRotation()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.SceneComponent.K2_GetComponentRotation");

        struct
        {
            struct FRotator ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.SceneComponent.K2_GetComponentToWorld
    struct FTransform USceneComponent::K2_GetComponentToWorld()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.SceneComponent.K2_GetComponentToWorld");

        struct
        {
            struct FTransform ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.Controller.LineOfSightTo
    bool AController::LineOfSightTo(class AActor* Other, const struct FVector& ViewPoint, bool bAlternateChecks)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Controller.LineOfSightTo");

        struct
        {
            class AActor* Other;
            struct FVector ViewPoint;
            bool bAlternateChecks;
            bool ReturnValue;
        } params{};
        params.Other = Other;
        params.ViewPoint = ViewPoint;
        params.bAlternateChecks = bAlternateChecks;

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.PlayerController.AddPitchInput
    void APlayerController::AddPitchInput(float Val)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.AddPitchInput");

        struct
        {
            float Val;
        } params{};
        params.Val = Val;

        UObject::ProcessEvent(this, fn, &params);
    }

    // Function Engine.PlayerController.AddYawInput
    void APlayerController::AddYawInput(float Val)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.AddYawInput");

        struct
        {
            float Val;
        } params{};
        params.Val = Val;

        UObject::ProcessEvent(this, fn, &params);
    }

    // Function Engine.PlayerController.IsInputKeyDown
    bool APlayerController::IsInputKeyDown(const struct FKey& Key)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.IsInputKeyDown");

        struct
        {
            struct FKey Key;
            bool ReturnValue;
        } params{};
        params.Key = Key;

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.PlayerController.ProjectWorldLocationToScreen
    bool APlayerController::ProjectWorldLocationToScreen(const struct FVector& WorldLocation, struct FVector2D* ScreenLocation)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.ProjectWorldLocationToScreen");

        struct
        {
            struct FVector WorldLocation;
            struct FVector2D ScreenLocation;
            bool ReturnValue;
        } params{};
        params.WorldLocation = WorldLocation;

        UObject::ProcessEvent(this, fn, &params);

        if (ScreenLocation != nullptr)
        {
            *ScreenLocation = params.ScreenLocation;
        }

        return params.ReturnValue;
    }

    // Function Engine.HUD.DrawRect
    void AHUD::DrawRect(const struct FLinearColor& RectColor, float ScreenX, float ScreenY, float ScreenW, float ScreenH)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.HUD.DrawRect");

        struct
        {
            struct FLinearColor RectColor;
            float ScreenX;
            float ScreenY;
            float ScreenW;
            float ScreenH;
        } params{};
        params.RectColor = RectColor;
        params.ScreenX = ScreenX;
        params.ScreenY = ScreenY;
        params.ScreenW = ScreenW;
        params.ScreenH = ScreenH;

        UObject::ProcessEvent(this, fn, &params);
    }

    // Function Engine.PlayerCameraManager.GetCameraLocation
    struct FVector APlayerCameraManager::GetCameraLocation()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerCameraManager.GetCameraLocation");

        struct
        {
            struct FVector ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.PlayerCameraManager.GetCameraRotation
    struct FRotator APlayerCameraManager::GetCameraRotation()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerCameraManager.GetCameraRotation");

        struct
        {
            struct FRotator ReturnValue;
        } params{};

        UObject::ProcessEvent(this, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.KismetGuidLibrary.Conv_GuidToString
    class FString UKismetGuidLibrary::Conv_GuidToString(const struct FGuid& InGuid)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetGuidLibrary.Conv_GuidToString");

        struct
        {
            struct FGuid                   InGuid;
            class FString                  ReturnValue;
        } params{};
        params.InGuid = InGuid;

        static auto defaultObj = UObject::FindObject<UClass>("Class Engine.KismetGuidLibrary");
        UObject::ProcessEvent(defaultObj, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.KismetGuidLibrary.EqualEqual_GuidGuid
    bool UKismetGuidLibrary::EqualEqual_GuidGuid(const struct FGuid& A, const struct FGuid& B)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetGuidLibrary.EqualEqual_GuidGuid");

        struct
        {
            struct FGuid A;
            struct FGuid B;
            bool ReturnValue;
        } params{};
        params.A = A;
        params.B = B;

        static auto defaultObj = UObject::FindObject<UClass>("Class Engine.KismetGuidLibrary");
        UObject::ProcessEvent(defaultObj, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.KismetMathLibrary.Conv_RotatorToVector
    struct FVector UKismetMathLibrary::Conv_RotatorToVector(const struct FRotator& InRot)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetMathLibrary.Conv_RotatorToVector");

        struct
        {
            struct FRotator InRot;
            struct FVector ReturnValue;
        } params{};
        params.InRot = InRot;

        static auto defaultObj = UObject::FindObject<UClass>("Class Engine.KismetMathLibrary");
        UObject::ProcessEvent(defaultObj, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.KismetMathLibrary.FindLookAtRotation
    struct FRotator UKismetMathLibrary::FindLookAtRotation(const struct FVector& Start, const struct FVector& Target)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetMathLibrary.FindLookAtRotation");

        struct
        {
            struct FVector Start;
            struct FVector Target;
            struct FRotator ReturnValue;
        } params{};
        params.Start = Start;
        params.Target = Target;

        static auto defaultObj = UObject::FindObject<UClass>("Class Engine.KismetMathLibrary");
        UObject::ProcessEvent(defaultObj, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.KismetMathLibrary.GetForwardVector
    struct FVector UKismetMathLibrary::GetForwardVector(const struct FRotator& InRot)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetMathLibrary.GetForwardVector");

        struct
        {
            struct FRotator InRot;
            struct FVector ReturnValue;
        } params{};
        params.InRot = InRot;

        static auto defaultObj = UObject::FindObject<UClass>("Class Engine.KismetMathLibrary");
        UObject::ProcessEvent(defaultObj, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.KismetMathLibrary.NormalizedDeltaRotator
    struct FRotator UKismetMathLibrary::NormalizedDeltaRotator(const struct FRotator& A, const struct FRotator& B)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetMathLibrary.NormalizedDeltaRotator");

        struct
        {
            struct FRotator A;
            struct FRotator B;
            struct FRotator ReturnValue;
        } params{};
        params.A = A;
        params.B = B;

        static auto defaultObj = UObject::FindObject<UClass>("Class Engine.KismetMathLibrary");
        UObject::ProcessEvent(defaultObj, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.KismetSystemLibrary.LineTraceSingle_NEW
    bool UKismetSystemLibrary::LineTraceSingle_NEW(class UObject* WorldContextObject, const struct FVector& Start, const struct FVector& End, TEnumAsByte<ETraceTypeQuery> TraceChannel, bool bTraceComplex, TArray<class AActor*> ActorsToIgnore, TEnumAsByte<EDrawDebugTrace> DrawDebugType, bool bIgnoreSelf, struct FHitResult* OutHit)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetSystemLibrary.LineTraceSingle_NEW");

        struct
        {
            class UObject* WorldContextObject;
            struct FVector Start;
            struct FVector End;
            TEnumAsByte<ETraceTypeQuery>   TraceChannel;
            bool bTraceComplex;
            TArray<class AActor*> ActorsToIgnore;
            TEnumAsByte<EDrawDebugTrace>   DrawDebugType;
            struct FHitResult OutHit;
            bool bIgnoreSelf;
            bool ReturnValue;
        } params{};
        params.WorldContextObject = WorldContextObject;
        params.Start = Start;
        params.End = End;
        params.TraceChannel = TraceChannel;
        params.bTraceComplex = bTraceComplex;
        params.ActorsToIgnore = ActorsToIgnore;
        params.DrawDebugType = DrawDebugType;
        params.bIgnoreSelf = bIgnoreSelf;

        static auto defaultObj = UObject::FindObject<UClass>("Class Engine.KismetSystemLibrary");
        UObject::ProcessEvent(defaultObj, fn, &params);

        if (OutHit != nullptr)
        {
            *OutHit = params.OutHit;
        }

        return params.ReturnValue;
    }

    // Function Engine.KismetTextLibrary.Conv_TextToString
    class FString UKismetTextLibrary::Conv_TextToString(const struct FText& InText)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetTextLibrary.Conv_TextToString");

        struct
        {
            struct FText InText;
            class FString ReturnValue;
        } params{};
        params.InText = InText;

        static auto defaultObj = UObject::FindObject<UClass>("Class Engine.KismetTextLibrary");
        UObject::ProcessEvent(defaultObj, fn, &params);

        return params.ReturnValue;
    }

    // Function Engine.Canvas.K2_DrawLine
    void UCanvas::K2_DrawLine(const struct FVector2D& ScreenPositionA, const struct FVector2D& ScreenPositionB, float Thickness, const struct FLinearColor& RenderColor)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Canvas.K2_DrawLine");

        struct
        {
            struct FVector2D ScreenPositionA;
            struct FVector2D ScreenPositionB;
            float Thickness;
            struct FLinearColor RenderColor;
        } params{};
        params.ScreenPositionA = ScreenPositionA;
        params.ScreenPositionB = ScreenPositionB;
        params.Thickness = Thickness;
        params.RenderColor = RenderColor;

        UObject::ProcessEvent(this, fn, &params);
    }

    // Function Engine.Canvas.K2_DrawText
    void UCanvas::K2_DrawText(class UFont* RenderFont, const class FString& RenderText, const struct FVector2D& ScreenPosition, const struct FLinearColor& RenderColor, float Kerning, const struct FLinearColor& ShadowColor, const struct FVector2D& ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, const struct FLinearColor& OutlineColor)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Canvas.K2_DrawText");

        struct
        {
            class UFont* RenderFont;
            class FString RenderText;
            struct FVector2D ScreenPosition;
            struct FLinearColor RenderColor;
            float Kerning;
            struct FLinearColor ShadowColor;
            struct FVector2D ShadowOffset;
            bool bCentreX;
            bool bCentreY;
            bool bOutlined;
            struct FLinearColor OutlineColor;
        } params{};
        params.RenderFont = RenderFont;
        params.RenderText = RenderText;
        params.ScreenPosition = ScreenPosition;
        params.RenderColor = RenderColor;
        params.Kerning = Kerning;
        params.ShadowColor = ShadowColor;
        params.ShadowOffset = ShadowOffset;
        params.bCentreX = bCentreX;
        params.bCentreY = bCentreY;
        params.bOutlined = bOutlined;
        params.OutlineColor = OutlineColor;

        UObject::ProcessEvent(this, fn, &params);
    }
}

#ifdef _MSC_VER
#pragma pack(pop)
#endif
