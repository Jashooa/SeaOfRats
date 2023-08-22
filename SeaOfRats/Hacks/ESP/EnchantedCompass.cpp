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
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Colour
            const auto colour = Utilities::Drawing::Colour::White;
            Utilities::Drawing::DrawString(ICON_FA_COMPASS, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            auto name = std::string{ "Enchanted Compass Location" };

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

            for (int i = 0; i < locations.Num(); ++i)
            {
                const auto location = locations[i];

                auto position = FVector2D{};
                if (!playerController->ProjectWorldLocationToScreen(location, &position))
                {
                    continue;
                }

                // Colour
                const auto colour = Utilities::Drawing::Colour::White;
                //Utilities::Drawing::DrawCircleFilled(position, 3.f, colour);
                Utilities::Drawing::DrawString(ICON_FA_COMPASS, position, colour);

                if (!Utilities::General::NearCursor(position))
                {
                    return;
                }

                // Get name
                auto name = "Enchanted Compass Location " + std::to_string(i + 1);

                // Get distance
                const auto distance = static_cast<int>((localPlayer->K2_GetActorLocation() - location).Size() * 0.01f);
                name += " [" + std::to_string(distance) + "m]";

                // Draw name
                Utilities::Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
            }*/
        }
    }
}
