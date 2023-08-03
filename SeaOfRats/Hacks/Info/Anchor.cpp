#include "Anchor.h"

#include "Utilities/Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace Info
    {
        void Anchor::Draw(UWorld* world)
        {
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn);

            const auto parent = localPlayer->GetAttachParentActor();
            if (parent && parent->IsA(ACapstanArm::StaticClass()))
            {
                const auto parentParent = parent->GetParentActor();
                if (parentParent && parentParent->IsA(ACapstan::StaticClass()))
                {
                    const auto capstan = reinterpret_cast<ACapstan*>(parentParent);
                    const auto anchorLevel = static_cast<int>(capstan->NetState.TargetRatio * 100.f);

                    const std::string capstanText = "Anchor Level: " + std::to_string(anchorLevel) + "%";
                    const FVector2D centre = Utilities::Drawing::GetScreenCentre();
                    Utilities::Drawing::DrawString(capstanText, { centre.X, centre.Y - 100.f }, Utilities::Drawing::Colour::Green);
                }
            }
        }
    }
}
