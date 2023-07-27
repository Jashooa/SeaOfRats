#include "MapPin.h"

#include "Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void DrawMapPin(UWorld* world, AActor* actor)
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
            ImU32 colour = Drawing::Colour::White;

            const auto pins = table->MapPins;

            for (auto pinIndex = 0; pinIndex < pins.Num(); ++pinIndex)
            {
                const auto& pin = pins[pinIndex];
                const FVector location((pin.X * 100.f), (pin.Y * 100.f), 0.f);

                // Check if on-screen
                FVector2D position;
                if (!playerController->ProjectWorldLocationToScreen(location, &position))
                {
                    continue;
                }

                //Drawing::DrawCircleFilled(position, 3.f, colour);
                Drawing::DrawString(ICON_FA_MAP_PIN, position, colour);

                if (!Utilities::NearCursor(position))
                {
                    continue;
                }

                // Get distance
                const int32_t distance = static_cast<int32_t>(UVectorMaths::Distance(localPlayer->RootComponent->K2_GetComponentLocation(), location) * 0.01f);

                // Draw
                const std::string pinText = "Map Pin [" + std::to_string(distance) + "m]";
                Drawing::DrawString(pinText, { position.X, position.Y - 15.f }, colour);
            }
        }
    }
}
