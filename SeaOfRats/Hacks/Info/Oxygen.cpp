#include "Oxygen.h"

#include "Utilities/Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace Info
    {
        void Oxygen::Draw(UWorld* world)
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
                    const FVector2D centre = Utilities::Drawing::GetScreenCentre();
                    const std::string oxygenText = "Oxygen: " + std::to_string(oxygenLevel) + "%";
                    Utilities::Drawing::DrawString(oxygenText, { centre.X, 50.f }, Utilities::Drawing::Colour::Red);
                }
            }
        }
    }
}
