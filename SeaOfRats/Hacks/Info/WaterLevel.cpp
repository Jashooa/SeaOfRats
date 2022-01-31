#include "WaterLevel.h"

#include "Drawing.h"

namespace Hacks
{
    namespace Info
    {
        void DrawWaterLevel(UWorld* world)
        {
            auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn);

            auto ship = reinterpret_cast<AShip*>(localPlayer->GetCurrentShip());
            if (ship)
            {
                auto waterInfo = ship->GetInternalWater();
                if (waterInfo)
                {
                    float waterMax = waterInfo->InternalWaterParams.MaxWaterAmount;
                    int32_t waterLevel = static_cast<int32_t>((waterInfo->WaterAmount / waterMax) * 100.0f);
                    if (waterLevel > 10)
                    {
                        std::string waterText = "Water Level: " + std::to_string(waterLevel) + "%";
                        float centerX = Drawing::Window->Size.x * 0.5f;
                        Drawing::DrawString(waterText, FVector2D(centerX, 65), Drawing::Colour::Red);
                    }
                }
            }
        }
    }
}
