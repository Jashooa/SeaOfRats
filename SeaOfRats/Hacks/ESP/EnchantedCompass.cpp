#include "EnchantedCompass.h"

#include "Drawing.h"

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
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get name
            std::string name = "Enchanted Compass Location";

            // Get distance
            const int32_t distance = static_cast<int32_t>((localPlayer->K2_GetActorLocation() - location).Size() * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Colour
            ImU32 colour = Drawing::Colour::White;
            Drawing::DrawCircleFilled(screen, 3.f, colour);

            // Draw name
            const FVector2D nameScreen = FVector2D(screen.X, screen.Y - 10.f);
            Drawing::DrawString(name, nameScreen, colour);
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

            const auto locations = multiTargetEnchantedCompass->Locations;

            for (auto locationIndex = 0; locationIndex < locations.Num(); ++locationIndex)
            {
                const auto& location = locations[locationIndex];

                FVector2D screen;
                if (!playerController->ProjectWorldLocationToScreen(location, &screen))
                {
                    continue;
                }

                // Get name
                std::string name = "Enchanted Compass Location " + std::to_string(locationIndex + 1);

                // Get distance
                const int32_t distance = static_cast<int32_t>((localPlayer->K2_GetActorLocation() - location).Size() * 0.01f);
                name += " [" + std::to_string(distance) + "m]";

                // Colour
                ImU32 colour = Drawing::Colour::White;
                Drawing::DrawCircleFilled(screen, 3.f, colour);

                // Draw name
                const FVector2D nameScreen = FVector2D(screen.X, screen.Y - 10.f);
                Drawing::DrawString(name, nameScreen, colour);
            }
        }
    }
}
