#include "Mermaid.h"

#include "Drawing.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawMermaid(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto mermaid = reinterpret_cast<AMermaid*>(actor);

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Colour
            ImU32 colour = Drawing::Colour::White;
            Drawing::DrawCircleFilled(position, 3.f, colour);

            // Get name
            std::string name = "Mermaid";

            // Check if my mermaid
            const auto localCrewId = UCrewFunctions::GetCrewIdFromActor(world, localPlayer);
            const auto crewIds = mermaid->GetCrewIdsResponsibleForSavingAsCopy();
            for (auto idIndex = 0; idIndex < crewIds.Num(); ++idIndex)
            {
                if (UKismetGuidLibrary::EqualEqual_GuidGuid(crewIds[idIndex], localCrewId))
                {
                    name = "My " + name;
                }
            }

            // Get distance
            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
        }
    }
}
