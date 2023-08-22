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
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Get bounds
            auto origin = FVector{};
            auto extent = FVector{};
            actor->GetActorBounds(true, &origin, &extent);

            auto topPosition = position;

            // Colour
            const auto colour = Utilities::Drawing::Colour::White;

            // Draw tentacles remaining
            const auto tentaclesRemaining = "Tentacles Remaining: " + std::to_string(kraken->NumTentaclesRemaining);
            Utilities::Drawing::DrawString(tentaclesRemaining, { topPosition.X, topPosition.Y -= 15.f }, colour);

            // Get name
            auto name = std::string{ "Kraken" };
            const auto actorName = actor->GetName();
            name += " " + actorName;
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
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
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Get bounds
            auto origin = FVector{};
            auto extent = FVector{};
            actor->GetActorBounds(true, &origin, &extent);

            auto topPosition = position;

            // Colour
            const auto colour = Utilities::Drawing::Colour::White;

            // Draw health bar
            if (const auto healthComponent = tentacle->HealthComponent)
            {
                const auto healthCurrent = healthComponent->GetCurrentHealth();
                const auto healthMax = healthComponent->GetMaxHealth();
                Utilities::Drawing::DrawHealthBar({ topPosition.X, topPosition.Y -= 15.f }, healthCurrent, healthMax);
            }

            // Get name
            auto name = std::string{ "Kraken Tentacle" };
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }
    }
}
