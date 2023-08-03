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
                const auto stormList = stormService->StormList;
                for (int stormIndex = 0; stormIndex < stormList.Num(); ++stormIndex)
                {
                    if (const auto storm = stormList[stormIndex])
                    {
                        drawStorm(world, storm);
                    }
                }
            }
        }

        void Storm::drawStorm(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto storm = reinterpret_cast<AStorm*>(actor);

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            //location.Z = 200.f * 100.f;
            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Colour
            ImU32 colour = Utilities::Drawing::Colour::Grey;
            Utilities::Drawing::DrawString(ICON_FA_CLOUD_SHOWERS_HEAVY, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            std::string name = storm->SubjectName.ToString();

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
        }
    }
}
