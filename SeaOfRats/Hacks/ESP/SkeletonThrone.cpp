#include "SkeletonThrone.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void SkeletonThrone::Draw(UWorld* world, AActor* actor)
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
            Utilities::Drawing::DrawString(ICON_FA_COUCH, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            std::string name = "Skeleton Throne";
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
        }
    }
}
