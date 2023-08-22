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
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
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
        } parms{};
        parms.bOnlyCollidingComponents = bOnlyCollidingComponents;

        UObject::ProcessEvent(this, fn, &parms);

        if (Origin != nullptr)
        {
            *Origin = parms.Origin;
        }
        if (BoxExtent != nullptr)
        {
            *BoxExtent = parms.BoxExtent;
        }
    }

    // Function Engine.Actor.GetActorForwardVector
    struct FVector AActor::GetActorForwardVector()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetActorForwardVector");

        struct
        {
            struct FVector ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.Actor.GetActorRightVector
    struct FVector AActor::GetActorRightVector()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetActorRightVector");

        struct
        {
            struct FVector ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.Actor.GetActorUpVector
    struct FVector AActor::GetActorUpVector()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetActorUpVector");

        struct
        {
            struct FVector ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.Actor.GetAttachParentActor
    class AActor* AActor::GetAttachParentActor()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetAttachParentActor");

        struct
        {
            class AActor* ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.Actor.GetComponentByClass
    class UActorComponent* AActor::GetComponentByClass(class UClass* ComponentClass)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetComponentByClass");

        struct
        {
            class UClass* ComponentClass;
            class UActorComponent* ReturnValue;
        } parms{};
        parms.ComponentClass = ComponentClass;

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.Actor.GetComponentsByClass
    TArray<class UActorComponent*> AActor::GetComponentsByClass(class UClass* ComponentClass)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetComponentsByClass");

        struct
        {
            class UClass* ComponentClass;
            TArray<class UActorComponent*> ReturnValue;
        } parms{};
        parms.ComponentClass = ComponentClass;

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.Actor.GetDistanceTo
    float AActor::GetDistanceTo(class AActor* OtherActor)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetDistanceTo");

        struct
        {
            class AActor* OtherActor;
            float ReturnValue;
        } parms{};
        parms.OtherActor = OtherActor;

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.Actor.GetParentActor
    class AActor* AActor::GetParentActor()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetParentActor");

        struct
        {
            class AActor* ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.Actor.GetVelocity
    struct FVector AActor::GetVelocity()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.GetVelocity");

        struct
        {
            struct FVector ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.Actor.K2_GetActorLocation
    struct FVector AActor::K2_GetActorLocation()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.K2_GetActorLocation");

        struct
        {
            struct FVector ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.Actor.K2_GetActorRotation
    struct FRotator AActor::K2_GetActorRotation()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.Actor.K2_GetActorRotation");

        struct
        {
            struct FRotator ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.SceneComponent.IsVisible
    bool USceneComponent::IsVisible()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.SceneComponent.IsVisible");

        struct
        {
            bool ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.SceneComponent.K2_GetComponentLocation
    struct FVector USceneComponent::K2_GetComponentLocation()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.SceneComponent.K2_GetComponentLocation");

        struct
        {
            struct FVector ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.SceneComponent.K2_GetComponentRotation
    struct FRotator USceneComponent::K2_GetComponentRotation()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.SceneComponent.K2_GetComponentRotation");

        struct
        {
            struct FRotator ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.SceneComponent.K2_GetComponentToWorld
    struct FTransform USceneComponent::K2_GetComponentToWorld()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.SceneComponent.K2_GetComponentToWorld");

        struct
        {
            struct FTransform ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
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
        } parms{};
        parms.Other = Other;
        parms.ViewPoint = ViewPoint;
        parms.bAlternateChecks = bAlternateChecks;

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.PlayerController.AddPitchInput
    void APlayerController::AddPitchInput(float Val)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.AddPitchInput");

        struct
        {
            float Val;
        } parms{};
        parms.Val = Val;

        UObject::ProcessEvent(this, fn, &parms);
    }

    // Function Engine.PlayerController.AddYawInput
    void APlayerController::AddYawInput(float Val)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerController.AddYawInput");

        struct
        {
            float Val;
        } parms{};
        parms.Val = Val;

        UObject::ProcessEvent(this, fn, &parms);
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
        } parms{};
        parms.WorldLocation = WorldLocation;

        UObject::ProcessEvent(this, fn, &parms);

        if (ScreenLocation != nullptr)
        {
            *ScreenLocation = parms.ScreenLocation;
        }

        return parms.ReturnValue;
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
        } parms{};
        parms.RectColor = RectColor;
        parms.ScreenX = ScreenX;
        parms.ScreenY = ScreenY;
        parms.ScreenW = ScreenW;
        parms.ScreenH = ScreenH;

        UObject::ProcessEvent(this, fn, &parms);
    }

    // Function Engine.PlayerCameraManager.GetCameraLocation
    struct FVector APlayerCameraManager::GetCameraLocation()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerCameraManager.GetCameraLocation");

        struct
        {
            struct FVector ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.PlayerCameraManager.GetCameraRotation
    struct FRotator APlayerCameraManager::GetCameraRotation()
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.PlayerCameraManager.GetCameraRotation");

        struct
        {
            struct FRotator ReturnValue;
        } parms{};

        UObject::ProcessEvent(this, fn, &parms);

        return parms.ReturnValue;
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
        } parms{};
        parms.Start = Start;
        parms.Target = Target;

        static auto defaultObj = UObject::FindObject<UClass>("Class Engine.KismetMathLibrary");
        UObject::ProcessEvent(defaultObj, fn, &parms);

        return parms.ReturnValue;
    }

    // Function Engine.KismetSystemLibrary.DrawDebugCircle
    void UKismetSystemLibrary::DrawDebugCircle(class UObject* WorldContextObject, const struct FVector& Center, float Radius, int NumSegments, const struct FLinearColor& LineColor, float Duration, float Thickness, const struct FVector& YAxis, const struct FVector& ZAxis, bool bDrawAxis)
    {
        static auto fn = UObject::FindObject<UFunction>("Function Engine.KismetSystemLibrary.DrawDebugCircle");

        struct
        {
            class UObject* WorldContextObject;
            struct FVector Center;
            float Radius;
            int NumSegments;
            struct FLinearColor LineColor;
            float Duration;
            float Thickness;
            struct FVector YAxis;
            struct FVector ZAxis;
            bool bDrawAxis;
        } parms{};
        parms.WorldContextObject = WorldContextObject;
        parms.Center = Center;
        parms.Radius = Radius;
        parms.NumSegments = NumSegments;
        parms.LineColor = LineColor;
        parms.Duration = Duration;
        parms.Thickness = Thickness;
        parms.YAxis = YAxis;
        parms.ZAxis = ZAxis;
        parms.bDrawAxis = bDrawAxis;

        static auto defaultObj = UObject::FindObject<UClass>("Class Engine.KismetSystemLibrary");
        UObject::ProcessEvent(defaultObj, fn, &parms);
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
        } parms{};
        parms.WorldContextObject = WorldContextObject;
        parms.Start = Start;
        parms.End = End;
        parms.TraceChannel = TraceChannel;
        parms.bTraceComplex = bTraceComplex;
        parms.ActorsToIgnore = ActorsToIgnore;
        parms.DrawDebugType = DrawDebugType;
        parms.bIgnoreSelf = bIgnoreSelf;

        static auto defaultObj = UObject::FindObject<UClass>("Class Engine.KismetSystemLibrary");
        UObject::ProcessEvent(defaultObj, fn, &parms);

        if (OutHit != nullptr)
        {
            *OutHit = parms.OutHit;
        }

        return parms.ReturnValue;
    }
}
