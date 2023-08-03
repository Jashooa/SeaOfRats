#include "Debug.h"

#include "Utilities/Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace Info
    {
        void Debug::Draw(UWorld* world)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(playerController->Pawn);
            const auto playerCamera = playerController->PlayerCameraManager;

            const FRotator rotation = playerCamera->GetCameraRotation();
            const FVector forwardVector = rotation.Vector();
            const FVector location = playerCamera->GetCameraLocation() + forwardVector;
            const FVector lookLocation = playerCamera->GetCameraLocation() + (forwardVector * 10000.f);
            FHitResult hitResult;
            if (UKismetSystemLibrary::LineTraceSingle_NEW(localPlayer, location, lookLocation, ETraceTypeQuery::TraceTypeQuery4, false, TArray<AActor*>(), EDrawDebugTrace::EDrawDebugTrace__None, true, &hitResult))
            {
                const auto actor = hitResult.Actor.Get();
                const auto hitLocation = hitResult.Location;
                FVector2D hitPosition;
                if (!playerController->ProjectWorldLocationToScreen(location, &hitPosition))
                {
                    return;
                }

                float x = 200.f;
                float y = 10.f;
                ImU32 colour = Utilities::Drawing::Colour::White;

                Utilities::Drawing::DrawString("X", { hitPosition.X, hitPosition.Y }, colour);
                Utilities::Drawing::DrawString("Name: " + actor->GetName(), { x, y }, colour, false);
                if (actor->InstanceComponents.Num() > 0)
                {
                    std::string tags = "Tags: ";
                    for (int i = 0; i < actor->Tags.Num(); ++i)
                    {
                        tags += actor->Tags[i].GetName();
                    }
                    Utilities::Drawing::DrawString(tags, { x, y += 15.f }, colour, false);
                }

                if (const auto item = actor->Owner)
                {
                    Utilities::Drawing::DrawString("Owner: " + item->GetName(), { x, y += 15.f }, colour, false);
                }

                if (const auto item = actor->RootComponent)
                {
                    Utilities::Drawing::DrawString("RootComponent: " + item->GetName(), { x, y += 15.f }, colour, false);
                }

                if (auto item = actor->ParentComponentActor.Actor)
                {
                    Utilities::Drawing::DrawString("Parents:", { x, y += 15.f }, colour, false);
                    while (item)
                    {
                        Utilities::Drawing::DrawString(item->GetName(), { x + 10.f, y += 15.f }, colour, false);
                        item = item->ParentComponentActor.Actor;

                        if (y > 1000.f)
                        {
                            x += 400.f;
                            y = 10.f;
                        }
                    }
                }

                if (actor->Children.Num() > 0)
                {
                    Utilities::Drawing::DrawString("Children:", { x, y += 15.f }, colour, false);
                    for (int i = 0; i < actor->Children.Num(); ++i)
                    {
                        if (const auto item = actor->Children[i])
                        {
                            Utilities::Drawing::DrawString(item->GetName(), { x + 10.f, y += 15.f }, colour, false);
                        }

                        if (y > 1000.f)
                        {
                            x += 400.f;
                            y = 10.f;
                        }
                    }
                }

                if (actor->ChildComponentActors.Num() > 0)
                {
                    Utilities::Drawing::DrawString("ChildComponentActors:", { x, y += 15.f }, colour, false);
                    for (int i = 0; i < actor->ChildComponentActors.Num(); ++i)
                    {
                        if (const auto item = actor->ChildComponentActors[i].Get())
                        {
                            Utilities::Drawing::DrawString(item->GetName(), { x + 10.f, y += 15.f }, colour, false);
                        }

                        if (y > 1000.f)
                        {
                            x += 400.f;
                            y = 10.f;
                        }
                    }
                }

                if (actor->BlueprintCreatedComponents.Num() > 0)
                {
                    Utilities::Drawing::DrawString("BlueprintCreatedComponents:", { x, y += 15.f }, colour, false);
                    for (int i = 0; i < actor->BlueprintCreatedComponents.Num(); ++i)
                    {
                        if (const auto item = actor->BlueprintCreatedComponents[i])
                        {
                            Utilities::Drawing::DrawString(item->GetName(), { x + 10.f, y += 15.f }, colour, false);
                        }

                        if (y > 1000.f)
                        {
                            x += 400.f;
                            y = 10.f;
                        }
                    }
                }

                if (actor->InstanceComponents.Num() > 0)
                {
                    Utilities::Drawing::DrawString("InstanceComponents:", { x, y += 15.f }, colour, false);
                    for (int i = 0; i < actor->InstanceComponents.Num(); ++i)
                    {
                        if (const auto item = actor->InstanceComponents[i])
                        {
                            Utilities::Drawing::DrawString(item->GetName(), { x + 10.f, y += 15.f }, colour, false);
                        }

                        if (y > 1000.f)
                        {
                            x += 400.f;
                            y = 10.f;
                        }
                    }
                }

                if (actor->ChildActorInterfaceProviders.Num() > 0)
                {
                    Utilities::Drawing::DrawString("ChildActorInterfaceProviders:", { x, y += 15.f }, colour, false);
                    for (int i = 0; i < actor->ChildActorInterfaceProviders.Num(); ++i)
                    {
                        if (const auto item = actor->ChildActorInterfaceProviders[i])
                        {
                            Utilities::Drawing::DrawString(item->GetName(), { x + 10.f, y += 15.f }, colour, false);
                        }

                        if (y > 1000.f)
                        {
                            x += 400.f;
                            y = 10.f;
                        }
                    }
                }
            }
        }
    }
}
