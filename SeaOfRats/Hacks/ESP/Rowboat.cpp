#include "Rowboat.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Rowboat::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 1500.f)
            {
                return;
            }

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Colour
            const ImU32 colour = Utilities::Drawing::Colour::White;
            Utilities::Drawing::DrawString(ICON_FA_HOT_TUB_PERSON, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            std::string name = "Rowboat";
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            const std::string actorName = actor->GetName();
            if (actorName.find("Harpoon") != std::string::npos)
            {
                name = "Harpoon " + name;
            }
            else if (actorName.find("Cannon") != std::string::npos)
            {
                name = "Cannon " + name;
            }

            // Draw name
            Utilities::Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
        }
    }
}
