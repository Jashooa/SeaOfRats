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
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Get bounds
            auto origin = FVector{};
            auto extent = FVector{};
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topPosition = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z + extent.Z }, &topPosition))
            {
                return;
            }

            // Get bottom coordinates
            auto bottomPosition = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z - extent.Z }, &bottomPosition))
            {
                return;
            }

            // Colour
            const auto colour = Utilities::Drawing::Colour::Orange;

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
            auto name = std::string{ "Skeleton" };
            if (skeleton->AssignedMesh)
            {
                auto meshName = skeleton->AssignedMesh->GetName();

                if (meshName.find("_crawler_") != std::string::npos)
                {
                    name = "Ocean Crawler";

                    if (meshName.find("_eel_") != std::string::npos)
                    {
                        name += " Eel";
                    }
                    else if (meshName.find("_hermit_") != std::string::npos)
                    {
                        name += " Hermit";
                    }
                    else if (meshName.find("_crab_") != std::string::npos)
                    {
                        name += " Crab";
                    }
                }

                if (meshName.find("_skellyshadow_") != std::string::npos)
                {
                    name = "Shadow " + name;
                }
                else if (meshName.find("_skellymetal_") != std::string::npos)
                {
                    name = "Gold " + name;
                }
                else if (meshName.find("_skellyplant_") != std::string::npos)
                {
                    name = "Plant " + name;
                }
                else if (meshName.find("_skellyash_") != std::string::npos)
                {
                    name = "Ashen " + name;
                }
                else if (meshName.find("_skellyancient_") != std::string::npos)
                {
                    name = "Ancient " + name;
                }
                else if (meshName.find("_goldhoarder_") != std::string::npos)
                {
                    name = "Gold Hoarder " + name;
                }

                if (meshName.find("_cap_") != std::string::npos)
                {
                    name += " Captain";
                }

                if (meshName.find("_lord_") != std::string::npos || meshName.find("_skellylord_") != std::string::npos)
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
                            const auto itemName = itemDesc->Title.DisplayString->ToString();
                            Utilities::Drawing::DrawString(itemName, { bottomPosition.X, bottomPosition.Y += 15.f }, Utilities::Drawing::Colour::White);
                        }
                    }
                }
            }
        }
    }
}
