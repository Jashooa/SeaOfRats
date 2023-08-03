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
        SDK::FVector Cannon::cameraLocation;
        SDK::ACannon* Cannon::cannon;
        SDK::FVector2D Cannon::centreScreen;

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
            }

            cameraLocation = playerController->PlayerCameraManager->GetCameraLocation();
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
            auto velocity = actor->GetVelocity();

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
                    auto masts = Utilities::Unreal::GetActorComponentsByClass(actor, AMast::StaticClass());
                    for (auto mast : masts)
                    {
                        if (!reinterpret_cast<AMast*>(mast)->IsMastFullyDamaged())
                        {
                            location = mast->K2_GetActorLocation();
                            const FVector up = mast->GetActorUpVector();
                            location += up * 1000.f;

                            break;
                        }
                    }
                }
                else
                {
                    if (damage)
                    {
                        FVector holeLocation = pickHoleToAim(damage, localPlayer);
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

                auto forward = actor->GetActorForwardVector();
                velocity = forward * ghostShip->ShipState.ShipSpeed;
            }

            FRotator low, high;
            const auto angularVelocity = actor->ReplicatedMovement.AngularVelocity;
            if (AimAtShip(location, velocity, angularVelocity, cameraLocation, cannon->GetVelocity(), cannon->ProjectileSpeed, cannon->ProjectileGravityScale, low, high) < 1)
            {
                return;
            }

            FRotator rotationDelta = low.GetNormalized();
            rotationDelta -= cannon->K2_GetActorRotation();
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

        void Cannon::Aim(UWorld* world)
        {
            if (!bestAim.target)
            {
                return;
            }

            // bestAim.delta = FRotator(30.f, 0.f, 0.f);

            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            // const auto localPlayer = playerController->Pawn;

            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(bestAim.location, &position))
            {
                return;
            }

            /*float x = 200.f;
            float y = 200.f;
            Utilities::Drawing::DrawString("BestAim", FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Pitch: " + std::to_string(bestAim.delta.Pitch), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw: " + std::to_string(bestAim.delta.Yaw), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);

            Utilities::Drawing::DrawString("Rotation Limits", FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Pitch: " + std::to_string(cannon->PitchRange.LowerBound.Value) + " to " + std::to_string(cannon->PitchRange.UpperBound.Value), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw: " + std::to_string(cannon->YawRange.LowerBound.Value) + " to " + std::to_string(cannon->YawRange.UpperBound.Value), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);*/

            if (bestAim.delta.Pitch > cannon->PitchRange.UpperBound.Value
                || bestAim.delta.Pitch < cannon->PitchRange.LowerBound.Value
                || bestAim.delta.Yaw > cannon->YawRange.UpperBound.Value
                || bestAim.delta.Yaw < cannon->YawRange.LowerBound.Value)
            {
                Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::Red);
            }
            else
            {
                Utilities::Drawing::DrawString("x", position, Utilities::Drawing::Colour::Green);

                /*Utilities::Drawing::DrawString("Difference", FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Pitch: " + std::to_string(cannon->ServerPitch - bestAim.delta.Pitch), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Yaw: " + std::to_string(cannon->ServerYaw - bestAim.delta.Yaw), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);*/

                /*Utilities::Drawing::DrawString("Target", FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Y: " + std::to_string(targetY), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("X: " + std::to_string(targetX), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);*/

                if (Utilities::Input::IsKeyPressed(VK_MENU))
                {
                    // cannon->ForceAimCannon(bestAim.delta.Pitch, bestAim.delta.Yaw);
                    // mouse_event(MOUSEEVENTF_MOVE, 0, 1, NULL, NULL);
                    
                    float targetX = (cannon->ServerYaw - bestAim.delta.Yaw) * -30.f;
                    float targetY = (cannon->ServerPitch - bestAim.delta.Pitch) * 20.f;
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
                const float gravityScale = cannon->ProjectileGravityScale;
                const float gravity = 981.f * gravityScale;
                const float launchSpeed = cannon->ProjectileSpeed;

                FRotator angle = FRotator(cannon->ServerPitch, cannon->ServerYaw, 0.f);
                const FRotator compAngle = cannon->K2_GetActorRotation();
                angle += compAngle;

                // const FRotator angle = playerController->PlayerCameraManager->GetCameraRotation();

                const FVector forwardVector = angle.Vector();
                FVector location = cannon->K2_GetActorLocation();
                location.Z += 100.f;
                location += forwardVector * 150.f;

                float x = 600.f;
                float y = 200.f;
                Utilities::Drawing::DrawString("Location", FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("X: " + std::to_string(location.X), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Y: " + std::to_string(location.Y), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Z: " + std::to_string(location.Z), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);

                Utilities::Drawing::DrawString("Camera Location", FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("X: " + std::to_string(cameraLocation.X), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Y: " + std::to_string(cameraLocation.Y), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Z: " + std::to_string(cameraLocation.Z), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);

                FVector cannonLocation = cannon->K2_GetActorLocation();
                Utilities::Drawing::DrawString("Cannon Location", FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("X: " + std::to_string(cannonLocation.X), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Y: " + std::to_string(cannonLocation.Y), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Z: " + std::to_string(cannonLocation.Z), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);

                FVector velocity = forwardVector * launchSpeed;
                if (const auto parentShip = cannon->GetAttachParentActor())
                {
                    velocity += parentShip->GetVelocity();
                }

                std::vector<FVector> path;
                const float interval = 0.1f;
                TArray<AActor*> ignoreList;
                ignoreList.Push(localPlayer);
                for (int i = 0; i < 500; ++i)
                {
                    path.push_back(location);
                    float newZ = velocity.Z - (gravity * interval);
                    FVector move(
                        velocity.X * interval,
                        velocity.Y * interval,
                        ((velocity.Z + newZ) * 0.5f) * interval
                    );
                    velocity.Z = newZ;
                    FVector nextLocation = location + move;
                    FHitResult hitResult;

                    if (UKismetSystemLibrary::LineTraceSingle_NEW(cannon, location, nextLocation, ETraceTypeQuery::TraceTypeQuery3, true, ignoreList, EDrawDebugTrace::EDrawDebugTrace__None, true, &hitResult))
                    {
                        FVector2D position{};
                        if (world->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(nextLocation, &position))
                        {
                            ImU32 colour = Utilities::Drawing::Colour::Red;

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

                /*float x = 600.f;
                float y = 200.f;
                FRotator serverAngles = FRotator(cannon->ServerPitch, cannon->ServerYaw, 0.f);
                Utilities::Drawing::DrawString("Server Angles", FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Pitch: " + std::to_string(serverAngles.Pitch), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Yaw: " + std::to_string(serverAngles.Yaw), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);

                FRotator actorRotation = cannon->K2_GetActorRotation();
                Utilities::Drawing::DrawString("Actor Rotation", FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Pitch: " + std::to_string(actorRotation.Pitch), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Yaw: " + std::to_string(actorRotation.Yaw), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);

                FRotator combinedRotation = serverAngles += actorRotation;
                combinedRotation.Normalize();
                Utilities::Drawing::DrawString("Combined Rotation", FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Pitch: " + std::to_string(combinedRotation.Pitch), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Yaw: " + std::to_string(combinedRotation.Yaw), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);

                FRotator cameraRotation = playerController->PlayerCameraManager->GetCameraRotation();
                Utilities::Drawing::DrawString("Camera Rotation", FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Pitch: " + std::to_string(cameraRotation.Pitch), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Yaw: " + std::to_string(cameraRotation.Yaw), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);

                FRotator rotationDifference = combinedRotation - cameraRotation;
                Utilities::Drawing::DrawString("Rotation Difference", FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Pitch: " + std::to_string(rotationDifference.Pitch), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Yaw: " + std::to_string(rotationDifference.Yaw), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);

                FRotator replicatedRotation = cannon->ReplicatedMovement.Rotation;
                Utilities::Drawing::DrawString("Replicated Rotation", FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Pitch: " + std::to_string(replicatedRotation.Pitch), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                Utilities::Drawing::DrawString("Yaw: " + std::to_string(replicatedRotation.Yaw), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);

                if (const auto loadedItem = cannon->LoadedItemInfo)
                {
                    Utilities::Drawing::DrawString("Loaded item: " + UKismetTextLibrary::Conv_TextToString(loadedItem->Desc->Title).ToString(), FVector2D(x, y += 15.f), Utilities::Drawing::Colour::Red, false);
                }*/

                Utilities::Drawing::DrawPath(world, path, Utilities::Drawing::Colour::White);
            }
        }

        FVector Cannon::pickHoleToAim(AHullDamage* damage, APawn* localPlayer)
        {
            FVector foundLocation = { 0.f, 0.f, 9999.f };
            float currentDist = 55000.f;
            const auto bottomHoles = damage->BottomDeckDamageZones;

            for (int i = 0; i < bottomHoles.Num(); ++i)
            {
                const auto hole = bottomHoles[i];
                if (hole->DamageLevel < 3)
                {
                    const float dist = localPlayer->GetDistanceTo(hole);
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

            const auto middleHoles = damage->MiddleDeckDamageZones;

            for (int i = 0; i < middleHoles.Num(); ++i)
            {
                const auto hole = middleHoles[i];
                if (hole->DamageLevel < 3)
                {
                    const float dist = localPlayer->GetDistanceTo(hole);
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
