#include "EnchantedCompass.h"

#include "Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void DrawEnchantedCompass(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(playerController->Pawn);
            const auto enchantedCompass = reinterpret_cast<AEnchantedCompass*>(actor);

            // Not mine
            if (actor->GetAttachParentActor() != localPlayer)
            {
                return;
            }

            const auto location = enchantedCompass->Target.TargetLocation;
            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Colour
            ImU32 colour = Drawing::Colour::White;
            //Drawing::DrawCircleFilled(position, 3.f, colour);
            Drawing::DrawString(ICON_FA_COMPASS, position, colour);

            if (!Utilities::NearCursor(position))
            {
                return;
            }

            // Get name
            std::string name = "Enchanted Compass Location";

            // Get distance
            const int32_t distance = static_cast<int32_t>((localPlayer->K2_GetActorLocation() - location).Size() * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
        }

        void DrawMultiTargetEnchantedCompass(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(playerController->Pawn);
            const auto multiTargetEnchantedCompass = reinterpret_cast<AMultiTargetEnchantedCompass*>(actor);

            // Not mine
            if (actor->GetAttachParentActor() != localPlayer)
            {
                return;
            }

            /*const auto locations = multiTargetEnchantedCompass->Locations;

            for (auto locationIndex = 0; locationIndex < locations.Num(); ++locationIndex)
            {
                const auto& location = locations[locationIndex];

                FVector2D position;
                if (!playerController->ProjectWorldLocationToScreen(location, &position))
                {
                    continue;
                }

                // Colour
                ImU32 colour = Drawing::Colour::White;
                //Drawing::DrawCircleFilled(position, 3.f, colour);
                Drawing::DrawString(ICON_FA_COMPASS, position, colour);

                if (!Utilities::NearCursor(position))
                {
                    return;
                }

                // Get name
                std::string name = "Enchanted Compass Location " + std::to_string(locationIndex + 1);

                // Get distance
                const int32_t distance = static_cast<int32_t>((localPlayer->K2_GetActorLocation() - location).Size() * 0.01f);
                name += " [" + std::to_string(distance) + "m]";

                // Draw name
                Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
            }*/
        }
    }
}
