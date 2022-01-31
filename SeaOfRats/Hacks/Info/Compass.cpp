#include "Compass.h"

#include "Drawing.h"

namespace Hacks
{
    namespace Info
    {
        void DrawCompass(UWorld* world)
        {
            static std::vector<const char*> compassDirections = {
                "North",
                "North North East",
                "North East",
                "East North East",
                "East",
                "East South East",
                "South East",
                "South South East",
                "South",
                "South South West",
                "South West",
                "West South West",
                "West",
                "West North West",
                "North West",
                "North North West"
            };

            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto cameraManager = playerController->PlayerCameraManager;
            if (!cameraManager)
            {
                return;
            }

            auto rotation = cameraManager->GetCameraRotation();
            int32_t bearing = static_cast<int32_t>(std::round(rotation.Yaw) + 450) % 360;
            int32_t index = static_cast<int32_t>(std::trunc(std::fmodf(static_cast<float>(bearing) + 11.25f, 360.0f)) * 0.04444444444f);

            float centerX = Drawing::Window->Size.x * 0.5f;
            Drawing::DrawString(std::to_string(bearing), FVector2D(centerX, 10), Drawing::Colour::White);
            Drawing::DrawString(compassDirections[index], FVector2D(centerX, 25), Drawing::Colour::White);
        }
    }
}
