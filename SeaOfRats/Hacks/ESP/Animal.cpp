#include "Animal.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Animal::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto animal = reinterpret_cast<AFauna*>(actor);

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 500.f)
            {
                return;
            }

            /*switch (animal->AIControllerParams->TeamID)
            {
                case EAthenaAITeam::Fauna_Chickens:
                    break;
                case EAthenaAITeam::Fauna_Pigs:
                    break;
                case EAthenaAITeam::Fauna_Snakes:
                    break;
            }*/

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Get bounds
            // FVector origin, extent;
            // actor->GetActorBounds(true, &origin, &extent);

            // Colour
            const ImU32 colour = Utilities::Drawing::Colour::White;
            Utilities::Drawing::DrawString(ICON_FA_PAW, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            std::string name = animal->DisplayName.DisplayString->ToString();
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
        }
    }
}
