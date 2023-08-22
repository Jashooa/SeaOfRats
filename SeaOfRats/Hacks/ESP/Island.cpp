#include "Island.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Island::Draw(UWorld* world)
        {
            const auto gameState = reinterpret_cast<AAthenaGameState*>(world->GameState);
            if (const auto islandService = gameState->IslandService)
            {
                const auto islandList = islandService->IslandDataAsset->IslandDataEntries;
                for (const auto& island : islandList)
                {
                    drawIsland(world, island);
                }
            }
        }

        void Island::drawIsland(UWorld* world, UIslandDataAssetEntry* island)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;

            const auto worldMapData = island->WorldMapData;

            if (!worldMapData)
            {
                return;
            }

            // Check if on-screen
            const auto location = worldMapData->CaptureParams.WorldSpaceCameraPosition;

            // Remove islands at 0,0,0
            if (location.Size() * 0.01f < 50.f)
            {
                return;
            }

            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            auto topPosition = position;

            // Colour
            auto colour = Utilities::Drawing::Colour::Green;
            Utilities::Drawing::DrawString(ICON_FA_MOUNTAIN_SUN, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            auto name = island->LocalisedName.DisplayString->ToString();

            // Get distance
            const auto distance = static_cast<int>((localPlayer->K2_GetActorLocation() - location).Size() * 0.01f);
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }
    }
}
