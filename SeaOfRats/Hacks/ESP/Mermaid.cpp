#include "Mermaid.h"

#include "Drawing.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawMermaid(UWorld* world, AActor* actor)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto mermaid = reinterpret_cast<AMermaid*>(actor);

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            auto topLocation = FVector(location.X, location.Y, location.Z + extent.Z);
            FVector2D topScreen;
            if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
            {
                // Get name
                std::string name = "Mermaid";

                // Check if my mermaid
                auto localCrewId = UCrewFunctions::GetCrewIdFromActor(world, localPlayer);
                auto crewIds = mermaid->GetCrewIdsResponsibleForSavingAsCopy();
                for (int32_t i = 0; i < crewIds.Num(); ++i)
                {
                    if (UKismetGuidLibrary::EqualEqual_GuidGuid(crewIds[i], localCrewId))
                    {
                        name = "My " + name;
                    }
                }

                int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                name += " [" + std::to_string(distance) + "m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Drawing::DrawString(name, nameScreen, Drawing::Colour::White);
            }
        }
    }
}
