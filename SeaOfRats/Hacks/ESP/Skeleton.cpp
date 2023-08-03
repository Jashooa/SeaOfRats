#include "Skeleton.h"

#include "Hacks/Bones.h"
#include "Utilities/Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Skeleton::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto skeleton = reinterpret_cast<AAthenaAICharacter*>(actor);

            // Get distance
            const auto worldDistance = localPlayer->GetDistanceTo(actor);
            const auto distance = worldDistance * 0.01f;
            if (distance >= 500.f)
            {
                return;
            }

            // Check if dead
            if (skeleton->IsDead())
            {
                return;
            }

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            FVector2D topPosition;
            if (!playerController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z + extent.Z }, &topPosition))
            {
                return;
            }

            // Get bottom coordinates
            FVector2D bottomPosition;
            if (!playerController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z - extent.Z }, &bottomPosition))
            {
                return;
            }

            // Colour
            const ImU32 colour = Utilities::Drawing::Colour::Orange;

            // Draw box
            Utilities::Drawing::DrawBoundingRect(world, actor, colour);

            // Draw health bar
            /*if (const auto healthComponent = skeleton->HealthComponent)
            {
                const float healthCurrent = healthComponent->GetCurrentHealth();
                const float healthMax = healthComponent->GetMaxHealth();
                Utilities::Drawing::DrawHealthBar({ topPosition.X, topPosition.Y -= 15.f }, healthCurrent, healthMax);
            }*/

            // Get name
            std::string name = "Skeleton";
            if (skeleton->AssignedMesh)
            {
                std::string meshName = skeleton->AssignedMesh->GetName();
                if (meshName.find("skellyshadow") != std::string::npos)
                {
                    name = "Shadow " + name;
                }
                else if (meshName.find("skellymetal") != std::string::npos)
                {
                    name = "Gold " + name;
                }
                else if (meshName.find("skellyplant") != std::string::npos)
                {
                    name = "Plant " + name;
                }
                else if (meshName.find("skellyash") != std::string::npos)
                {
                    name = "Ashen " + name;
                }
                else if (meshName.find("_goldhoarder_") != std::string::npos)
                {
                    name = "Gold Hoarder " + name;
                }

                if (meshName.find("_cap_") != std::string::npos)
                {
                    name += " Captain";
                }

                if (meshName.find("_lord_") != std::string::npos)
                {
                    name += " Lord";
                }

                name += " Mesh: " + meshName;

                /*if (skeleton->TeamColorTexture)
                {
                    std::string skeletonColour = skeleton->TeamColorTexture->GetName();
                    if (skeletonColour.find("venom") != std::string::npos)
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
                    }
                    if (skeletonColour.find("_red_") != std::string::npos)
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
                       //  name += " Texture: " + skeletonColour;
                    }
                }*/
            }

            /*auto namePlate = reinterpret_cast<UAINameplateComponent*>(skeleton->GetComponentByClass(UAINameplateComponent::StaticClass()));
            bool isNameplateShown = false;
            if (!namePlate->DisplayNameAsString.IsEmpty())
            {
                isNameplateShown = (worldDistance < namePlate->VisibleUntilWorldDistance) && playerController->LineOfSightTo(actor, FVector(0.f, 0.f, 0.f), false);
                std::wstring namePlateText = namePlate->DisplayNameAsString.c_str();
                name = namePlateText + L" " + name;
            }

            if (!isNameplateShown)
            {
                const auto distance = static_cast<int>(worldDistance * 0.01f);
                name += L" [" + std::to_wstring(distance) + L"m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topPosition.X, topPosition.Y - 10.f);
                Utilities::Drawing::DrawString(hud, name, nameScreen, Utilities::Drawing::Colour::White);
            }*/

            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, Utilities::Drawing::Colour::White);

            // Draw item info
            if (const auto wieldedItemComponent = skeleton->WieldedItemComponent)
            {
                if (const auto wieldedItem = reinterpret_cast<AWieldableItem*>(wieldedItemComponent->CurrentlyWieldedItem))
                {
                    if (const auto itemInfo = wieldedItem->ItemInfo)
                    {
                        if (const auto itemDesc = itemInfo->Desc)
                        {
                            const std::string itemName = itemDesc->Title.DisplayString->ToString();
                            Utilities::Drawing::DrawString(itemName, { bottomPosition.X, bottomPosition.Y += 15.f }, Utilities::Drawing::Colour::White);
                        }
                    }
                }
            }
        }
    }
}
