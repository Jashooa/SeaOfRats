#include "Animal.h"

#include "Drawing.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawAnimal(UWorld* world, AActor* actor)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto animal = reinterpret_cast<AFauna*>(actor);

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
            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get name
                std::string name = UKismetTextLibrary::Conv_TextToString(animal->DisplayName).ToString();
                int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                name += " [" + std::to_string(distance) + "m]";
                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Drawing::DrawString(name, nameScreen, Drawing::Colour::White);
            }
        }
    }
}
