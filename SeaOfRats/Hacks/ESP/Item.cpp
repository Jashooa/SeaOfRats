#include "Item.h"

#include "Drawing.h"
#include "Utilities/Math.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawItem(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto item = reinterpret_cast<AFloatingItemProxy*>(actor);

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Colour
            ImU32 colour = Drawing::Colour::White;

            // Get item info
            if (const auto itemInfo = item->ItemInfo)
            {
                if (itemInfo->IsA(ABootyItemInfo::StaticClass()))
                {
                    const auto bootyItemInfo = reinterpret_cast<ABootyItemInfo*>(itemInfo);

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
                    else
                    {
                        colour = Drawing::Colour::Blue;
                    }
                }

                Drawing::DrawCircleFilled(position, 3.f, colour);

                if (!Utilities::PointInCircle(position, Drawing::GetScreenCentre(), 60.f) && !(GetAsyncKeyState('R') & 0x8000))
                {
                    return;
                }

                if (const auto itemDesc = itemInfo->Desc)
                {
                    // Get name
                    std::string name = UKismetTextLibrary::Conv_TextToString(itemDesc->Title).ToString();

                    // Get distance
                    const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                    name += " [" + std::to_string(distance) + "m]";

                    // Draw name
                    Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
                }
            }
        }
    }
}
