#include "Barrel.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Barrel::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto barrel = reinterpret_cast<AStorageContainer*>(actor);

            // Ignore if ship component
            if (actor->ParentComponentActor.Actor && actor->ParentComponentActor.Actor->IsA(AShip::StaticClass()))
            {
                return;
            }

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 500.f)
            {
                return;
            }

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();

            // Get bounds
            auto origin = FVector{};
            auto extent = FVector{};
            actor->GetActorBounds(true, &origin, &extent);

            if (!actor->IsA(ABuoyantStorageContainer::StaticClass()))
            {
                location = origin;
            }

            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            auto topPosition = position;
            auto bottomPosition = position;

            // Colour
            const auto colour = Utilities::Drawing::Colour::White;
            Utilities::Drawing::DrawString(ICON_FA_BOX_OPEN, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            auto name = std::string{ "Barrel" };
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            if (actor->IsA(ABuoyantStorageContainer::StaticClass()))
            {
                name = "Water " + name;
            }

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);

            // Draw contents
            if (const auto storageComponent = reinterpret_cast<UStorageContainerComponent*>(barrel->GetComponentByClass(UStorageContainerComponent::StaticClass())))
            {
                for (const auto& node : storageComponent->ContainerNodes.ContainerNodes)
                {
                    if (const UItemDesc* itemDesc = node.ItemDesc->CreateDefaultObject<UItemDesc>())
                    {
                        auto itemName = itemDesc->Title.DisplayString->ToString();
                        if (itemName.empty())
                        {
                            continue;
                        }
                        itemName = std::to_string(node.NumItems) + "x " + itemName;

                        Utilities::Drawing::DrawString(itemName, { bottomPosition.X, bottomPosition.Y += 15.f }, colour);
                    }
                }
            }
        }
    }
}
