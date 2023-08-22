#include "Event.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Event::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            auto topPosition = position;

            // Colour
            const auto colour = Utilities::Drawing::Colour::White;
            Utilities::Drawing::DrawString(ICON_FA_TRIANGLE_EXCLAMATION, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            auto name = std::string{ "Event" };
            const auto actorName = actor->GetName();
            if (actorName.find("ShipCloud") != std::string::npos)
            {
                name = "Fleet " + name;
            }
            else if (actorName.find("BP_GhostShip_") != std::string::npos)
            {
                name = "Ghost Fleet " + name;
            }
            else if (actorName.find("_Flameheart_") != std::string::npos)
            {
                name = "Ghost Fleet Flameheart " + name;
            }
            else if (actorName.find("BP_SkellyFort_") != std::string::npos)
            {
                name = "Skeleton Fort " + name;
            }
            else if (actorName.find("BP_SkellyFort_RitualSkullCloud_") != std::string::npos)
            {
                name = "Fort of the Damned " + name;
            }
            else if (actorName.find("BP_LegendSkellyFort_") != std::string::npos)
            {
                name = "Fort of Fortune " + name;
            }
            else if (actorName.find("BP_AshenLord_") != std::string::npos)
            {
                name = "Ashen Winds " + name;
            }
            /*else
            {
                name = actorName + " " + name;
            }*/

            // debugging
            name += " ActorName: " + actorName;

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }
    }
}
