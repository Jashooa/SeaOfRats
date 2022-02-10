#include "Storm.h"

#include "Drawing.h"
#include "Utilities/General.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawStorm(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto storm = reinterpret_cast<AStorm*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            //location.Z = 200.f * 100.f;
            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Colour
            ImU32 colour = Drawing::Colour::Grey;
            //Drawing::DrawCircleFilled(position, 3.f, colour);
            Drawing::DrawString(ICON_FA_CLOUD_SHOWERS_HEAVY, position, colour);

            if (!Utilities::NearCursor(position))
            {
                return;
            }

            // Get name
            std::string name = storm->SubjectName.ToString();

            // Get distance
            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            const FVector2D nameScreen = FVector2D();
            Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
        }

        void DrawStorms(UWorld* world)
        {
            const auto gameState = reinterpret_cast<AAthenaGameState*>(world->GameState);

            if (const auto stormService = gameState->StormService)
            {
                const auto stormList = stormService->StormList;

                for (auto stormIndex = 0; stormIndex < stormList.Num(); ++stormIndex)
                {
                    if (const auto storm = stormList[stormIndex])
                    {
                        DrawStorm(world, storm);
                    }
                }
            }
        }
    }
}
