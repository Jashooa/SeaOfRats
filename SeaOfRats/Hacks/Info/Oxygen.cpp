#include "Oxygen.h"

#include "Drawing.h"

namespace Hacks
{
    namespace Info
    {
        void DrawOxygen(UWorld* world)
        {
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn);

            if (!localPlayer->IsInWater())
            {
                return;
            }

            if (const auto drowningComponent = localPlayer->DrowningComponent)
            {
                const int oxygenLevel = static_cast<int>(drowningComponent->GetOxygenLevel() * 100.f);
                if (oxygenLevel < 100)
                {
                    const FVector2D centre = Drawing::GetScreenCentre();
                    const std::string oxygenText = "Oxygen: " + std::to_string(oxygenLevel) + "%";
                    Drawing::DrawString(oxygenText, { centre.X, 50.f }, Drawing::Colour::Red);
                }
            }
        }
    }
}
