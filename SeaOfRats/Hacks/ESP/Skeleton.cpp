#include "Skeleton.h"

#include "Drawing.h"
#include "Hacks/Bones.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawSkeleton(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto skeleton = reinterpret_cast<AAthenaAICharacter*>(actor);

            // Check if dead
            if (skeleton->IsDead())
            {
                return;
            }

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }
            //Drawing::DrawBoundingBox(world, actor, Drawing::Colour::White);
            Drawing::DrawBoundingRect(world, actor, Drawing::Colour::Red);
            //DrawBones(world, actor);

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            const auto topLocation = FVector(location.X, location.Y, location.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get name
                std::string name = "Skeleton";
                /*if (skeleton->AssignedMesh)
                {
                    std::string meshName = skeleton->AssignedMesh->GetName();
                    if (meshName.find("skellyshadow") != std::string::npos)
                    {
                        name = "Shadow " + name;
                    }
                    else if (meshName.find("skellymetal") != std::string::npos)
                    {
                        name = "Metal " + name;
                    }
                    else if (meshName.find("skellyplant") != std::string::npos)
                    {
                        name = "Plant " + name;
                    }
                    else if (meshName.find("skellyash") != std::string::npos)
                    {
                        name = "Ashen " + name;
                    }

                    if (meshName.find("_cap_") != std::string::npos)
                    {
                        name += " Captain";
                    }

                    name += " Mesh: " + meshName;

                    if (skeleton->TeamColorTexture)
                    {
                        std::string skeletonColour = skeleton->TeamColorTexture->GetName();
                        /*if (skeletonColour.find("venom") != std::string::npos)
                        {
                            name = "Purple " + name;
                        }
                        else if (skeletonColour.find("shark") != std::string::npos)
                        {
                            name = "Blue " + name;
                        }
                        else if (skeletonColour.find("lightning") != std::string::npos)
                        {
                            name = "White " + name;
                        }
                        else if (skeletonColour.find("player") != std::string::npos)
                        {
                            name = "Pink " + name;
                        }
                        else if (skeletonColour.find("skeleton") != std::string::npos)
                        {
                            name = "Green " + name;
                        }*/
                        /*if (skeletonColour.find("_red_") != std::string::npos)
                        {
                            name = "Red " + name;
                        }
                        else if (skeletonColour.find("_green_") != std::string::npos)
                        {
                            name = "Green " + name;
                        }
                        else if (skeletonColour.find("_blue_") != std::string::npos)
                        {
                            name = "Blue " + name;
                        }
                        else
                        {
                            name += " Texture: " + skeletonColour;
                        }
                    }
                }*/

                const float worldDistance = localPlayer->GetDistanceTo(actor);

                /*auto namePlate = reinterpret_cast<UAINameplateComponent*>(skeleton->GetComponentByClass(UAINameplateComponent::StaticClass()));
                bool isNameplateShown = false;
                if (!namePlate->DisplayNameAsString.IsEmpty())
                {
                    isNameplateShown = (worldDistance < namePlate->VisibleUntilWorldDistance) && playerController->LineOfSightTo(actor, FVector(0.0f, 0.0f, 0.0f), false);
                    std::wstring namePlateText = namePlate->DisplayNameAsString.c_str();
                    name = namePlateText + L" " + name;
                }

                if (!isNameplateShown)
                {
                    int32_t distance = static_cast<int32_t>(worldDistance * 0.01f);
                    name += L" [" + std::to_wstring(distance) + L"m]";

                    // Draw name
                    FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                    Drawing::DrawString(hud, name, nameScreen, Drawing::Colour::White);
                }*/
                const int32_t distance = static_cast<int32_t>(worldDistance * 0.01f);
                name += " [" + std::to_string(distance) + "m]";

                // Draw name
                const FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Drawing::DrawString(name, nameScreen, Drawing::Colour::White);
            }

            // Get bottom coordinates
            const auto bottomLocation = FVector(location.X, location.Y, location.Z - extent.Z);
            FVector2D bottomScreen;
            if (playerController->ProjectWorldLocationToScreen(bottomLocation, &bottomScreen))
            {

                // Draw health bar
                /*if (const auto healthComponent = skeleton->HealthComponent)
                {
                    const FVector2D healthScreen = FVector2D(bottomScreen.X, bottomScreen.Y + 10.0f);
                    const FVector2D healthTopLeft = FVector2D(healthScreen.X - 50.0f, healthScreen.Y);
                    const FVector2D healthBottomRight = FVector2D(healthTopLeft.X + 100.0f, healthTopLeft.Y + 5.0f);
                    Drawing::DrawHealthBar(hud, healthTopLeft, healthBottomRight, healthComponent->GetCurrentHealth(), healthComponent->GetMaxHealth());
                }*/

                // Draw item info
                if (const auto wieldedItemComponent = skeleton->WieldedItemComponent)
                {
                    if (const auto wieldedItem = reinterpret_cast<AWieldableItem*>(wieldedItemComponent->CurrentlyWieldedItem))
                    {
                        if (const auto itemInfo = wieldedItem->ItemInfo)
                        {
                            if (const auto itemDesc = itemInfo->Desc)
                            {
                                const std::string itemName = UKismetTextLibrary::Conv_TextToString(itemDesc->Title).ToString();
                                const FVector2D itemScreen = FVector2D(bottomScreen.X, bottomScreen.Y + 10.0f);
                                Drawing::DrawString(itemName, itemScreen, Drawing::Colour::White);
                            }
                        }
                    }
                }
            }
        }
    }
}
