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

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 500.f)
            {
                return;
            }

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            if (!barrel->IsA(ABuoyantStorageContainer::StaticClass()))
            {
                location = origin;
            }

            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Colour
            const ImU32 colour = Utilities::Drawing::Colour::White;
            Utilities::Drawing::DrawString(ICON_FA_BOX_OPEN, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            std::string name = "Barrel";
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            if (actor->IsA(ABuoyantStorageContainer::StaticClass()))
            {
                name = "Water " + name;
            }

            // Draw name
            Utilities::Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);

            if (const auto storageComponent = reinterpret_cast<UStorageContainerComponent*>(barrel->GetComponentByClass(UStorageContainerComponent::StaticClass())))
            {
                const auto nodes = storageComponent->ContainerNodes.ContainerNodes;
                for (int nodeIndex = 0; nodeIndex < nodes.Num(); ++nodeIndex)
                {
                    const auto& node = nodes[nodeIndex];
                    if (const UItemDesc* itemDesc = node.ItemDesc->CreateDefaultObject<UItemDesc>())
                    {
                        std::string itemName = itemDesc->Title.DisplayString->ToString();
                        if (itemName.empty())
                        {
                            continue;
                        }
                        itemName = std::to_string(node.NumItems) + "x " + itemName;

                        Utilities::Drawing::DrawString(itemName, { position.X, position.Y + 15.f * (nodeIndex + 1) }, colour);
                    }
                }
            }
        }
    }
}
