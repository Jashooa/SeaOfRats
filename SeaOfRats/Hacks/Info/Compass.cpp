#include "Compass.h"

#include "Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace Info
    {
        void DrawCompass(UWorld* world)
        {
            static const std::vector<std::string> compassDirections = {
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

            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto cameraManager = playerController->PlayerCameraManager;
            if (!cameraManager)
            {
                return;
            }

            const auto rotation = cameraManager->GetCameraRotation();
            const int32_t bearing = static_cast<int32_t>(std::round(rotation.Yaw) + 450) % 360;
            const int32_t index = static_cast<int32_t>(std::trunc(std::fmodf(static_cast<float>(bearing) + 11.25f, 360.f)) * 0.04444444444f);

            const FVector2D centre = Drawing::GetScreenCentre();
            Drawing::DrawString(std::to_string(bearing), { centre.X, 10.f }, Drawing::Colour::White);
            Drawing::DrawString(compassDirections[index], { centre.X, 25.f }, Drawing::Colour::White);
        }
    }
}
