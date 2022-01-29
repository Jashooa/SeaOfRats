#include "Aimbot.h"

#include <float.h>

#include "include/SDK/SDK.h"

#include "Bones.h"
#include "Drawing.h"

using namespace SDK;

AActor* nearestActor = nullptr;
float nearestDistance = FLT_MAX;
FVector2D centerScreen;

struct
{
    AActor* target = nullptr;
    FVector location;
    FRotator delta;
    float best = FLT_MAX;
} bestAim;

FVector cameraLocation;
FRotator cameraRotation;
AProjectileWeapon* playerWeapon = nullptr;

namespace Hacks
{
    namespace Aimbot
    {
        void Init(UWorld* world)
        {
            bestAim.target = nullptr;
            bestAim.best = FLT_MAX;
            playerWeapon = nullptr;

            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            cameraLocation = playerController->PlayerCameraManager->GetCameraLocation();
            cameraRotation = playerController->PlayerCameraManager->GetCameraRotation();

            auto wieldedItemComponent = reinterpret_cast<AAthenaCharacter*>(localPlayer)->WieldedItemComponent;
            auto wieldedItem = wieldedItemComponent->CurrentlyWieldedItem;
            if (wieldedItem)
            {
                if (wieldedItem->IsA(AProjectileWeapon::StaticClass()))
                {
                    playerWeapon = reinterpret_cast<AProjectileWeapon*>(wieldedItem);
                }
            }
        }

        void CalculateAim(UWorld* world, AActor* actor)
        {
            if (!playerWeapon)
            {
                return;
            }

            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
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

            // Check if same team
            if (UCrewFunctions::AreCharactersInSameCrew(reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer), reinterpret_cast<AAthenaCharacter*>(actor)))
            {
                return;
            }

            // Check if on screen
            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Check if out of range
            auto distance = localPlayer->GetDistanceTo(actor);
            if (distance > playerWeapon->WeaponParameters.ProjectileMaximumRange)
            {
                return;
            }

            // Check if have line of sight
            if (!playerController->LineOfSightTo(actor, cameraLocation, false))
            {
                return;
            }

            FRotator rotationDelta = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(cameraLocation, location), cameraRotation);
            float absYaw = abs(rotationDelta.Yaw);
            float absPitch = abs(rotationDelta.Pitch);
            float sum = absYaw + absPitch;

            if (sum < bestAim.best)
            {
                bestAim.target = actor;
                bestAim.location = location;
                bestAim.delta = rotationDelta;
                bestAim.best = sum;
            }
        }

        void Aim(UWorld* world)
        {
            if (!bestAim.target)
            {
                return;
            }

            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;

            auto boneLocation = GetBoneLocation(reinterpret_cast<ACharacter*>(bestAim.target), EBones::CHEST__Skeleton);

            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(boneLocation, &screen))
            {
                return;
            }
            bestAim.location = boneLocation;

            Drawing::DrawString(L"x", screen, Drawing::Colour::Red);

            FVector localVelocity = localPlayer->GetVelocity();
            if (const auto localShip = reinterpret_cast<AAthenaCharacter*>(localPlayer)->GetCurrentShip())
            {
                localVelocity += localShip->GetVelocity();
            }

            FVector targetVelocity = bestAim.target->GetVelocity();
            if (const auto targetShip = reinterpret_cast<AAthenaCharacter*>(bestAim.target)->GetCurrentShip())
            {
                targetVelocity += targetShip->GetVelocity();
            }

            const FVector relativeVelocity = targetVelocity - localVelocity;
            const float bulletSpeed = playerWeapon->WeaponParameters.AmmoParams.Velocity;
            const FVector relativeLocation = localPlayer->K2_GetActorLocation() - bestAim.location;
            const float a = relativeVelocity.Size() - bulletSpeed * bulletSpeed;
            const auto temp = relativeLocation * relativeVelocity * 2.f;
            //const float b = (relativeLocation * relativeVelocity * 2.f).Sum();
            const float b = temp.X + temp.Y + temp.Z;
            const float c = relativeLocation.SizeSquared();
            const float d = b * b - 4 * a - c;

            if (d > 0)
            {
                const float dRoot = sqrtf(d);
                const float x1 = (-b + dRoot) / (2 * a);
                const float x2 = (-b - dRoot) / (2 * a);
                if (x1 >= 0 && x1 >= x2)
                {
                    bestAim.location += relativeVelocity * x1;
                }
                else if (x2 >= 0)
                {
                    bestAim.location += relativeVelocity * x2;
                }

                //if (playerController->IsInputKeyDown(FKey{ "LeftMouseButton" }))
                if (playerController->IsInputKeyDown(FKey{ "LeftAlt" }))
                {
                    bestAim.delta = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(cameraLocation, bestAim.location), cameraRotation);

                    auto smoothness = 1.f / 5;
                    Drawing::DrawString(L"Yaw: " + std::to_wstring(bestAim.delta.Yaw), FVector2D(200.0f, 200.0f), Drawing::Colour::Red, false);
                    Drawing::DrawString(L"Pitch: " + std::to_wstring(bestAim.delta.Pitch), FVector2D(200.0f, 215.0f), Drawing::Colour::Red, false);
                    playerController->AddYawInput(bestAim.delta.Yaw * smoothness);
                    playerController->AddPitchInput(bestAim.delta.Pitch * -smoothness);
                }
            }
        }
    }
}