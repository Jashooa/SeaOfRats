#include "Anchor.h"

#include "Drawing.h"

namespace Hacks
{
    namespace Info
    {
        void DrawAnchor(UWorld* world)
        {
            auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(world->OwningGameInstance->LocalPlayers[0]->PlayerController->Pawn);

            auto parent = localPlayer->GetAttachParentActor();

            if (parent && parent->IsA(ACapstanArm::StaticClass()))
            {
                auto parentParent = parent->GetParentActor();
                if (parentParent && parentParent->IsA(ACapstan::StaticClass()))
                {
                    auto capstan = reinterpret_cast<ACapstan*>(parentParent);
                    int32_t anchorLevel = static_cast<int32_t>(capstan->NetState.TargetRatio * 100.0f);

                    std::string capstanText = "Anchor Level: " + std::to_string(anchorLevel) + "%";
                    float centerX = Drawing::Window->Size.x * 0.5f;
                    Drawing::DrawString(capstanText, FVector2D(centerX, 80), Drawing::Colour::Red);
                }
            }

        }
    }
}
