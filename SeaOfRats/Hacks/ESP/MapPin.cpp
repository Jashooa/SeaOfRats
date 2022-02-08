#include "MapPin.h"

#include "Drawing.h"

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

                FVector2D screen;
                if (!playerController->ProjectWorldLocationToScreen(location, &screen))
                {
                    continue;
                }

                const int32_t distance = static_cast<int32_t>(UVectorMaths::Distance(localPlayer->RootComponent->K2_GetComponentLocation(), location) * 0.01f);
                const std::string pinText = "Map Pin [" + std::to_string(distance) + "m]";
                Drawing::DrawString(pinText, screen, colour);
            }
        }
    }
}
