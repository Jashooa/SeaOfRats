#include "Aimbot.h"

#include "SDK/SDK.h"

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

            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
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

        void Aim(UGameViewportClient* client, AHUD* hud)
        {
            if (!nearestActor)
            {
                return;
            }

            auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;

            auto location = nearestActor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            Drawing::DrawActorString(hud, L"x", screen, Drawing::Colour::Red);

            auto cameraManager = playerController->PlayerCameraManager;
            if (cameraManager)
            {
                /*auto currentRotation = playerController->GetControlRotation();
                Drawing::DrawInterfaceString(hud, L"Pitch: " + std::to_wstring(currentRotation.Pitch), FVector2D(200.0f, 200.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Yaw: " + std::to_wstring(currentRotation.Yaw), FVector2D(200.0f, 215.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Roll: " + std::to_wstring(currentRotation.Roll), FVector2D(200.0f, 230.0f), Drawing::Colour::Red, false);*/

                auto rotation = UKismetMathLibrary::FindLookAtRotation(cameraManager->CameraCache.POV.Location, location);
                /*Drawing::DrawInterfaceString(hud, L"Pitch: " + std::to_wstring(rotation.Pitch), FVector2D(400.0f, 200.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Yaw: " + std::to_wstring(rotation.Yaw), FVector2D(400.0f, 215.0f), Drawing::Colour::Red, false);
                Drawing::DrawInterfaceString(hud, L"Roll: " + std::to_wstring(rotation.Roll), FVector2D(400.0f, 230.0f), Drawing::Colour::Red, false);*/

                if (playerController->IsInputKeyDown(FKey{ "LeftAlt" }))
                {
                    playerController->ClientSetRotation(rotation, false);
                }
            }
        }
    }
}