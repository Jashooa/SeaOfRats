#include "GhostShip.h"

#include "Drawing.h"

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
            location.Z += 25 * 100;

            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Colour
            ImU32 colour = Drawing::Colour::White;

            std::string name = "Ghost Ship";
            switch (ship->GetShipType())
            {
                case EAggressiveGhostShipType::EAggressiveGhostShipType__Grunt:
                    //name += "Grunt Ship";
                    name += " Grunt";
                    break;
                case EAggressiveGhostShipType::EAggressiveGhostShipType__FormationGrunt:
                    //name += "Ghost Flagship";
                    name += " Formation Grunt";
                    break;
                case EAggressiveGhostShipType::EAggressiveGhostShipType__FormationLeader:
                    //name += "Ghost Captain Ship";
                    name += " Formation Leader";
                    break;
                case EAggressiveGhostShipType::EAggressiveGhostShipType__CaptainFormationGrunt:
                    //name += "Ashen Dragon Ship";
                    name += " Captain Formation Grunt";
                    break;
                case EAggressiveGhostShipType::EAggressiveGhostShipType__Captain:
                    //name += "The Burning Blade";
                    name += " Captain";
                    break;
            }

            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            const FVector2D nameScreen = FVector2D(screen.X, screen.Y - 25.0f);
            Drawing::DrawString(name, nameScreen, colour);

            // Draw hits remaining
            const std::string hitsRemaining = "Hits Remaining: " + std::to_string(ship->GetNumShotsLeftToKill());
            const FVector2D hitsScreen = FVector2D(screen.X, screen.Y - 10.0f);
            Drawing::DrawString(hitsRemaining, hitsScreen, colour);
        }
    }
}
