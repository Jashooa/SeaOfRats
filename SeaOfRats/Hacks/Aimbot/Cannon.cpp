#include "Cannon.h"

#include <vector>

#include "Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace Aimbot
    {
        void InitCannon(UWorld* world)
        {

        }

        void CalculateAimCannon(UWorld* world, AActor* actor)
        {
        }

        void AimCannon(UWorld* world)
        {

        }

        void CannonTrace(UWorld* world)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(playerController->Pawn);

            const auto parent = localPlayer->GetAttachParentActor();
            if (parent && parent->IsA(ACannon::StaticClass()))
            {
                const auto cannon = reinterpret_cast<ACannon*>(parent);

                const float gravityScale = cannon->ProjectileGravityScale;
                const float gravity = 981.f * gravityScale;
                const float launchSpeed = cannon->ProjectileSpeed;

                FRotator angle = FRotator(cannon->ServerPitch, cannon->ServerYaw, 0.f);
                const FRotator compAngle = cannon->K2_GetActorRotation();
                angle += compAngle;

                //const FRotator angle = playerController->PlayerCameraManager->GetCameraRotation();

                const FVector forwardVector = UKismetMathLibrary::Conv_RotatorToVector(angle);
                FVector location = cannon->K2_GetActorLocation();
                location.Z += 100.f;
                location += forwardVector * 150.f;

                FVector velocity = forwardVector * launchSpeed;
                if (const auto parentShip = cannon->GetAttachParentActor())
                {
                    velocity += parentShip->GetVelocity();
                }

                std::vector<FVector> path;
                const float interval = 0.1f;
                TArray<AActor*> ignoreList;
                ignoreList.Push(localPlayer);
                for (auto i = 0; i < 500; ++i)
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
                            ImU32 colour = Drawing::Colour::Red;

                            AActor* hitActor = nullptr;
                            if (hitResult.Actor.Get())
                            {
                                hitActor = hitResult.Actor.Get();

                                if (hitActor->IsA(AShip::StaticClass()) || (hitActor->GetAttachParentActor() && hitActor->GetAttachParentActor()->IsA(AShip::StaticClass())))
                                {
                                    colour = Drawing::Colour::Green;
                                }

                                Drawing::DrawString(hitActor->GetName(), FVector2D(position.X, position.Y + 13.f), colour);
                            }
                            Drawing::DrawCircle(position, 3.f, colour);
                        }
                        break;
                    }

                    if (location == nextLocation)
                    {
                        break;
                    }

                    location = nextLocation;
                }

                Drawing::DrawPath(world, path, Drawing::Colour::White);
            }
        }
    }
}
