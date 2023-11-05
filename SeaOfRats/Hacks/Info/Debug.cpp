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

            const auto rotation = playerCamera->GetCameraRotation();
            const auto forwardVector = rotation.Vector();
            const auto location = playerCamera->GetCameraLocation() + forwardVector;
            const auto lookLocation = playerCamera->GetCameraLocation() + (forwardVector * 200000.f);
            auto hitResult = FHitResult{};
            if (UKismetSystemLibrary::LineTraceSingle_NEW(localPlayer, location, lookLocation, ETraceTypeQuery::TraceTypeQuery4, false, TArray<AActor*>(), EDrawDebugTrace::EDrawDebugTrace__None, true, &hitResult))
            {
                const auto actor = hitResult.Actor.Get();
                const auto hitLocation = hitResult.Location;
                auto hitPosition = FVector2D{};
                if (!playerController->ProjectWorldLocationToScreen(location, &hitPosition))
                {
                    return;
                }

                auto x = 200.f;
                auto y = 10.f;
                auto colour = Utilities::Drawing::Colour::White;

                Utilities::Drawing::DrawString("Name: " + actor->GetFullName(), { x, y }, colour, false);
                if (actor->Tags.Num() > 0)
                {
                    auto tags = std::string{ "Tags:" };
                    for (const auto& tag : actor->Tags)
                    {
                        tags += " " + tag.GetName();
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
                    for (const auto& item : actor->Children)
                    {
                        if (item)
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
                    for (const auto& item : actor->ChildComponentActors)
                    {
                        if (const auto itemActor = item.Get())
                        {
                            Utilities::Drawing::DrawString(itemActor->GetName(), { x + 10.f, y += 15.f }, colour, false);
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
                    for (const auto& item : actor->BlueprintCreatedComponents)
                    {
                        if (item)
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
                    for (const auto& item : actor->InstanceComponents)
                    {
                        if (item)
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
                    for (const auto& item : actor->ChildActorInterfaceProviders)
                    {
                        if (item)
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

        /*void DrawDebug(UWorld* world, AActor* actor)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;

            auto location = actor->K2_GetActorLocation();
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            std::string name = actor->GetName();
            if (name.find("_") != std::string::npos)
                return;
            if (name.find("cmn") != std::string::npos)
                return;
            if (name.find("wsp") != std::string::npos)
                return;
            if (name.find("vfx") != std::string::npos)
                return;
            if (name.find("ske") != std::string::npos)
                return;
            if (name.find("dvr") != std::string::npos)
                return;
            if (name.find("ref") != std::string::npos)
                return;
            if (name.find("bp") != std::string::npos)
                return;
            if (name.find("bld") != std::string::npos)
                return;
            if (name.find("bsp") != std::string::npos)
                return;
            if (name.find("wpn") != std::string::npos)
                return;
            if (name.find("tls") != std::string::npos)
                return;
            if (name.find("wld_feature") != std::string::npos)
                return;
            if (name.find("Copied") != std::string::npos)
                return;
            if (name.find("NavBlocker") != std::string::npos)
                return;
            if (name.find("NavMesh") != std::string::npos)
                return;
            if (name.find("Light") != std::string::npos)
                return;
            if (name.find("water") != std::string::npos)
                return;
            if (name.find("Water") != std::string::npos)
                return;
            if (name.find("rocks") != std::string::npos)
                return;
            if (name.find("jetty") != std::string::npos)
                return;
            if (name.find("shop") != std::string::npos)
                return;
            if (name.find("volume") != std::string::npos)
                return;
            if (name.find("Volume") != std::string::npos)
                return;
            if (name.find("NulVol") != std::string::npos)
                return;
            if (name.find("PhasedClusterRoot") != std::string::npos)
                return;
            if (name.find("StaticMeshActor") != std::string::npos)
                return;
            //name = actor->GetFullName();
            Utilities::Drawing::DrawString(name, screen, Utilities::Drawing::Colour::Red);
        }*/
    }
}
