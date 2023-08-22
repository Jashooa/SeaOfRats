#include "Compass.h"

#include "Utilities/Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace Info
    {
        void Compass::Draw(UWorld* world)
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
            const auto bearing = static_cast<int>(std::round(rotation.Yaw) + 450) % 360;
            const auto index = static_cast<int>(std::trunc(std::fmodf(static_cast<float>(bearing) + 11.25f, 360.f)) * 0.04444444444f);

            const auto centre = Utilities::Drawing::GetScreenCentre();
            Utilities::Drawing::DrawString(std::to_string(bearing), { centre.X, 10.f }, Utilities::Drawing::Colour::White);
            Utilities::Drawing::DrawString(compassDirections[index], { centre.X, 25.f }, Utilities::Drawing::Colour::White);
        }
    }
}
