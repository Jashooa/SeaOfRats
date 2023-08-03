#include "WaterLevel.h"

#include "Utilities/Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace Info
    {
        void WaterLevel::Draw(UWorld* world)
        {
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn);

            if (const auto ship = reinterpret_cast<AShip*>(localPlayer->GetCurrentShip()))
            {
                if (const auto waterInfo = ship->GetInternalWater())
                {
                    const float waterMax = waterInfo->InternalWaterParams.MaxWaterAmount;
                    const auto waterLevel = static_cast<int>((waterInfo->WaterAmount / waterMax) * 100.f);
                    if (waterLevel > 0)
                    {
                        const std::string waterText = "Water Level: " + std::to_string(waterLevel) + "%";
                        const FVector2D centre = Utilities::Drawing::GetScreenCentre();
                        Utilities::Drawing::DrawString(waterText, { centre.X, 65.f }, Utilities::Drawing::Colour::Red);
                    }
                }
            }
        }
    }
}
