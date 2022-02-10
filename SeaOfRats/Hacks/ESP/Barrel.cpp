#include "Barrel.h"

#include "Drawing.h"
#include "Utilities/General.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawBarrel(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto barrel = reinterpret_cast<AStorageContainer*>(actor);

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
            ImU32 colour = Drawing::Colour::White;
            //Drawing::DrawCircleFilled(position, 3.f, colour);
            Drawing::DrawString(ICON_FA_BOX_OPEN, position, colour);

            if (!Utilities::NearCursor(position))
            {
                return;
            }

            // Get name
            std::string name = "Barrel";
            if (actor->IsA(ABuoyantStorageContainer::StaticClass()))
            {
                name = "Water " + name;
            }

            // Get distance
            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);

            if (const auto storageComponent = reinterpret_cast<UStorageContainerComponent*>(barrel->GetComponentByClass(UStorageContainerComponent::StaticClass())))
            {
                auto nodes = storageComponent->ContainerNodes.ContainerNodes;
                for (auto nodeIndex = 0; nodeIndex < nodes.Num(); ++nodeIndex)
                {
                    const auto& node = nodes[nodeIndex];
                    if (const UItemDesc* itemDesc = node.ItemDesc->CreateDefaultObject<UItemDesc>())
                    {
                        if (UKismetTextLibrary::TextIsEmpty(itemDesc->Title))
                        {
                            continue;
                        }
                        std::string itemName = UKismetTextLibrary::Conv_TextToString(itemDesc->Title).ToString();
                        itemName = std::to_string(node.NumItems) + "x " + itemName;

                        Drawing::DrawString(itemName, { position.X, position.Y + 15.f * (nodeIndex + 1) }, colour);
                    }
                }
            }
        }
    }
}
