#include "Harpoon.h"

#include "Utilities/Drawing.h"
#include "Utilities/Input.h"
#include "Utilities/Math.h"

using namespace SDK;

namespace Hacks
{
    namespace Aimbot
    {
        Harpoon::BestAim Harpoon::bestAim{};
        SDK::FVector Harpoon::harpoonLocation;
        SDK::FRotator Harpoon::harpoonRotation;
        SDK::AHarpoonLauncher* Harpoon::harpoon;
        SDK::FVector2D Harpoon::centreScreen;

        void Harpoon::InitAim(UWorld* world)
        {
            bestAim.target = nullptr;
            bestAim.best = FLT_MAX;
            harpoon = nullptr;

            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaCharacter*>(playerController->Pawn);

            centreScreen = Utilities::Drawing::GetScreenCentre();

            if (const auto attachActor = localPlayer->GetAttachParentActor())
            {
                if (attachActor->IsA(AHarpoonLauncher::StaticClass()))
                {
                    harpoon = reinterpret_cast<AHarpoonLauncher*>(attachActor);
                    Utilities::Drawing::DrawCircle(centreScreen, aimRadius, Utilities::Drawing::Colour::Red);
                }
                else
                {
                    return;
                }
            }
            else
            {
                return;
            }

            harpoonLocation = playerController->PlayerCameraManager->GetCameraLocation();
            harpoonRotation = harpoon->K2_GetActorRotation();

            /*float x = 600.f;
            float y = 200.f;
            auto serverAngles = FRotator{ harpoon->ReplicatedPitch, harpoon->ReplicatedYaw, 0.f };
            Utilities::Drawing::DrawString("Server Angles", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Pitch: " + std::to_string(serverAngles.Pitch), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw: " + std::to_string(serverAngles.Yaw), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            FRotator actorRotation = harpoon->K2_GetActorRotation();
            Utilities::Drawing::DrawString("Actor Rotation", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Pitch: " + std::to_string(actorRotation.Pitch), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw: " + std::to_string(actorRotation.Yaw), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            FRotator combinedRotation = serverAngles += actorRotation;
            combinedRotation.Normalize();
            Utilities::Drawing::DrawString("Combined Rotation", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Pitch: " + std::to_string(combinedRotation.Pitch), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw: " + std::to_string(combinedRotation.Yaw), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            FRotator cameraRotation = playerController->PlayerCameraManager->GetCameraRotation();
            Utilities::Drawing::DrawString("Camera Rotation", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Pitch: " + std::to_string(cameraRotation.Pitch), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw: " + std::to_string(cameraRotation.Yaw), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            FRotator rotationDifference = combinedRotation - cameraRotation;
            Utilities::Drawing::DrawString("Rotation Difference", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Pitch: " + std::to_string(rotationDifference.Pitch), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw: " + std::to_string(rotationDifference.Yaw), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            Utilities::Drawing::DrawString("Speed", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Pitch: " + std::to_string(harpoon->PitchSpeed), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw: " + std::to_string(harpoon->YawSpeed), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            Utilities::Drawing::DrawString("Camera Location", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("X: " + std::to_string(harpoonLocation.X), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Y: " + std::to_string(harpoonLocation.Y), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Z: " + std::to_string(harpoonLocation.Z), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            FVector harpoonLocation2 = harpoon->K2_GetActorLocation();
            Utilities::Drawing::DrawString("Cannon Location", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("X: " + std::to_string(harpoonLocation2.X), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Y: " + std::to_string(harpoonLocation2.Y), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Z: " + std::to_string(harpoonLocation2.Z), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            const auto angle = FRotator{ harpoon->ReplicatedPitch, harpoon->ReplicatedYaw, 0.f } + harpoonRotation;
            const auto forwardVector = angle.Vector();
            auto location = harpoon->K2_GetActorLocation();
            location.Z += 100.f;
            location += forwardVector * 150.f;
            Utilities::Drawing::DrawString("Location", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("X: " + std::to_string(location.X), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Y: " + std::to_string(location.Y), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Z: " + std::to_string(location.Z), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);*/
        }

        void Harpoon::CalculateAim(UWorld* world, AActor* actor)
        {
            if (!harpoon)
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
                // return;
            }

            // Check if out of range
            const auto distance = localPlayer->GetDistanceTo(actor);
            if (distance > harpoon->MaximumTetherLengthCm)
            {
                return;
            }

            // Check if have line of sight
            // if (!playerController->LineOfSightTo(actor, harpoonLocation, false))
            auto ignoreList = TArray<AActor*>{};
            ignoreList.Push(localPlayer);
            auto hitResult = FHitResult{};
            if (UKismetSystemLibrary::LineTraceSingle_NEW(harpoon, harpoonLocation, location, ETraceTypeQuery::TraceTypeQuery1, false, ignoreList, EDrawDebugTrace::EDrawDebugTrace__None, true, &hitResult))
            {
                return;
            }

            auto rotationDelta = (UKismetMathLibrary::FindLookAtRotation(harpoonLocation, location) - harpoonRotation).GetNormalized();
            const auto yawDelta = FMath::Abs(rotationDelta.Yaw - harpoon->ReplicatedYaw);
            const auto pitchDelta = FMath::Abs(rotationDelta.Pitch - harpoon->ReplicatedPitch);
            const auto sum = yawDelta + pitchDelta;

            Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::Red);
            Utilities::Drawing::DrawString(std::to_string(sum), {position.X, position.Y + 15.f}, Utilities::Drawing::Colour::Red, true);
            Utilities::Drawing::DrawString("Yaw: " + std::to_string(rotationDelta.Yaw), {position.X, position.Y + 30.f}, Utilities::Drawing::Colour::Red, true);
            Utilities::Drawing::DrawString("Pitch: " + std::to_string(rotationDelta.Pitch), {position.X, position.Y + 45.f}, Utilities::Drawing::Colour::Red, true);

            if (sum < bestAim.best)
            {
                bestAim.target = actor;
                bestAim.location = location;
                bestAim.delta = rotationDelta;
                bestAim.best = sum;
            }
        }

        void Harpoon::Aim(UWorld* world)
        {
            if (!bestAim.target)
            {
                return;
            }

            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            // const auto localPlayer = playerController->Pawn;

            auto aimLocation = bestAim.target->K2_GetActorLocation();

            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(aimLocation, &position))
            {
                return;
            }
            bestAim.location = aimLocation;

            // auto localVelocity = localPlayer->GetVelocity();
            auto localVelocity = FVector::ZeroVector;
            auto targetVelocity = bestAim.target->GetVelocity();

            const auto relativeVelocity = targetVelocity - localVelocity;
            const auto projectileSpeed = harpoon->ProjectileSpeed;
            const auto relativeLocation = harpoonLocation - bestAim.location;
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

                auto rotationDelta = UKismetMathLibrary::FindLookAtRotation(harpoonLocation, bestAim.location);
                rotationDelta -= harpoonRotation;
                rotationDelta.Normalize();
                bestAim.delta = rotationDelta;

                auto x = 200.f;
                auto y = 200.f;
                Utilities::Drawing::DrawString("Rotation Limits", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Pitch: " + std::to_string(harpoon->PitchRange.LowerBound.Value) + " to " + std::to_string(harpoon->PitchRange.UpperBound.Value), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Yaw: " + std::to_string(harpoon->YawRange.LowerBound.Value) + " to " + std::to_string(harpoon->YawRange.UpperBound.Value), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

                Utilities::Drawing::DrawString("BestAim", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Pitch: " + std::to_string(bestAim.delta.Pitch), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Yaw: " + std::to_string(bestAim.delta.Yaw), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Velocity: " + std::to_string(projectileSpeed), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

                Utilities::Drawing::DrawString("Difference", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Pitch: " + std::to_string(harpoon->ReplicatedPitch - bestAim.delta.Pitch), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Yaw: " + std::to_string(harpoon->ReplicatedYaw - bestAim.delta.Yaw), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

                if (bestAim.delta.Pitch > harpoon->PitchRange.UpperBound.Value
                    || bestAim.delta.Pitch < harpoon->PitchRange.LowerBound.Value
                    || bestAim.delta.Yaw > harpoon->YawRange.UpperBound.Value
                    || bestAim.delta.Yaw < harpoon->YawRange.LowerBound.Value)
                {
                    Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::Red);
                }
                else
                {
                    Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::Green);

                    if (Utilities::Input::IsKeyPressed(VK_MENU))
                    {
                        const auto targetX = -1.f * (30.f / harpoon->YawSpeed) * ((harpoon->ReplicatedYaw - bestAim.delta.Yaw) / 100.f) * centreScreen.X;
                        const auto targetY = 1.f * (30.f / harpoon->PitchSpeed) * ((harpoon->ReplicatedPitch - bestAim.delta.Pitch) / 102.f) * centreScreen.X * centreScreen.X / centreScreen.Y;

                        Utilities::Drawing::DrawString("Target", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
                        Utilities::Drawing::DrawString("Y: " + std::to_string(targetY), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
                        Utilities::Drawing::DrawString("X: " + std::to_string(targetX), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

                        Utilities::Input::MouseMove(static_cast<int>(targetX), static_cast<int>(targetY));
                    }
                }
            }
        }
    }
}
