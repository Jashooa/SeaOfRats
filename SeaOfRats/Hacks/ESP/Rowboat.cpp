#include "Rowboat.h"

#include "Drawing.h"
#include "Utilities/General.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawRowboat(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Colour
            ImU32 colour = Drawing::Colour::White;
            //Drawing::DrawCircleFilled(position, 3.f, colour);
            Drawing::DrawString(ICON_FA_HOT_TUB_PERSON, position, colour);

            if (!Utilities::NearCursor(position))
            {
                return;
            }

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

            // Get distance
            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
        }
    }
}
