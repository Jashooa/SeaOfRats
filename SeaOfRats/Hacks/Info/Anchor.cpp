#include "Anchor.h"

#include "Drawing.h"

namespace Hacks
{
    namespace Info
    {
        void DrawAnchor(UWorld* world)
        {
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn);

            const auto parent = localPlayer->GetAttachParentActor();
            if (parent && parent->IsA(ACapstanArm::StaticClass()))
            {
                const auto parentParent = parent->GetParentActor();
                if (parentParent && parentParent->IsA(ACapstan::StaticClass()))
                {
                    const auto capstan = reinterpret_cast<ACapstan*>(parentParent);
                    const int32_t anchorLevel = static_cast<int32_t>(capstan->NetState.TargetRatio * 100.f);

                    const std::string capstanText = "Anchor Level: " + std::to_string(anchorLevel) + "%";
                    const FVector2D centre = Drawing::GetScreenCentre();
                    Drawing::DrawString(capstanText, { centre.X, centre.Y - 100.f }, Drawing::Colour::Green);
                }
            }
        }
    }
}
