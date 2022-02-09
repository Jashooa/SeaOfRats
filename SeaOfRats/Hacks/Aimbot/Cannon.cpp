#include "Cannon.h"

#include <vector>

#include "include/SDK/SDK.h"

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
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn);

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
                    if (UKismetSystemLibrary::LineTraceSingle_NEW(cannon, location, nextLocation, ETraceTypeQuery::TraceTypeQuery1, false, ignoreList, EDrawDebugTrace::EDrawDebugTrace__None, true, &hitResult))
                    {
                        FVector2D position{};
                        if (world->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(nextLocation, &position))
                        {
                            ImU32 colour = Drawing::Colour::Red;
                            /*if (hitResult.Actor.Get() && hitResult.Actor.Get()->IsA(AShip::StaticClass()))
                            {
                                colour = Drawing::Colour::Green;
                            }
                            Drawing::DrawString(hitResult.Actor.Get()->GetName(), screen, colour);*/
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
