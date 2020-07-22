#include "Aimbot.h"

#include "SDK/SDK.h"

#include "Bones.h"
#include "Drawing.h"

using namespace SDK;

AActor* nearestActor = nullptr;
float nearestDistance = FLT_MAX;
FVector2D centerScreen;

namespace Hacks
{
    namespace Aimbot
    {
        void Init(AHUD* hud)
        {
            nearestActor = nullptr;
            nearestDistance = FLT_MAX;
            centerScreen = FVector2D(hud->Canvas->ClipX * 0.5f, hud->Canvas->ClipY * 0.5f);
        }

        void SetNearest(UGameViewportClient* client, AActor* actor)
        {
            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;

            // Check if me
            if (actor == localPlayer)
            {
                return;
            }

            // Check if dead
            if (reinterpret_cast<AAthenaCharacter*>(actor)->IsDead())
            {
                return;
            }

            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            if (!playerController->LineOfSightTo(actor, FVector(0.0f, 0.0f, 0.0f), false))
            {
                return;
            }

            auto centerDistance = UKismetMathLibrary::VSize2D(centerScreen - screen);
            if (centerDistance < nearestDistance)
            {
                nearestDistance = centerDistance;
                nearestActor = actor;
            }
        }

        bool ValidateAngles(APlayerCameraManager* cameraManager, FRotator* rotator)
        {
            if (rotator->Pitch < cameraManager->ViewPitchMin || rotator->Pitch > cameraManager->ViewPitchMax)
            {
                return false;
            }

            if (rotator->Pitch < 0.0f)
            {
                rotator->Pitch += 360.0f;
            }

            if (rotator->Yaw < 0.0f)
            {
                rotator->Yaw += 360.0f;
            }

            if (rotator->Yaw < cameraManager->ViewYawMin || rotator->Yaw > cameraManager->ViewYawMax)
            {
                return false;
            }

            rotator->Roll = 0.0f;

            return true;
        }

        void Aim(UGameViewportClient* client, AHUD* hud)
        {
            if (!nearestActor)
            {
                return;
            }

            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;

            auto location = Bones::GetBoneLocation(reinterpret_cast<ACharacter*>(nearestActor), Bones::EBones::HEAD__Skeleton);
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            Drawing::DrawActorString(hud, L"x", screen, Drawing::Colour::Red);

            auto cameraManager = playerController->PlayerCameraManager;
            if (cameraManager)
            {
                auto controlRotation = playerController->GetControlRotation();
                Drawing::DrawInterfaceString(hud, L"Pitch: " + std::to_wstring(controlRotation.Pitch), FVector2D(200.0f, 200.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Yaw: " + std::to_wstring(controlRotation.Yaw), FVector2D(200.0f, 215.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Roll: " + std::to_wstring(controlRotation.Roll), FVector2D(200.0f, 230.0f), Drawing::Colour::Red, false);

                auto cameraRotation = cameraManager->GetCameraRotation();
                Drawing::DrawInterfaceString(hud, L"Pitch: " + std::to_wstring(cameraRotation.Pitch), FVector2D(400.0f, 200.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Yaw: " + std::to_wstring(cameraRotation.Yaw), FVector2D(400.0f, 215.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Roll: " + std::to_wstring(cameraRotation.Roll), FVector2D(400.0f, 230.0f), Drawing::Colour::Red, false);

                auto rotation = UKismetMathLibrary::FindLookAtRotation(cameraManager->CameraCache.POV.Location, location);
                Drawing::DrawInterfaceString(hud, L"Pitch: " + std::to_wstring(rotation.Pitch), FVector2D(600.0f, 200.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Yaw: " + std::to_wstring(rotation.Yaw), FVector2D(600.0f, 215.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Roll: " + std::to_wstring(rotation.Roll), FVector2D(600.0f, 230.0f), Drawing::Colour::Red, false);

                bool validateAngles = ValidateAngles(cameraManager, &rotation);
                Drawing::DrawInterfaceString(hud, L"Pitch: " + std::to_wstring(rotation.Pitch), FVector2D(800.0f, 200.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Yaw: " + std::to_wstring(rotation.Yaw), FVector2D(800.0f, 215.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Roll: " + std::to_wstring(rotation.Roll), FVector2D(800.0f, 230.0f), Drawing::Colour::Red, false);
                if (validateAngles)
                {
                    Drawing::DrawInterfaceString(hud, L"True", FVector2D(800.0f, 245.0f), Drawing::Colour::Green, false);
                }

                Drawing::DrawInterfaceString(hud, L"Pitch Min: " + std::to_wstring(cameraManager->ViewPitchMin), FVector2D(1000.0f, 200.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Pitch Max: " + std::to_wstring(cameraManager->ViewPitchMax), FVector2D(1000.0f, 215.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Yaw Min: " + std::to_wstring(cameraManager->ViewYawMin), FVector2D(1000.0f, 230.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Yaw Max: " + std::to_wstring(cameraManager->ViewYawMax), FVector2D(1000.0f, 245.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Roll Min: " + std::to_wstring(cameraManager->ViewRollMin), FVector2D(1000.0f, 260.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Roll Max: " + std::to_wstring(cameraManager->ViewRollMax), FVector2D(1000.0f, 275.0f), Drawing::Colour::Red, false);

                if (playerController->IsInputKeyDown(FKey{ "LeftAlt" }) && validateAngles)
                {
                    //playerController->ClientSetRotation(rotation, false);
                    playerController->ControlRotation = rotation;
                }
            }
        }
    }
}