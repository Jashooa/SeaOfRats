#include "Player.h"

#include "Hacks/Bones.h"
#include "Utilities/Drawing.h"
#include "Utilities/Input.h"
#include "Utilities/Math.h"

using namespace SDK;

namespace Hacks
{
    namespace Aimbot
    {
        Player::BestAim Player::bestAim{};
        SDK::FVector Player::cameraLocation;
        SDK::FRotator Player::cameraRotation;
        SDK::AProjectileWeapon* Player::weapon;
        SDK::FVector2D Player::centreScreen;

        void Player::InitAim(UWorld * world)
        {
            bestAim.target = nullptr;
            bestAim.best = FLT_MAX;
            weapon = nullptr;

            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaCharacter*>(playerController->Pawn);

            centreScreen = Utilities::Drawing::GetScreenCentre();

            if (const auto wieldedItemComponent = localPlayer->WieldedItemComponent)
            {
                if (const auto wieldedItem = wieldedItemComponent->CurrentlyWieldedItem)
                {
                    if (wieldedItem->IsA(AProjectileWeapon::StaticClass()))
                    {
                        weapon = reinterpret_cast<AProjectileWeapon*>(wieldedItem);
                        Utilities::Drawing::DrawCircle(centreScreen, aimRadius, Utilities::Drawing::Colour::Red);
                    }
                }
            }

            cameraLocation = playerController->PlayerCameraManager->GetCameraLocation();
            cameraRotation = playerController->PlayerCameraManager->GetCameraRotation();
        }

        void Player::CalculateAim(UWorld* world, AActor* actor)
        {
            if (!weapon)
            {
                return;
            }

            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;

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
            const auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Check if out of range
            const auto distance = localPlayer->GetDistanceTo(actor);
            if (distance > weapon->WeaponParameters.ProjectileMaximumRange)
            {
                return;
            }

            // Check if have line of sight
            if (!playerController->LineOfSightTo(actor, cameraLocation, false))
            {
                return;
            }

            FRotator rotationDelta = FRotator(UKismetMathLibrary::FindLookAtRotation(cameraLocation, location) - cameraRotation);
            rotationDelta.Normalize();
            const float absYaw = FMath::Abs(rotationDelta.Yaw);
            const float absPitch = FMath::Abs(rotationDelta.Pitch);
            const float sum = absYaw + absPitch;

            if (sum < bestAim.best)
            {
                bestAim.target = actor;
                bestAim.location = location;
                bestAim.delta = rotationDelta;
                bestAim.best = sum;
            }
        }

        void Player::Aim(UWorld* world)
        {
            if (!bestAim.target)
            {
                return;
            }

            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;

            FVector aimLocation;
            if (bestAim.target->IsA(AAthenaPlayerCharacter::StaticClass()) || bestAim.target->IsA(AAthenaAICharacter::StaticClass()))
            {
                aimLocation = GetBoneLocation(reinterpret_cast<ACharacter*>(bestAim.target), EBones::CHEST__Skeleton);
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

            if (!Utilities::Math::PointInCircle(position, centreScreen, aimRadius))
            {
                return;
            }

            // FVector localVelocity = localPlayer->GetVelocity();
            FVector localVelocity{ 0.f };
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
            const float bulletSpeed = weapon->WeaponParameters.AmmoParams.Velocity;
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
                Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::Red);
                // Utilities::Drawing::DrawString("Yaw: " + std::to_string(bestAim.delta.Yaw), FVector2D(200.f, 200.f), Utilities::Drawing::Colour::Red, false);
                // Utilities::Drawing::DrawString("Pitch: " + std::to_string(bestAim.delta.Pitch), FVector2D(200.f, 215.f), Utilities::Drawing::Colour::Red, false);
                // Utilities::Drawing::DrawString("Velocity: " + std::to_string(bulletSpeed), FVector2D(200.f, 200.f), Utilities::Drawing::Colour::Red, false);

                if (Utilities::Input::IsKeyPressed(VK_MENU))
                {
                    // bestAim.delta = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(cameraLocation, bestAim.location), cameraRotation);

                    // auto aimSpeed = 5.f;
                    // auto smoothness = 1.f / aimSpeed;
                    // playerController->AddYawInput(bestAim.delta.Yaw * smoothness);
                    // playerController->AddPitchInput(bestAim.delta.Pitch * -smoothness);

                    float targetX = 0;
                    float targetY = 0;

                    const float centreX = centreScreen.X;
                    const float centreY = centreScreen.Y;

                    if (position.X > centreX)
                    {
                        targetX = -(centreX - position.X);
                        if (targetX + centreX > centreX * 2)
                        {
                            targetX = 0;
                        }
                    }
                    else
                    {
                        targetX = position.X - centreX;
                        if (targetX + centreX < 0)
                        {
                            targetX = 0;
                        }
                    }

                    if (position.Y > centreY)
                    {
                        targetY = -(centreY - position.Y);
                        if (targetY + centreY > centreY * 2)
                        {
                            targetY = 0;
                        }
                    }
                    else
                    {
                        targetY = position.Y - centreY;
                        if (targetY + centreY < 0)
                        {
                            targetY = 0;
                        }
                    }

                    Utilities::Input::MouseMove(static_cast<int>(targetX), static_cast<int>(targetY));
                }
            }
        }
    }
}
