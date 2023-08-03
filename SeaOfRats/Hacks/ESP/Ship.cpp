#include "Ship.h"

#include <vector>

#include "Utilities/Drawing.h"
#include "Utilities/General.h"
#include "Utilities/Unreal.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Ship::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto ship = reinterpret_cast<AShip*>(actor);

            if (ship == reinterpret_cast<AAthenaCharacter*>(localPlayer)->GetCurrentShip())
            {
                return;
            }

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 1500.f)
            {
                return;
            }

            // Get location
            auto location = actor->K2_GetActorLocation();
            location.Z += 25.f * 100.f;

            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Colour
            ImU32 colour = Utilities::Drawing::Colour::Red;

            // Draw water level as health bar
            if (const auto waterInfo = ship->GetInternalWater())
            {
                const float waterMax = waterInfo->InternalWaterParams.MaxWaterAmount;
                const float waterLevel = waterMax - waterInfo->WaterAmount;
                Utilities::Drawing::DrawHealthBar({ position.X, position.Y - 15.f }, waterLevel, waterMax);
            }

            // Get name
            const std::string actorName = actor->GetName();
            std::string name = "Ship";
            if (actorName.find("Large") != std::string::npos)
            {
                name = "Galleon";
            }
            else if (actorName.find("Medium") != std::string::npos)
            {
                name = "Brigantine";
            }
            else if (actorName.find("Small") != std::string::npos)
            {
                name = "Sloop";
            }

            if (actorName.find("AI") != std::string::npos)
            {
                name = "Skeleton " + name;
                colour = Utilities::Drawing::Colour::Orange;
            }

            if (UCrewFunctions::IsActorMemberOfCharactersCrew(ship, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
            {
                name = "My " + name;
                colour = Utilities::Drawing::Colour::Green;
            }

            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { position.X, position.Y - 30.f }, colour);
        }

        void Ship::DrawFar(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto ship = reinterpret_cast<AShipNetProxy*>(actor);

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance < 1500.f)
            {
                return;
            }

            // Get location
            auto location = actor->K2_GetActorLocation();
            location.Z += 25.f * 100.f;

            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Colour
            ImU32 colour = Utilities::Drawing::Colour::Red;

            // Get name
            const std::string actorName = actor->GetName();
            std::string name = "Ship";
            if (actorName.find("Large") != std::string::npos)
            {
                name = "Galleon";
            }
            else if (actorName.find("Medium") != std::string::npos)
            {
                name = "Brigantine";
            }
            else if (actorName.find("Small") != std::string::npos)
            {
                name = "Sloop";
            }

            if (actorName.find("AI") != std::string::npos)
            {
                name = "Skeleton " + name;
                colour = Utilities::Drawing::Colour::Orange;
            }

            Utilities::Drawing::DrawString(ICON_FA_SHIP, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            if (UCrewFunctions::IsActorMemberOfCharactersCrew(ship, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
            {
                name = "My " + name;
                colour = Utilities::Drawing::Colour::Green;
            }

            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
        }
    }
}
