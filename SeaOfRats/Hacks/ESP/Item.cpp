#include "Item.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Item::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto item = reinterpret_cast<AFloatingItemProxy*>(actor);

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 500.f)
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

            // Colour
            ImU32 colour = Utilities::Drawing::Colour::White;

            // Get item info
            if (const auto itemInfo = item->ItemInfo)
            {
                if (itemInfo->IsA(ABootyItemInfo::StaticClass()))
                {
                    const auto bootyItemInfo = reinterpret_cast<ABootyItemInfo*>(itemInfo);

                    const std::string rarity = bootyItemInfo->Rarity.GetName();
                    if (rarity == "Common")
                    {
                        colour = Utilities::Drawing::Colour::Grey;
                    }
                    else if (rarity == "Rare")
                    {
                        colour = Utilities::Drawing::Colour::Green;
                    }
                    else if (rarity == "Legendary")
                    {
                        colour = Utilities::Drawing::Colour::Purple;
                    }
                    else if (rarity == "Mythical")
                    {
                        colour = Utilities::Drawing::Colour::Orange;
                    }
                    else
                    {
                        colour = Utilities::Drawing::Colour::Blue;
                    }
                }

                //Utilities::Drawing::DrawCircleFilled(position, 3.f, colour);
                Utilities::Drawing::DrawString(ICON_FA_GEM, position, colour);

                if (!Utilities::General::NearCursor(position))
                {
                    return;
                }

                if (const auto itemDesc = itemInfo->Desc)
                {
                    // Get name
                    std::string name = itemDesc->Title.DisplayString->ToString();
                    name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

                    // Draw name
                    Utilities::Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
                }
            }
        }
    }
}
