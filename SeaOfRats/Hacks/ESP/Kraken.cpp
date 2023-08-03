#include "Kraken.h"

#include "Utilities/Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Kraken::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto kraken = reinterpret_cast<AKraken*>(actor);

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 1500.f)
            {
                return;
            }

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
            const ImU32 colour = Utilities::Drawing::Colour::White;

            // Draw tentacles remaining
            const std::string tentaclesRemaining = "Tentacles Remaining: " + std::to_string(kraken->NumTentaclesRemaining);
            Utilities::Drawing::DrawString(tentaclesRemaining, { position.X, position.Y - 15.f }, colour);

            // Get name
            std::string name = "Kraken";
            const std::string actorName = actor->GetName();
            name += " " + actorName;
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { position.X, position.Y - 30.f }, colour);
        }

        void Kraken::DrawTentacle(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto tentacle = reinterpret_cast<AKrakenTentacle*>(actor);

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 1500.f)
            {
                return;
            }

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
            const ImU32 colour = Utilities::Drawing::Colour::White;

            // Draw health bar
            if (const auto healthComponent = tentacle->HealthComponent)
            {
                const float healthCurrent = healthComponent->GetCurrentHealth();
                const float healthMax = healthComponent->GetMaxHealth();
                Utilities::Drawing::DrawHealthBar({ position.X, position.Y - 15.f }, healthCurrent, healthMax);
            }

            // Get name
            std::string name = "Kraken Tentacle";
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { position.X, position.Y - 30.f }, colour);
        }
    }
}
