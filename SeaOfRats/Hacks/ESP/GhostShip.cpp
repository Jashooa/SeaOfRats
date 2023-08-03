#include "GhostShip.h"

#include "Utilities/Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void GhostShip::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto ship = reinterpret_cast<AAggressiveGhostShip*>(actor);

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 1500.f)
            {
                return;
            }

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
            const ImU32 colour = Utilities::Drawing::Colour::White;

            // Draw hits remaining
            const std::string hitsRemaining = "Hits Remaining: " + std::to_string(ship->GetNumShotsLeftToKill());
            Utilities::Drawing::DrawString(hitsRemaining, { position.X, position.Y - 15.f }, colour);

            // Get name
            std::string name = "Ghost Ship";
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { position.X, position.Y - 30.f }, colour);
        }
    }
}
