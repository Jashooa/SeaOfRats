#include "Mermaid.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Mermaid::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto mermaid = reinterpret_cast<AMermaid*>(actor);

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 1500.f)
            {
                return;
            }

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            auto topPosition = position;

            // Colour
            auto colour = Utilities::Drawing::Colour::White;
            Utilities::Drawing::DrawString(ICON_FA_LIFE_RING, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            auto name = std::string{ "Mermaid" };
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Check if my mermaid
            const auto localCrewId = UCrewFunctions::GetCrewIdFromActor(world, localPlayer);
            const auto crewIds = mermaid->GetCrewIdsResponsibleForSavingAsCopy();
            for (const auto& crewId : crewIds)
            {
                if (crewId == localCrewId)
                {
                    name = "My " + name;
                }
            }

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }
    }
}
