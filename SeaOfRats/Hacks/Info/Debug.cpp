#include "Debug.h"

#include "Drawing.h"

namespace Hacks
{
    namespace Info
    {
        void DrawDebug(UWorld* world)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(playerController->Pawn);
            auto playerCamera = playerController->PlayerCameraManager;

            FRotator rotation = playerCamera->GetCameraRotation();
            FVector forwardVector = UKismetMathLibrary::Conv_RotatorToVector(rotation);
            FVector position = playerCamera->GetCameraLocation() + forwardVector;
            FVector lookPosition = playerCamera->GetCameraLocation() + (forwardVector * 10000.f);
            FHitResult hitResult;
            bool hit = UKismetSystemLibrary::LineTraceSingle_NEW(localPlayer, position, lookPosition, ETraceTypeQuery::TraceTypeQuery1, false, TArray<AActor*>(), EDrawDebugTrace::EDrawDebugTrace__None, true, &hitResult);

            if (hit)
            {
                auto actor = hitResult.Actor.Get();
                auto hitPosition = hitResult.Location;

                float x = 10.f;
                float y = 10.f;
                ImU32 colour = Drawing::Colour::White;

                Drawing::DrawString("Name: " + actor->GetName(), FVector2D(x, y), colour, false);
                if (actor->InstanceComponents.Num() > 0)
                {
                    std::string tags = "Tags: ";
                    for (int32_t i = 0; i < actor->Tags.Num(); ++i)
                    {
                        tags += actor->Tags[i].GetName();
                    }
                    Drawing::DrawString(tags, FVector2D(x, y += 15.f), colour, false);
                }

                if (const auto item = actor->Owner)
                {
                    Drawing::DrawString("Owner: " + item->GetName(), FVector2D(x, y += 15.f), colour, false);
                }

                if (const auto item = actor->RootComponent)
                {
                    Drawing::DrawString("RootComponent: " + item->GetName(), FVector2D(x, y += 15.f), colour, false);
                }

                if (const auto item = actor->ParentComponentActor.Actor)
                {
                    Drawing::DrawString("ParentComponentActor: " + item->GetName(), FVector2D(x, y += 15.f), colour, false);
                }

                if (actor->ChildComponentActors.Num() > 0)
                {
                    Drawing::DrawString("ChildComponentActors:", FVector2D(x, y += 15.f), colour, false);
                    for (int32_t i = 0; i < actor->ChildComponentActors.Num(); ++i)
                    {
                        if (const auto item = actor->ChildComponentActors[i].Get())
                        {
                            Drawing::DrawString(item->GetName(), FVector2D(x + 10.f, y += 15.f), colour, false);
                        }
                    }
                }

                if (actor->ChildComponentActors.Num() > 0)
                {
                    Drawing::DrawString("BlueprintCreatedComponents:", FVector2D(x, y += 15.f), colour, false);
                    for (int32_t i = 0; i < actor->BlueprintCreatedComponents.Num(); ++i)
                    {
                        if (const auto item = actor->BlueprintCreatedComponents[i])
                        {
                            Drawing::DrawString(item->GetName(), FVector2D(x + 10.f, y += 15.f), colour, false);
                        }
                    }
                }

                if (actor->InstanceComponents.Num() > 0)
                {
                    Drawing::DrawString("InstanceComponents:", FVector2D(x, y += 15.f), colour, false);
                    for (int32_t i = 0; i < actor->InstanceComponents.Num(); ++i)
                    {
                        if (const auto item = actor->InstanceComponents[i])
                        {
                            Drawing::DrawString(item->GetName(), FVector2D(x + 10.f, y += 15.f), colour, false);
                        }
                    }
                }

                if (actor->ChildActorInterfaceProviders.Num() > 0)
                {
                    Drawing::DrawString("ChildActorInterfaceProviders:", FVector2D(x, y += 15.f), colour, false);
                    for (int32_t i = 0; i < actor->ChildActorInterfaceProviders.Num(); ++i)
                    {
                        if (const auto item = actor->ChildActorInterfaceProviders[i])
                        {
                            Drawing::DrawString(item->GetName(), FVector2D(x + 10.f, y += 15.f), colour, false);
                        }
                    }
                }
            }
        }
    }
}
