#include "GhostShip.h"

#include "Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void DrawGhostShip(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto ship = reinterpret_cast<AAggressiveGhostShip*>(actor);

            auto location = actor->K2_GetActorLocation();
            location.Z += 25.f * 100.f;

            // Check if on screen
            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            if (ship->ShipState.IsShipDead || !ship->ShipState.IsShipVisible)
            {
                return;
            }

            // Colour
            ImU32 colour = Drawing::Colour::White;

            // Get name
            std::string name = "Ghost Ship";

            // Get distance
            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            Drawing::DrawString(name, { position.X, position.Y - 25.f }, colour);

            // Draw hits remaining
            const std::string hitsRemaining = "Hits Remaining: " + std::to_string(ship->GetNumShotsLeftToKill());
            Drawing::DrawString(hitsRemaining, { position.X, position.Y - 10.f }, colour);
        }
    }
}
