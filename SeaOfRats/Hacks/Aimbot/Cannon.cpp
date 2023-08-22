#include "Cannon.h"

#include <vector>

#include "Hacks/Aimbot/Aim.h"
#include "Utilities/Drawing.h"
#include "Utilities/Input.h"
#include "Utilities/Unreal.h"

using namespace SDK;

namespace Hacks
{
    namespace Aimbot
    {
        Cannon::BestAim Cannon::bestAim{};
        FVector Cannon::cannonLocation;
        FRotator Cannon::cannonRotation;
        ACannon* Cannon::cannon;
        FVector2D Cannon::centreScreen;

        void Cannon::InitAim(UWorld* world)
        {
            bestAim.target = nullptr;
            bestAim.best = FLT_MAX;
            cannon = nullptr;

            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaCharacter*>(playerController->Pawn);

            centreScreen = Utilities::Drawing::GetScreenCentre();

            if (const auto attachActor = localPlayer->GetAttachParentActor())
            {
                if (attachActor->IsA(ACannon::StaticClass()))
                {
                    cannon = reinterpret_cast<ACannon*>(attachActor);
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

            cannonLocation = playerController->PlayerCameraManager->GetCameraLocation();
            cannonRotation = cannon->K2_GetActorRotation();

            /*const auto angle = FRotator{cannon->ServerPitch, cannon->ServerYaw, 0.f} + cannonRotation;
            cannonLocation = cannon->K2_GetActorLocation();
            cannonLocation.Z += 100.f;
            cannonLocation += angle.Vector() * 150.f;*/

            /*float x = 600.f;
            float y = 200.f;
            auto serverAngles = FRotator{ cannon->ServerPitch, cannon->ServerYaw, 0.f };
            Utilities::Drawing::DrawString("Server Angles", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Pitch: " + std::to_string(serverAngles.Pitch), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw: " + std::to_string(serverAngles.Yaw), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            FRotator actorRotation = cannon->K2_GetActorRotation();
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
            Utilities::Drawing::DrawString("Pitch: " + std::to_string(cannon->PitchSpeed), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw: " + std::to_string(cannon->YawSpeed), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            Utilities::Drawing::DrawString("Projectile speed: " + std::to_string(cannon->ProjectileSpeed), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Projectile gravity: " + std::to_string(cannon->ProjectileGravityScale), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            if (const auto loadedItem = cannon->LoadedItemInfo)
            {
                Utilities::Drawing::DrawString("Loaded item: " + loadedItem->Desc->Title.DisplayString->ToString(), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            }

            Utilities::Drawing::DrawString("Camera Location", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("X: " + std::to_string(cannonLocation.X), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Y: " + std::to_string(cannonLocation.Y), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Z: " + std::to_string(cannonLocation.Z), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            FVector cannonLocation2 = cannon->K2_GetActorLocation();
            Utilities::Drawing::DrawString("Cannon Location", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("X: " + std::to_string(cannonLocation2.X), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Y: " + std::to_string(cannonLocation2.Y), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Z: " + std::to_string(cannonLocation2.Z), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            Utilities::Drawing::DrawString("Location", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("X: " + std::to_string(location.X), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Y: " + std::to_string(location.Y), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Z: " + std::to_string(location.Z), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            Utilities::Drawing::DrawString("Location Difference", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("X: " + std::to_string(cannonLocation.X - cannonLocation2.X), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Y: " + std::to_string(cannonLocation.Y - cannonLocation2.Y), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Z: " + std::to_string(cannonLocation.Z - cannonLocation2.Z), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);*/
        }

        void Cannon::CalculateAim(UWorld* world, AActor* actor)
        {
            if (!cannon)
            {
                return;
            }

            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;

            // Check if ship currently on
            if (actor == reinterpret_cast<AAthenaCharacter*>(localPlayer)->GetCurrentShip())
            {
                return;
            }

            // Check if out of range
            if (localPlayer->GetDistanceTo(actor) > 55000.f)
            {
                return;
            }

            auto location = actor->K2_GetActorLocation();
            auto velocity = actor->ReplicatedMovement.LinearVelocity;
            auto projectileGravityScale = cannon->ProjectileGravityScale;
            auto projectileSpeed = cannon->ProjectileSpeed;

            if (actor->IsA(AShip::StaticClass()))
            {
                const auto ship = reinterpret_cast<AShip*>(actor);

                // Check if dead
                const auto damage = ship->GetHullDamage();
                if (damage && damage->IsShipSinking())
                {
                    return;
                }

                /*if (auto water = reinterpret_cast<AShip*>(actor)->GetInternalWater())
                {
                    if (water->GetNormalizedWaterAmount() == 1.f)
                    {
                        return;
                    }
                }*/

                const auto loadedItem = cannon->LoadedItemInfo;
                if (loadedItem && loadedItem->Desc && loadedItem->Desc->Title.DisplayString->ToString() == "Chainshot")
                {
                    projectileGravityScale = 1.f;
                    auto masts = Utilities::Unreal::GetActorComponentsByClass(actor, AMast::StaticClass());
                    for (const auto mast : masts)
                    {
                        if (!reinterpret_cast<AMast*>(mast)->IsMastFullyDamaged())
                        {
                            location = mast->K2_GetActorLocation();
                            const auto up = mast->GetActorUpVector();
                            location += up * 1000.f;

                            break;
                        }
                    }
                }
                else
                {
                    if (damage)
                    {
                        const auto holeLocation = pickHoleToAim(damage, localPlayer);
                        if (holeLocation.Sum() != 9999.f)
                        {
                            location = holeLocation;
                        }
                    }
                }
            }
            else if (actor->IsA(AAggressiveGhostShip::StaticClass()))
            {
                const auto ghostShip = reinterpret_cast<AAggressiveGhostShip*>(actor);
                velocity = actor->GetActorForwardVector() * ghostShip->ShipState.ShipSpeed;
            }

            auto low = FRotator{};
            auto high = FRotator{};
            const auto angularVelocity = actor->ReplicatedMovement.AngularVelocity;
            if (AimAtShip(world, location, velocity, angularVelocity, cannonLocation, cannon->GetVelocity(), projectileSpeed, projectileGravityScale, low, high) < 1)
            // if (AimAtMovingTarget(world, location, velocity, cannonLocation, cannon->GetVelocity(), projectileSpeed, projectileGravityScale, low, high) < 1)
            // if (GetAimAngles(world, location, cannonLocation, projectileSpeed, projectileGravityScale, low, high) < 1)
            {
                return;
            }

            auto rotationDelta = (low - cannonRotation).GetNormalized();
            const auto yawDelta = FMath::Abs(rotationDelta.Yaw - cannon->ServerYaw);
            const auto pitchDelta = FMath::Abs(rotationDelta.Pitch - cannon->ServerPitch);
            const auto sum = yawDelta + pitchDelta;

            auto position = FVector2D{};
            if (playerController->ProjectWorldLocationToScreen(location, &position))
            {
                Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::Red);
            }

            if (sum < bestAim.best)
            {
                bestAim.target = actor;
                bestAim.location = location;
                bestAim.delta = rotationDelta;
                bestAim.best = sum;
            }
        }

        void Cannon::Aim(UWorld* world)
        {
            if (!bestAim.target)
            {
                return;
            }

            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            // const auto localPlayer = playerController->Pawn;

            auto position = FVector2D{};
            /*if (!playerController->ProjectWorldLocationToScreen(bestAim.location, &position))
            {
                return;
            }*/
            playerController->ProjectWorldLocationToScreen(bestAim.location, &position);

            /*float x = 200.f;
            float y = 200.f;
            Utilities::Drawing::DrawString("BestAim", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Pitch: " + std::to_string(bestAim.delta.Pitch), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw: " + std::to_string(bestAim.delta.Yaw), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            Utilities::Drawing::DrawString("Rotation Limits", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Pitch: " + std::to_string(cannon->PitchRange.LowerBound.Value) + " to " + std::to_string(cannon->PitchRange.UpperBound.Value), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw: " + std::to_string(cannon->YawRange.LowerBound.Value) + " to " + std::to_string(cannon->YawRange.UpperBound.Value), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);*/

            // bestAim.delta = FRotator(30.f, 0.f, 0.f);

            if (bestAim.delta.Pitch > cannon->PitchRange.UpperBound.Value
                || bestAim.delta.Pitch < cannon->PitchRange.LowerBound.Value
                || bestAim.delta.Yaw > cannon->YawRange.UpperBound.Value
                || bestAim.delta.Yaw < cannon->YawRange.LowerBound.Value)
            {
                if (!position.IsZero())
                {
                    Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::Red);
                }
            }
            else
            {
                if (!position.IsZero())
                {
                    Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::Green);
                }

                /*Utilities::Drawing::DrawString("Difference", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Pitch: " + std::to_string(cannon->ServerPitch - bestAim.delta.Pitch), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Yaw: " + std::to_string(cannon->ServerYaw - bestAim.delta.Yaw), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);*/

                if (Utilities::Input::IsKeyPressed(VK_MENU))
                {
                    // cannon->ForceAimCannon(bestAim.delta.Pitch, bestAim.delta.Yaw);
                    // mouse_event(MOUSEEVENTF_MOVE, 0, 1, NULL, NULL);
                    
                    // const auto targetX = -1.f * ((cannon->ServerYaw - bestAim.delta.Yaw) / 64.f) * centreScreen.X;
                    // const auto targetY = 3.f * ((cannon->ServerPitch - bestAim.delta.Pitch) / 75.f) * centreScreen.Y;
                    const auto targetX = -1.f * (30.f / cannon->YawSpeed) * ((cannon->ServerYaw - bestAim.delta.Yaw) / 64.f) * centreScreen.X;
                    const auto targetY = 1.f * (30.f / cannon->PitchSpeed) * ((cannon->ServerPitch - bestAim.delta.Pitch) / 75.f) * centreScreen.X * centreScreen.X / centreScreen.Y;

                    /*Utilities::Drawing::DrawString("Target", { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
                    Utilities::Drawing::DrawString("Y: " + std::to_string(targetY), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
                    Utilities::Drawing::DrawString("X: " + std::to_string(targetX), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);*/

                    Utilities::Input::MouseMove(static_cast<int>(targetX), static_cast<int>(targetY));
                }
            }
        }

        void Cannon::TracePath(UWorld* world)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(playerController->Pawn);

            if (cannon)
            {
                auto projectileGravityScale = cannon->ProjectileGravityScale;

                const auto loadedItem = cannon->LoadedItemInfo;
                if (loadedItem && loadedItem->Desc && loadedItem->Desc->Title.DisplayString->ToString() == "Chainshot")
                {
                    projectileGravityScale = 1.0f;
                }

                const auto gravity = 981.f * projectileGravityScale;
                const auto launchSpeed = cannon->ProjectileSpeed;

                const auto angle = FRotator{ cannon->ServerPitch, cannon->ServerYaw, 0.f } + cannonRotation;
                const auto forwardVector = angle.Vector();

                auto location = cannon->K2_GetActorLocation();
                location.Z += 100.f;
                location += forwardVector * 150.f;

                auto velocity = forwardVector * launchSpeed;
                if (const auto parentShip = cannon->GetAttachParentActor())
                {
                    velocity += parentShip->GetVelocity();
                }

                auto path = std::vector<FVector>{};
                auto ignoreList = TArray<AActor*>{};
                ignoreList.Push(localPlayer);
                const auto interval = 0.1f;
                for (int i = 0; i < 500; ++i)
                {
                    path.push_back(location);
                    auto newZ = velocity.Z - (gravity * interval);
                    auto move = FVector{
                        velocity.X * interval,
                        velocity.Y * interval,
                        ((velocity.Z + newZ) * 0.5f) * interval
                    };
                    velocity.Z = newZ;
                    auto nextLocation = location + move;
                    auto hitResult = FHitResult{};

                    if (UKismetSystemLibrary::LineTraceSingle_NEW(cannon, location, nextLocation, ETraceTypeQuery::TraceTypeQuery3, false, ignoreList, EDrawDebugTrace::EDrawDebugTrace__None, true, &hitResult))
                    {
                        auto position = FVector2D{};
                        if (world->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(nextLocation, &position))
                        {
                            auto colour = Utilities::Drawing::Colour::Red;

                            AActor* hitActor = nullptr;
                            if (hitResult.Actor.Get())
                            {
                                hitActor = hitResult.Actor.Get();

                                if (hitActor->IsA(AHullDamage::StaticClass()) 
                                    || (hitActor->GetAttachParentActor() && hitActor->GetAttachParentActor()->IsA(AShip::StaticClass()))
                                    || (hitActor->GetAttachParentActor() && hitActor->GetAttachParentActor()->GetAttachParentActor() && hitActor->GetAttachParentActor()->GetAttachParentActor()->IsA(AShip::StaticClass())))
                                {
                                    colour = Utilities::Drawing::Colour::Green;
                                }

                                // Utilities::Drawing::DrawString(hitActor->GetName(), FVector2D(position.X, position.Y + 13.f), colour);
                            }
                            Utilities::Drawing::DrawCircle(position, 3.f, colour);
                        }
                        break;
                    }

                    if (location == nextLocation)
                    {
                        break;
                    }

                    location = nextLocation;
                }

                Utilities::Drawing::DrawPath(world, path, Utilities::Drawing::Colour::White);
            }
        }

        FVector Cannon::pickHoleToAim(AHullDamage* damage, APawn* localPlayer)
        {
            auto foundLocation = FVector{ 0.f, 0.f, 9999.f };
            auto currentDist = 55000.f;

            for (const auto& hole : damage->BottomDeckDamageZones)
            {
                if (hole->DamageLevel < 3)
                {
                    const auto dist = localPlayer->GetDistanceTo(hole);
                    if (dist <= currentDist)
                    {
                        currentDist = dist;
                        foundLocation = hole->K2_GetActorLocation();
                    }
                }
            }

            if (foundLocation.Sum() != 9999.f)
            {
                return foundLocation;
            }

            for (const auto& hole : damage->MiddleDeckDamageZones)
            {
                if (hole->DamageLevel < 3)
                {
                    const auto dist = localPlayer->GetDistanceTo(hole);
                    if (dist <= currentDist)
                    {
                        currentDist = dist;
                        foundLocation = hole->K2_GetActorLocation();
                    }
                }
            }

            return foundLocation;
        }
    }
}
