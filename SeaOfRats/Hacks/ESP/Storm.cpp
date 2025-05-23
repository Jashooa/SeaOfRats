#include "Storm.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Storm::Draw(UWorld* world)
        {
            const auto gameState = reinterpret_cast<AAthenaGameState*>(world->GameState);
            if (const auto stormService = gameState->StormService)
            {
                for (const auto& storm : stormService->StormList)
                {
                    drawStorm(world, storm);
                }
            }
        }

        void Storm::drawStorm(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto storm = reinterpret_cast<AStorm*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            location.Z = 500.f * 100.f;
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            auto topPosition = position;

            // Colour
            auto colour = Utilities::Drawing::Colour::Grey;
            Utilities::Drawing::DrawString(ICON_FA_CLOUD_SHOWERS_HEAVY, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            auto name = storm->SubjectName.ToString();

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }
    }
}
