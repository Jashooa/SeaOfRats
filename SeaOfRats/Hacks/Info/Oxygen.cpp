#include "Oxygen.h"

#include "Drawing.h"

namespace Hacks
{
    namespace Info
    {
        void DrawOxygen(UWorld* world)
        {
            auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn);

            if (!localPlayer->IsInWater())
            {
                return;
            }

            auto drowningComponent = localPlayer->DrowningComponent;
            if (drowningComponent)
            {
                int oxygenLevel = static_cast<int>(drowningComponent->GetOxygenLevel() * 100.0f);
                if (oxygenLevel < 100)
                {
                    float centerX = Drawing::Window->Size.x * 0.5f;
                    std::string oxygenText = "Oxygen: " + std::to_string(oxygenLevel) + "%";
                    Drawing::DrawString(oxygenText, FVector2D(centerX, 50), Drawing::Colour::Red);
                }
            }
        }
    }
}
