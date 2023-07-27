#include "Player.h"

#include "Drawing.h"
#include "Hacks/Bones.h"
#include "Utilities/Math.h"

using namespace SDK;

namespace Hacks
{
    namespace Aimbot
    {
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
        FVector2D centreScreen;
        const float aimRadius = 100.f;

        void InitAimPlayer(UWorld* world)
        {
            bestAim.target = nullptr;
            bestAim.best = FLT_MAX;
            playerWeapon = nullptr;

            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaCharacter*>(playerController->Pawn);

            centreScreen = Drawing::GetScreenCentre();

            if (const auto wieldedItemComponent = localPlayer->WieldedItemComponent)
            {
                if (const auto wieldedItem = wieldedItemComponent->CurrentlyWieldedItem)
                {
                    if (wieldedItem->IsA(AProjectileWeapon::StaticClass()))
                    {
                        playerWeapon = reinterpret_cast<AProjectileWeapon*>(wieldedItem);
                        Drawing::DrawCircle(centreScreen, aimRadius, Drawing::Colour::Red);
                    }
                }
            }

            cameraLocation = playerController->PlayerCameraManager->GetCameraLocation();
            cameraRotation = playerController->PlayerCameraManager->GetCameraRotation();
        }

        void CalculateAimPlayer(UWorld* world, AActor* actor)
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

        void AimPlayer(UWorld* world)
        {
            if (!bestAim.target)
            {
                return;
            }

            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;

            FVector aimLocation;
            if (bestAim.target->IsA(AAthenaPlayerCharacter::StaticClass()) || bestAim.target->IsA(AAthenaAICharacter::StaticClass()))
            {
                aimLocation = GetBoneLocation(reinterpret_cast<ACharacter*>(bestAim.target), EBones::UPPER_BODY_LOCK__Skeleton);
            }
            else
            {
                aimLocation = bestAim.target->K2_GetActorLocation();
            }

            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(aimLocation, &position))
            {
                return;
            }
            bestAim.location = aimLocation;

            if (!Utilities::PointInCircle(position, centreScreen, aimRadius))
            {
                return;
            }

            // FVector localVelocity = localPlayer->GetVelocity();
            FVector localVelocity(0.f, 0.f, 0.f);
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
            const float b = (relativeLocation * relativeVelocity * 2.f).Sum();
            const float c = relativeLocation.SizeSquared();
            const float d = b * b - 4 * a * c;

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

                if (!playerController->ProjectWorldLocationToScreen(bestAim.location, &position))
                {
                    return;
                }
                Drawing::DrawString("x", position, Drawing::Colour::Red);
                // Drawing::DrawString("Yaw: " + std::to_string(bestAim.delta.Yaw), FVector2D(200.f, 200.f), Drawing::Colour::Red, false);
                // Drawing::DrawString("Pitch: " + std::to_string(bestAim.delta.Pitch), FVector2D(200.f, 215.f), Drawing::Colour::Red, false);
                Drawing::DrawString("Velocity: " + std::to_string(bulletSpeed), FVector2D(200.f, 200.f), Drawing::Colour::Red, false);
                //Drawing::DrawString("Yaw: " + std::to_string(bestAim.delta.Yaw), FVector2D(200.f, 215.f), Drawing::Colour::Red, false);

                // if (playerController->IsInputKeyDown(FKey{ "LeftMouseButton" }))
                // if (playerController->IsInputKeyDown(FKey{ "LeftAlt" }))
                if ((GetAsyncKeyState(VK_LMENU) & 0x8000) != 0)
                {
                    // bestAim.delta = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(cameraLocation, bestAim.location), cameraRotation);

                    auto aimSpeed = 5.f;
                    auto smoothness = 1.f / aimSpeed;
                    // playerController->AddYawInput(bestAim.delta.Yaw * smoothness);
                    // playerController->AddPitchInput(bestAim.delta.Pitch * -smoothness);

                    FVector2D centre = Drawing::GetScreenCentre();

                    float targetX = 0;
                    float targetY = 0;

                    if (position.X > centre.X)
                    {
                        targetX = -(centre.X - position.X);
                        // targetX /= aimSpeed;
                        if (targetX + centre.X > centre.X * 2)
                        {
                            targetX = 0;
                        }
                    }
                    else
                    {
                        targetX = position.X - centre.X;
                        // targetX /= aimSpeed;
                        if (targetX + centre.X < 0)
                        {
                            targetX = 0;
                        }
                    }

                    if (position.Y > centre.Y)
                    {
                        targetY = -(centre.Y - position.Y);
                        // targetY /= aimSpeed;
                        if (targetY + centre.Y > centre.Y * 2)
                        {
                            targetY = 0;
                        }
                    }
                    else
                    {
                        targetY = position.Y - centre.Y;
                        // targetY /= aimSpeed;
                        if (targetY + centre.Y < 0)
                        {
                            targetY = 0;
                        }
                    }

                    if ((GetAsyncKeyState(VK_LMENU) & 0x8000) != 0)
                    {
                        mouse_event(MOUSEEVENTF_MOVE, (DWORD)(targetX), (DWORD)(targetY), NULL, NULL);
                    }
                }
            }
        }
    }
}
