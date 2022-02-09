#include "Debug.h"

#include "Drawing.h"

namespace Hacks
{
    namespace Info
    {
        void DrawDebug(UWorld* world)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(playerController->Pawn);
            const auto playerCamera = playerController->PlayerCameraManager;

            const FRotator rotation = playerCamera->GetCameraRotation();
            const FVector forwardVector = UKismetMathLibrary::Conv_RotatorToVector(rotation);
            const FVector position = playerCamera->GetCameraLocation() + forwardVector;
            const FVector lookPosition = playerCamera->GetCameraLocation() + (forwardVector * 10000.f);
            FHitResult hitResult;
            if (UKismetSystemLibrary::LineTraceSingle_NEW(localPlayer, position, lookPosition, ETraceTypeQuery::TraceTypeQuery4, false, TArray<AActor*>(), EDrawDebugTrace::EDrawDebugTrace__None, true, &hitResult))
            {
                const auto actor = hitResult.Actor.Get();
                const auto hitPosition = hitResult.Location;

                float x = 10.f;
                float y = 10.f;
                ImU32 colour = Drawing::Colour::White;

                Drawing::DrawString("Name: " + actor->GetName(), { x, y }, colour, false);
                if (actor->InstanceComponents.Num() > 0)
                {
                    std::string tags = "Tags: ";
                    for (int32_t i = 0; i < actor->Tags.Num(); ++i)
                    {
                        tags += actor->Tags[i].GetName();
                    }
                    Drawing::DrawString(tags, { x, y += 15.f }, colour, false);
                }

                if (const auto item = actor->Owner)
                {
                    Drawing::DrawString("Owner: " + item->GetName(), { x, y += 15.f }, colour, false);
                }

                if (const auto item = actor->RootComponent)
                {
                    Drawing::DrawString("RootComponent: " + item->GetName(), { x, y += 15.f }, colour, false);
                }

                if (const auto item = actor->ParentComponentActor.Actor)
                {
                    Drawing::DrawString("ParentComponentActor: " + item->GetName(), { x, y += 15.f }, colour, false);
                }

                if (actor->Children.Num() > 0)
                {
                    Drawing::DrawString("Children:", { x, y += 15.f }, colour, false);
                    for (int32_t i = 0; i < actor->Children.Num(); ++i)
                    {
                        if (const auto item = actor->Children[i])
                        {
                            Drawing::DrawString(item->GetName(), { x + 10.f, y += 15.f }, colour, false);
                        }
                    }
                }

                if (actor->ChildComponentActors.Num() > 0)
                {
                    Drawing::DrawString("ChildComponentActors:", { x, y += 15.f }, colour, false);
                    for (int32_t i = 0; i < actor->ChildComponentActors.Num(); ++i)
                    {
                        if (const auto item = actor->ChildComponentActors[i].Get())
                        {
                            Drawing::DrawString(item->GetName(), { x + 10.f, y += 15.f }, colour, false);
                        }
                    }
                }

                if (actor->ChildComponentActors.Num() > 0)
                {
                    Drawing::DrawString("BlueprintCreatedComponents:", { x, y += 15.f }, colour, false);
                    for (int32_t i = 0; i < actor->BlueprintCreatedComponents.Num(); ++i)
                    {
                        if (const auto item = actor->BlueprintCreatedComponents[i])
                        {
                            Drawing::DrawString(item->GetName(), { x + 10.f, y += 15.f }, colour, false);
                        }
                    }
                }

                if (actor->InstanceComponents.Num() > 0)
                {
                    Drawing::DrawString("InstanceComponents:", { x, y += 15.f }, colour, false);
                    for (int32_t i = 0; i < actor->InstanceComponents.Num(); ++i)
                    {
                        if (const auto item = actor->InstanceComponents[i])
                        {
                            Drawing::DrawString(item->GetName(), { x + 10.f, y += 15.f }, colour, false);
                        }
                    }
                }

                if (actor->ChildActorInterfaceProviders.Num() > 0)
                {
                    Drawing::DrawString("ChildActorInterfaceProviders:", { x, y += 15.f }, colour, false);
                    for (int32_t i = 0; i < actor->ChildActorInterfaceProviders.Num(); ++i)
                    {
                        if (const auto item = actor->ChildActorInterfaceProviders[i])
                        {
                            Drawing::DrawString(item->GetName(), { x + 10.f, y += 15.f }, colour, false);
                        }
                    }
                }
            }
        }
    }
}
