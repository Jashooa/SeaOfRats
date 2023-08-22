#include "LoreBook.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void LoreBook::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto item = reinterpret_cast<AModalInteractionProxy*>(actor);

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 1500.f)
            {
                return;
            }

            // Check if lorebook
            if (item->GetName().find("LoreBook") == std::string::npos)
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
            const auto colour = Utilities::Drawing::Colour::Yellow;
            Utilities::Drawing::DrawString(ICON_FA_BOOK, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            auto name = item->GetName();
            if (const auto dialog = reinterpret_cast<UNPCDialogComponent*>(item->GetComponentByClass(UNPCDialogComponent::StaticClass())))
            {
                name = dialog->WelcomeMessage.DisplayString->ToString();
            }

            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }
    }
}
