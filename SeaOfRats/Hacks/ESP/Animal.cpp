#include "Animal.h"

#include "Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void DrawAnimal(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto animal = reinterpret_cast<AFauna*>(actor);

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
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Colour
            ImU32 colour = Drawing::Colour::White;
            //Drawing::DrawCircleFilled(position, 3.f, colour);
            Drawing::DrawString(ICON_FA_PAW, position, colour);

            if (!Utilities::NearCursor(position))
            {
                return;
            }

            // Get name
            std::string name = UKismetTextLibrary::Conv_TextToString(animal->DisplayName).ToString();

            // Get distance
            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
        }
    }
}
