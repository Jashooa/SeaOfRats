#include "LoreBook.h"

#include "Drawing.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawLoreBook(UWorld* world, AActor* actor)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto item = reinterpret_cast<AModalInteractionProxy*>(actor);

            // Check if lorebook
            if (item->GetName().find("LoreBook") == std::string::npos)
            {
                return;
            }

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
                ImU32 colour = Drawing::Colour::Yellow;
                Drawing::DrawCircleFilled(screen, 3.0f, colour);

                // Get name
                std::string name = item->GetName();
                if (const auto dialog = reinterpret_cast<UNPCDialogComponent*>(item->GetComponentByClass(UNPCDialogComponent::StaticClass())))
                {
                    name = UKismetTextLibrary::Conv_TextToString(dialog->WelcomeMessage).ToString();
                }

                int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
                name += " [" + std::to_string(distance) + "m]";

                // Draw name
                FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                Drawing::DrawString(name, nameScreen, colour);
            }
        }
    }
}
