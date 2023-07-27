#include "LoreBook.h"

#include "Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void DrawLoreBook(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto item = reinterpret_cast<AModalInteractionProxy*>(actor);

            // Check if lorebook
            if (item->GetName().find("LoreBook") == std::string::npos)
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
            ImU32 colour = Drawing::Colour::Yellow;
            //Drawing::DrawCircleFilled(position, 3.f, colour);
            Drawing::DrawString(ICON_FA_BOOK, position, colour);

            if (!Utilities::NearCursor(position))
            {
                return;
            }

            // Get name
            std::string name = item->GetName();
            if (const auto dialog = reinterpret_cast<UNPCDialogComponent*>(item->GetComponentByClass(UNPCDialogComponent::StaticClass())))
            {
                name = UKismetTextLibrary::Conv_TextToString(dialog->WelcomeMessage).ToString();
            }

            // Get distance
            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
        }
    }
}
