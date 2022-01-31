#include "Item.h"

#include "Drawing.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawItem(UWorld* world, AActor* actor)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto item = reinterpret_cast<ABootyProxy*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                ImU32 colour = Drawing::Colour::Blue;

                // Get item info
                if (!item->ItemInfo)
                {
                    return;
                }

                if (item->ItemInfo->IsA(ABootyItemInfo::StaticClass()))
                {
                    auto bootyItemInfo = reinterpret_cast<ABootyItemInfo*>(item->ItemInfo);

                    // Get colour
                    std::string rarity = bootyItemInfo->Rarity.GetName();
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

                // Get name
                std::string name = UKismetTextLibrary::Conv_TextToString(item->ItemInfo->Desc->Title).ToString();
                int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                name += " [" + std::to_string(distance) + "m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Drawing::DrawString(name, nameScreen, colour);
            }
        }
    }
}
