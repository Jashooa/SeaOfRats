#include "Rowboat.h"

#include "Drawing.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawRowboat(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            //const auto rowboat = reinterpret_cast<ARowboat*>(actor);

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            const auto topLocation = FVector(location.X, location.Y, location.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get name
                std::string name = "Rowboat";

                const std::string actorName = actor->GetName();
                if (actorName.find("Harpoon") != std::string::npos)
                {
                    name = "Harpoon " + name;
                }
                else if (actorName.find("Cannon") != std::string::npos)
                {
                    name = "Cannon " + name;
                }

                const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                name += " [" + std::to_string(distance) + "m]";

                // Draw name
                const FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Drawing::DrawString(name, nameScreen, Drawing::Colour::White);
            }
        }
    }
}
