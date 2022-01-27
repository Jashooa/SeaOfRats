#pragma once

#ifdef _MSC_VER
    #pragma pack(push, 0x8)
#endif

namespace SDK
{
    // Class Engine.ActorComponent
    // 0x00A0 (0x00C8 - 0x0028)
    class UActorComponent : public UObject
    {
    public:
        char pad_0x0028[0x00A0];
    };

    // Class Engine.Actor
    // 0x03A8 (0x03D0 - 0x0028)
    class AActor : public UObject
    {
    public:
        char pad_0x0028[0x0148];
        class USceneComponent* RootComponent; // 0x0170(0x0008)
        char pad_0x0178[0x0258];

        void GetActorBounds(bool bOnlyCollidingComponents, struct FVector* Origin, struct FVector* BoxExtent);
        class AActor* GetAttachParentActor();
        class UActorComponent* GetComponentByClass(class UClass* ComponentClass);
        float GetDistanceTo(AActor* OtherActor);
        class AActor* GetParentActor();
        struct FVector GetVelocity();
        struct FVector K2_GetActorLocation();
        struct FRotator K2_GetActorRotation();
    };

    // Class Engine.DataAsset
    // 0x0000 (0x0028 - 0x0028)
    class UDataAsset : public UObject
    {
    public:
    };

    // Class Engine.BlueprintFunctionLibrary
    // 0x0000 (0x0028 - 0x0028)
    class UBlueprintFunctionLibrary : public UObject
    {
    public:
    };

    // Class Engine.SceneComponent
    // 0x01E8 (0x02B0 - 0x00C8)
    class USceneComponent : public UActorComponent
    {
    public:
        char pad_0x00C8[0x01E8];

        bool IsVisible();
        struct FVector K2_GetComponentLocation();
        struct FTransform K2_GetComponentToWorld();
    };

    // Class Engine.Pawn
    // 0x0078 (0x0448 - 0x03D0)
    class APawn : public AActor
    {
    public:
        char pad_0x03D0[0x0020];
        class APlayerState* PlayerState; // 0x03F0(0x0008)
        char pad_0x03F8[0x0010];
        class AController* Controller; // 0x0408(0x0008)
        char pad_0x0410[0x0038];
    };

    // Class Engine.Character
    // 0x0198 (0x05E0 - 0x0448)
    class ACharacter : public APawn
    {
    public:
        class USkeletalMeshComponent* Mesh; // 0x0448(0x0008)
        char pad_0x450[0x0190];
    };

    // Class Engine.GameInstance
    // 0x0060 (0x0088 - 0x0028)
    class UGameInstance : public UObject
    {
    public:
        char pad_0x0028[0x0010];
        class TArray<class ULocalPlayer*> LocalPlayers; // 0x0038(0x0010)
        char pad_0x0048[0x0040];
    };

    // Class Engine.Info
    // 0x0000 (0x03D0 - 0x03D0)
    class AInfo : public AActor
    {
    public:
    };

    // Class Engine.PrimitiveComponent
    // 0x02E0 (0x0590 - 0x02B0)
    class UPrimitiveComponent : public USceneComponent
    {
    public:
        char pad_0x02B0[0x02E0];
    };

    // Class Engine.GameState
    // 0x0058 (0x0428 - 0x03D0)
    class AGameState : public AInfo
    {
    public:
        char pad_0x03D0[0x0058];
    };

    // Class Engine.ScriptViewportClient
    // 0x0008 (0x0030 - 0x0028)
    class UScriptViewportClient : public UObject
    {
    public:
        char pad_0x0028[0x0008];
    };

    // Class Engine.GameViewportClient
    // 0x0220 (0x0250 - 0x0030)
    class UGameViewportClient : public UScriptViewportClient
    {
    public:
        char pad_0x0030[0x0050];
        class UWorld* World; // 0x0080(0x0008)
        class UGameInstance* GameInstance; // 0x0088(0x0008)
        char pad_0x0090[0x01C0];
    };

    // Class Engine.PlayerState
    // 0x0088 (0x0458 - 0x03D0)
    class APlayerState : public AInfo
    {
    public:
        char pad_0x03D0[0x0008];
        class FString PlayerName; // 0x03D8(0x0010)
        char pad_0x03E8[0x0070];
    };

    // Class Engine.Controller
    // 0x0060 (0x0430 - 0x03D0)
    class AController : public AActor
    {
    public:
        char pad_0x03D0[0x0008];
        class APawn* Pawn; // 0x03D8(0x0008)
        char pad_0x03E0[0x0050];

        bool LineOfSightTo(class AActor* Other, const struct FVector& ViewPoint, bool bAlternateChecks);
    };

    // Class Engine.PlayerController
    // 0x02F8 (0x0728 - 0x0430)
    class APlayerController : public AController
    {
    public:
        char pad_0x0430[0x0028];
        class AHUD* MyHUD;// 0x0458(0x0008)
        class APlayerCameraManager* PlayerCameraManager; // 0x0460(0x0008)
        char pad_0x0468[0x02C0];

        void AddPitchInput(float Val);
        void AddYawInput(float Val);
        bool IsInputKeyDown(const struct FKey& Key);
        bool ProjectWorldLocationToScreen(const struct FVector& WorldLocation, struct FVector2D* ScreenLocation);
    };

    // Class Engine.HUD
    // 0x00F8 (0x04C8 - 0x03D0)
    class AHUD : public AActor
    {
    public:
        char pad_0x03D0[0x0058];
        class UCanvas* Canvas; // 0x0428(0x0008)
        char pad_0x0430[0x0098];

        void DrawRect(const struct FLinearColor& RectColor, float ScreenX, float ScreenY, float ScreenW, float ScreenH);
    };

    // Class Engine.MeshComponent
    // 0x0010 (0x05A0 - 0x0590)
    class UMeshComponent : public UPrimitiveComponent
    {
    public:
        char pad_0x0590[0x0010];
    };

    // Class Engine.Player
    // 0x0020 (0x0048 - 0x0028)
    class UPlayer : public UObject
    {
    public:
        char pad_0x0028[0x0008];
        class APlayerController* PlayerController; // 0x0030(0x0008)
        char pad_0x0038[0x0010];
    };

    // Class Engine.World
    // 0x0840 (0x0868 - 0x0028)
    class UWorld : public UObject
    {
    public:
        char pad_0x0028[0x0008];
        class ULevel* PersistentLevel; // 0x0030(0x0008)
        char pad_0x0038[0x0020];
        class AGameState* GameState; // 0x0058(0x0008)
        char pad_0x0060[0x00F0];
        class TArray<ULevel*> Levels; // 0x0150(0x0010)
        char pad_0x0160[0x0050];
        class ULevel* CurrentLevel; // 0x01B0(0x0008)
        char pad_0x01B8[0x0008];
        class UGameInstance* OwningGameInstance; // 0x01C0(0x0008)
        char pad_0x01C8[0x06A0];
    };

    // Class Engine.Level
    // 0x02D8 (0x0300 - 0x0028)
    class ULevel : public UObject
    {
    public:
        char pad_0x0028[0x0078];
        class TArray<AActor*> AActors; // 0x00A0(0x0010)
        char pad_0x00B0[0x0250];
    };

    // Class Engine.PlayerCameraManager
    // 0x1880 (0x1C50 - 0x03D0)
    class APlayerCameraManager : public AActor
    {
    public:
        char pad_0x03D0[0x1880];

        struct FVector GetCameraLocation();
        struct FRotator GetCameraRotation();
    };

    // Class Engine.SkinnedMeshComponent
    // 0x0120 (0x06C0 - 0x05A0)
    class USkinnedMeshComponent : public UMeshComponent
    {
    public:
        char pad_0x05A0[0x0008];
        class TArray<struct FTransform> SpaceBasesArray[2]; // 0x05A8(0x0020)
        int CurrentEditableSpaceBases; // 0x05C8(0x0004)
        int CurrentReadSpaceBases; // 0x05CC(0x0004)
        char pad_0x05D0[0x00F0];
    };

    // Class Engine.SkeletalMeshComponent
    // 0x02D0 (0x0990 - 0x06C0)
    class USkeletalMeshComponent : public USkinnedMeshComponent
    {
    public:
        char pad_0x06C0[0x02D0];
    };

    // Class Engine.KismetGuidLibrary
    // 0x0000 (0x0028 - 0x0028)
    class UKismetGuidLibrary : public UBlueprintFunctionLibrary
    {
    public:
        static bool EqualEqual_GuidGuid(const struct FGuid& A, const struct FGuid& B);
    };

    // Class Engine.KismetMathLibrary
    // 0x0000 (0x0028 - 0x0028)
    class UKismetMathLibrary : public UBlueprintFunctionLibrary
    {
    public:
        static struct FRotator FindLookAtRotation(const struct FVector& Start, const struct FVector& Target);
        static struct FVector GetForwardVector(const struct FRotator& InRot);
        static struct FRotator NormalizedDeltaRotator(const struct FRotator& A, const struct FRotator& B);
    };

    // Class Engine.KismetTextLibrary
    // 0x0000 (0x0028 - 0x0028)
    class UKismetTextLibrary : public UBlueprintFunctionLibrary
    {
    public:
        static class FString Conv_TextToString(const struct FText& InText);
    };

    // Class Engine.Canvas
    // 0x00C8 (0x00F0 - 0x0028)
    class UCanvas : public UObject
    {
    public:
        char pad_0x0028[0x0008];
        float ClipX; // 0x0030(0x0004)
        float ClipY; // 0x0034(0x0004)
        char pad_0x0038[0x0008];
        int SizeX; // 0x0040(0x0004) 
        int SizeY; // 0x0044(0x0004)
        char pad_0x0048[0x00A8];

        void K2_DrawLine(const struct FVector2D& ScreenPositionA, const struct FVector2D& ScreenPositionB, float Thickness, const struct FLinearColor& RenderColor);
        void K2_DrawText(class UFont* RenderFont, const class FString& RenderText, const struct FVector2D& ScreenPosition, const struct FLinearColor& RenderColor, float Kerning, const struct FLinearColor& ShadowColor, const struct FVector2D& ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, const struct FLinearColor& OutlineColor);
    };

    // Class Engine.Font
    // 0x01B0 (0x01D8 - 0x0028)
    class UFont : public UObject
    {
    public:
        char pad_0x0028[0x01B0];
    };

    // Class Engine.LocalPlayer
    // 0x01C8 (0x0210 - 0x0048)
    class ULocalPlayer : public UPlayer
    {
    public:
        char pad_0x0048[0x01C8];
    };
}

#ifdef _MSC_VER
    #pragma pack(pop)
#endif
