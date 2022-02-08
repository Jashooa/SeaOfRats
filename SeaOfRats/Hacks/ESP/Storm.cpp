#include "Storm.h"

#include "Drawing.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawStorm(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto storm = reinterpret_cast<AStorm*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            location.Z = 200.f * 100.f;
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get name
            std::string name = storm->SubjectName.ToString();

            // Get distance
            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Colour
            ImU32 colour = Drawing::Colour::White;

            // Draw name
            const FVector2D nameScreen = FVector2D(screen.X, screen.Y - 10.0f);
            Drawing::DrawString(name, nameScreen, colour);
        }
    }
}
