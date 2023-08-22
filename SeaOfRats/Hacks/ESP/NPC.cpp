#include "NPC.h"

#include <format>

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void NPC::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto npc = reinterpret_cast<ANPC*>(actor);

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 500.f)
            {
                return;
            }

            // Check if on-screen
            auto location = actor->K2_GetActorLocation();
            location.Z += 100.f;
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            auto topPosition = position;

            // Colour
            const auto colour = Utilities::Drawing::Colour::White;
            Utilities::Drawing::DrawString(ICON_FA_USER, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            auto name = npc->DefaultDisplayName.DisplayString->ToString();
            /*if (name.empty())
            {
                const auto gameState = reinterpret_cast<AAthenaGameState*>(world->GameState);
                const auto npcData = gameState->NPCService->NPCData;

                for (const auto& npcFound : npcData)
                {
                    if (npc->Id == npcFound.Id)
                    {
                        name += " " + npcFound.Name.DisplayString->ToString();
                        break;
                    }
                }
            }*/
            if (const auto dialog = reinterpret_cast<UNPCDialogComponent*>(npc->GetComponentByClass(UNPCDialogComponent::StaticClass())))
            {
                name = dialog->WelcomeMessage.DisplayString->ToString();

                // Find the position of the opening and closing tags.
                const auto openingTagPos = name.find("<hl>");
                const auto closingTagPos = name.find("</hl>");

                // If both tags are found and the closing tag appears after the opening tag.
                if (openingTagPos != std::string::npos && closingTagPos != std::string::npos && closingTagPos > openingTagPos) {
                    // Extract the content between the tags.
                    const auto contentStart = openingTagPos + 4; // Skip "<hl>"
                    const auto contentLength = closingTagPos - contentStart;
                    name = name.substr(contentStart, contentLength);
                }
            }

            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }
    }
}
