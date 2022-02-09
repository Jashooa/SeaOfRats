#include "WaterLevel.h"

#include "Drawing.h"

namespace Hacks
{
    namespace Info
    {
        void DrawWaterLevel(UWorld* world)
        {
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn);

            if (const auto ship = reinterpret_cast<AShip*>(localPlayer->GetCurrentShip()))
            {
                if (const auto waterInfo = ship->GetInternalWater())
                {
                    const float waterMax = waterInfo->InternalWaterParams.MaxWaterAmount;
                    const int32_t waterLevel = static_cast<int32_t>((waterInfo->WaterAmount / waterMax) * 100.f);
                    if (waterLevel > 0)
                    {
                        const std::string waterText = "Water Level: " + std::to_string(waterLevel) + "%";
                        const FVector2D centre = Drawing::GetScreenCentre();
                        Drawing::DrawString(waterText, { centre.X, 65.f }, Drawing::Colour::Red);
                    }
                }
            }
        }
    }
}
