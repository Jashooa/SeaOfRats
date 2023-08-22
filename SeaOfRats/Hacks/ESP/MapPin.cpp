#include "MapPin.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void MapPin::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto table = reinterpret_cast<AMapTable*>(actor);

            // Check if not on current ship
            if (const auto parentShip = actor->GetAttachParentActor())
            {
                if (!UCrewFunctions::IsActorMemberOfCharactersCrew(parentShip, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
                {
                    return;
                }
            }
            else
            {
                return;
            }

            // Colour
            const auto colour = Utilities::Drawing::Colour::White;

            for (const auto& pin : table->MapPins)
            {
                const auto location = FVector{ (pin.X * 100.f), (pin.Y * 100.f), 0.f };

                // Check if on-screen
                auto position = FVector2D{};
                if (!playerController->ProjectWorldLocationToScreen(location, &position))
                {
                    continue;
                }

                auto topPosition = position;

                Utilities::Drawing::DrawString(ICON_FA_MAP_PIN, position, colour);

                if (!Utilities::General::NearCursor(position))
                {
                    continue;
                }

                // Get distance
                const auto distance = FVector::Dist(localPlayer->K2_GetActorLocation(), location) * 0.01f;

                // Draw
                auto name = std::string{ "Map Pin" };
                name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

                Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
            }
        }
    }
}
