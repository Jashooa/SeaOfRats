#include "Megalodon.h"

#include "Utilities/Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Megalodon::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto megalodon = reinterpret_cast<ASharkPawn*>(actor);

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 1500.f)
            {
                return;
            }

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Get top coordinates
            FVector2D topPosition;
            if (!playerController->ProjectWorldLocationToScreen({ location.X, location.Y, location.Z + extent.Z }, &topPosition))
            {
                return;
            }

            // Colour
            const ImU32 colour = Utilities::Drawing::Colour::Orange;

            // Draw box
            Utilities::Drawing::DrawBoundingRect(world, actor, colour);

            // Draw health bar
            if (const auto healthComponent = megalodon->HealthComponent)
            {
                const float healthCurrent = healthComponent->GetCurrentHealth();
                const float healthMax = healthComponent->GetMaxHealth();
                Utilities::Drawing::DrawHealthBar({ topPosition.X, topPosition.Y -= 15.f }, healthCurrent, healthMax);
            }

            // Get name
            std::string name = "Megalodon";
            const std::string meshName = megalodon->Mesh->MeshReference.AssetLongPathname.ToString();
            name += " Mesh: " + meshName;
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }
    }
}
