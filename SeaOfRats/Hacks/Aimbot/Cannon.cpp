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
            auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn);

            auto parent = localPlayer->GetAttachParentActor();
            if (parent && parent->IsA(ACannon::StaticClass()))
            {
                auto cannon = reinterpret_cast<ACannon*>(parent);

                float gravityScale = cannon->ProjectileGravityScale;
                float gravity = 981.f * gravityScale;
                float launchSpeed = cannon->ProjectileSpeed;

                FRotator angle = FRotator(cannon->ServerPitch, cannon->ServerYaw, 0.f);
                FRotator compAngle = cannon->K2_GetActorRotation();
                angle += compAngle;

                FVector forwardVector = UKismetMathLibrary::Conv_RotatorToVector(angle);
                FVector position = cannon->K2_GetActorLocation();
                position.Z += 100.f;
                position += forwardVector * 150.f;

                FVector velocity = forwardVector * launchSpeed;
                if (const auto parentShip = cannon->GetAttachParentActor())
                {
                    velocity += parentShip->GetVelocity();
                }

                std::vector<FVector> path;
                const float interval = 0.1f;
                TArray<AActor*> ignoreList;
                ignoreList.Push(localPlayer);
                for (int32_t i = 0; i < 500; ++i)
                {
                    path.push_back(position);
                    float newZ = velocity.Z - (gravity * interval);
                    FVector move(
                        velocity.X * interval,
                        velocity.Y * interval,
                        ((velocity.Z + newZ) * 0.5f) * interval
                    );
                    velocity.Z = newZ;
                    FVector nextPosition = position + move;
                    FHitResult hitResult;
                    if (UKismetSystemLibrary::LineTraceSingle_NEW(cannon, position, nextPosition, ETraceTypeQuery::TraceTypeQuery1, false, ignoreList, EDrawDebugTrace::EDrawDebugTrace__None, true, &hitResult))
                    {
                        FVector2D screen{};
                        if (world->OwningGameInstance->LocalPlayers[0]->PlayerController->ProjectWorldLocationToScreen(nextPosition, &screen))
                        {
                            ImU32 colour = Drawing::Colour::Green;
                            /*if (hitResult.Actor.Get() && hitResult.Actor.Get()->IsA(AShip::StaticClass()))
                            {
                                colour = Drawing::Colour::Green;
                            }
                            Drawing::DrawString(hitResult.Actor.Get()->GetName(), screen, colour);*/
                            Drawing::DrawCircle(screen, 3.f, colour);
                        }
                        break;
                    }
                    if (position == nextPosition)
                    {
                        break;
                    }
                    position = nextPosition;
                }

                Drawing::DrawPath(world, path, Drawing::Colour::White);

            }
        }
    }
}
