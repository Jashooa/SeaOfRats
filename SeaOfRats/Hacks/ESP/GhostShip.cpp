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
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            auto topPosition = position;

            if (ship->ShipState.IsShipDead || !ship->ShipState.IsShipVisible)
            {
                return;
            }

            // Colour
            const auto colour = Utilities::Drawing::Colour::White;

            // Draw hits remaining
            const auto hitsRemaining = "Hits Remaining: " + std::to_string(ship->GetNumShotsLeftToKill());
            Utilities::Drawing::DrawString(hitsRemaining, { topPosition.X, topPosition.Y -= 15.f }, colour);

            // Get name
            auto name = std::string{ "Ghost Ship" };
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }
    }
}
