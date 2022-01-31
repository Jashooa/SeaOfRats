#include "Map.h"

#include "Drawing.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawMap(UWorld* world, AActor* actor)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto table = reinterpret_cast<AMapTable*>(actor);

            auto parentShip = actor->GetAttachParentActor();
            if (!UCrewFunctions::IsActorMemberOfCharactersCrew(parentShip, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
            {
                return;
            }

            auto pins = table->MapPins;

            for (int32_t i = 0; i < pins.Num(); ++i)
            {
                auto& pin = pins[i];
                FVector location((pin.X * 100.0f), (pin.Y * 100.0f), 100.0f);

                FVector2D screen;
                if (!playerController->ProjectWorldLocationToScreen(location, &screen))
                {
                    continue;
                }

                int32_t distance = static_cast<int32_t>(UVectorMaths::Distance(localPlayer->RootComponent->K2_GetComponentLocation(), location) * 0.01f);
                std::string pinText = "Map Pin [" + std::to_string(distance) + "m]";
                Drawing::DrawString(pinText, screen, Drawing::Colour::White);
            }
        }
    }
}
