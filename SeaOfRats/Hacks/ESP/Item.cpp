#include "Item.h"

#include "Drawing.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawItem(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto item = reinterpret_cast<ABootyProxy*>(actor);

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            const auto topLocation = FVector(location.X, location.Y, location.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get item info
                if (const auto itemInfo = item->ItemInfo)
                {
                    // Colour
                    ImU32 colour = Drawing::Colour::Blue;

                    if (itemInfo->IsA(ABootyItemInfo::StaticClass()))
                    {
                        const auto bootyItemInfo = reinterpret_cast<ABootyItemInfo*>(itemInfo);

                        // Get colour
                        const std::string rarity = bootyItemInfo->Rarity.GetName();
                        if (rarity == "Common")
                        {
                            colour = Drawing::Colour::Grey;
                        }
                        else if (rarity == "Rare")
                        {
                            colour = Drawing::Colour::Green;
                        }
                        else if (rarity == "Legendary")
                        {
                            colour = Drawing::Colour::Purple;
                        }
                        else if (rarity == "Mythical")
                        {
                            colour = Drawing::Colour::Orange;
                        }
                    }

                    Drawing::DrawCircleFilled(screen, 3.0f, colour);

                    if (const auto itemDesc = itemInfo->Desc)
                    {
                        // Get name
                        std::string name = UKismetTextLibrary::Conv_TextToString(itemDesc->Title).ToString();
                        const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                        name += " [" + std::to_string(distance) + "m]";

                        // Draw name
                        const FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                        Drawing::DrawString(name, nameScreen, colour);
                    }
                }
            }
        }
    }
}
