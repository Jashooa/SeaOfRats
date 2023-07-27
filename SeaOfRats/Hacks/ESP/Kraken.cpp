#include "Kraken.h"

#include "Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void DrawKraken(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto kraken = reinterpret_cast<AKraken*>(actor);

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Colour
            ImU32 colour = Drawing::Colour::White;

            // Get name
            std::string name = "Kraken";
            const std::string actorName = actor->GetName();
            name += " " + actorName;

            // Get distance
            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            Drawing::DrawString(name, { position.X, position.Y - 30.f }, colour);

            // Draw tentacles remaining
            const std::string tentaclesRemaining = "Tentacles Remaining: " + std::to_string(kraken->NumTentaclesRemaining);
            Drawing::DrawString(tentaclesRemaining, { position.X, position.Y - 15.f }, colour);
        }

        void DrawKrakenTentacle(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto tentacle = reinterpret_cast<AKrakenTentacle*>(actor);

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Get bounds
            FVector origin, extent;
            actor->GetActorBounds(true, &origin, &extent);

            // Colour
            ImU32 colour = Drawing::Colour::White;

            // Get name
            std::string name = "Kraken Tentacle";

            // Get distance
            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            Drawing::DrawString(name, { position.X, position.Y - 30.f }, colour);

            // Draw health bar
            if (const auto healthComponent = tentacle->HealthComponent)
            {
                const float healthCurrent = healthComponent->GetCurrentHealth();
                const float healthMax = healthComponent->GetMaxHealth();
                Drawing::DrawHealthBar({ position.X, position.Y - 15.f }, healthCurrent, healthMax);
            }
        }
    }
}
