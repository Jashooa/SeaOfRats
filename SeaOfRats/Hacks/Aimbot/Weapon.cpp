#include "Weapon.h"

#include "Hacks/Bones.h"
#include "Utilities/Drawing.h"
#include "Utilities/Input.h"
#include "Utilities/Math.h"

using namespace SDK;

namespace Hacks
{
    namespace Aimbot
    {
        Weapon::BestAim Weapon::bestAim{};
        FVector Weapon::cameraLocation;
        FRotator Weapon::cameraRotation;
        AProjectileWeapon* Weapon::weapon;
        FVector2D Weapon::centreScreen;

        void Weapon::InitAim(UWorld * world)
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

        void Weapon::CalculateAim(UWorld* world, AActor* actor)
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

            if (actor->IsA(AAthenaCharacter::StaticClass()))
            {
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
            }
            else if (actor->IsA(ASwimmingCreaturePawn::StaticClass()))
            {
                // Check if dead
                if (const auto healthComponent = reinterpret_cast<ASwimmingCreaturePawn*>(actor)->HealthComponent)
                {
                    if (healthComponent->GetCurrentHealth() == 0.f)
                    {
                        return;
                    }
                }
            }

            // Check if on screen
            const auto location = actor->K2_GetActorLocation();
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Check if outside aim radius
            if (!Utilities::Math::PointInCircle(position, centreScreen, aimRadius))
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

            auto rotationDelta = (UKismetMathLibrary::FindLookAtRotation(cameraLocation, location) - cameraRotation).GetNormalized();
            const auto yawDelta = FMath::Abs(rotationDelta.Yaw);
            const auto pitchDelta = FMath::Abs(rotationDelta.Pitch);
            const auto sum = yawDelta + pitchDelta;

            if (sum < bestAim.best)
            {
                bestAim.target = actor;
                bestAim.location = location;
                bestAim.delta = rotationDelta;
                bestAim.best = sum;
            }
        }

        void Weapon::Aim(UWorld* world)
        {
            if (!bestAim.target)
            {
                return;
            }

            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;

            auto aimLocation = FVector{};
            if (bestAim.target->IsA(AAthenaCharacter::StaticClass()))
            {
                aimLocation = GetBoneLocation(reinterpret_cast<ACharacter*>(bestAim.target), EBones::CHEST__Skeleton);
            }
            else
            {
                aimLocation = bestAim.target->K2_GetActorLocation();
            }

            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(aimLocation, &position))
            {
                return;
            }
            bestAim.location = aimLocation;

            // FVector localVelocity = localPlayer->GetVelocity();
            auto localVelocity = FVector::ZeroVector;
            if (const auto localShip = reinterpret_cast<AAthenaCharacter*>(localPlayer)->GetCurrentShip())
            {
                localVelocity += localShip->GetVelocity();
            }

            auto targetVelocity = bestAim.target->GetVelocity();
            if (bestAim.target->IsA(AAthenaCharacter::StaticClass()))
            {
                if (const auto targetShip = reinterpret_cast<AAthenaCharacter*>(bestAim.target)->GetCurrentShip())
                {
                    targetVelocity += targetShip->GetVelocity();
                }
            }

            const auto relativeVelocity = targetVelocity - localVelocity;
            const auto projectileSpeed = weapon->WeaponParameters.AmmoParams.Velocity;
            const auto relativeLocation = localPlayer->K2_GetActorLocation() - bestAim.location;
            const auto a = relativeVelocity.Size() - projectileSpeed * projectileSpeed;
            const auto b = (relativeLocation * relativeVelocity * 2.f).Sum();
            const auto c = relativeLocation.SizeSquared();
            const auto d = b * b - 4 * a * c;

            if (d > 0)
            {
                const auto dRoot = std::sqrt(d);
                const auto x1 = (-b + dRoot) / (2 * a);
                const auto x2 = (-b - dRoot) / (2 * a);
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
                    bestAim.delta = (UKismetMathLibrary::FindLookAtRotation(cameraLocation, bestAim.location) - cameraRotation).GetNormalized();

                    // auto aimSpeed = 5.f;
                    // auto smoothness = 1.f / aimSpeed;
                    // playerController->AddYawInput(bestAim.delta.Yaw * smoothness);
                    // playerController->AddPitchInput(bestAim.delta.Pitch * -smoothness);

                    auto targetX = 0.f;
                    auto targetY = 0.f;

                    const auto centreX = centreScreen.X;
                    const auto centreY = centreScreen.Y;

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
