#include "EnchantedCompass.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void EnchantedCompass::Draw(UWorld* world, AActor* actor)
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
            const ImU32 colour = Utilities::Drawing::Colour::White;
            //Utilities::Drawing::DrawCircleFilled(position, 3.f, colour);
            Utilities::Drawing::DrawString(ICON_FA_COMPASS, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            std::string name = "Enchanted Compass Location";

            // Get distance
            const auto distance = static_cast<int>((localPlayer->K2_GetActorLocation() - location).Size() * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
        }

        void EnchantedCompass::DrawMultiTarget(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(playerController->Pawn);
            // const auto multiTargetEnchantedCompass = reinterpret_cast<AMultiTargetEnchantedCompass*>(actor);

            // Not mine
            if (actor->GetAttachParentActor() != localPlayer)
            {
                return;
            }

            /*const auto locations = multiTargetEnchantedCompass->Locations;

            for (int locationIndex = 0; locationIndex < locations.Num(); ++locationIndex)
            {
                const auto& location = locations[locationIndex];

                FVector2D position;
                if (!playerController->ProjectWorldLocationToScreen(location, &position))
                {
                    continue;
                }

                // Colour
                const ImU32 colour = Utilities::Drawing::Colour::White;
                //Utilities::Drawing::DrawCircleFilled(position, 3.f, colour);
                Utilities::Drawing::DrawString(ICON_FA_COMPASS, position, colour);

                if (!Utilities::General::NearCursor(position))
                {
                    return;
                }

                // Get name
                std::string name = "Enchanted Compass Location " + std::to_string(locationIndex + 1);

                // Get distance
                const auto distance = static_cast<int>((localPlayer->K2_GetActorLocation() - location).Size() * 0.01f);
                name += " [" + std::to_string(distance) + "m]";

                // Draw name
                Utilities::Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
            }*/
        }
    }
}
