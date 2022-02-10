#include "Ship.h"

#include "Drawing.h"
#include "Utilities/General.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawShip(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto ship = reinterpret_cast<AShip*>(actor);

            if (ship == reinterpret_cast<AAthenaCharacter*>(localPlayer)->GetCurrentShip())
            {
                return;
            }

            auto location = actor->K2_GetActorLocation();
            location.Z += 25.f * 100.f;

            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Get distance
            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            if (distance >= 1500)
            {
                return;
            }

            // Colour
            ImU32 colour = Drawing::Colour::Red;

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
                colour = Drawing::Colour::Orange;
            }

            if (UCrewFunctions::IsActorMemberOfCharactersCrew(ship, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
            {
                name = "My " + name;
                colour = Drawing::Colour::Green;
            }

            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            Drawing::DrawString(name, { position.X, position.Y - 30.f }, colour);

            if (const auto waterInfo = ship->GetInternalWater())
            {
                const float waterMax = waterInfo->InternalWaterParams.MaxWaterAmount;
                const float waterLevel = waterMax - waterInfo->WaterAmount;
                Drawing::DrawHealthBar({ position.X, position.Y - 15.f }, waterLevel, waterMax);
            }
        }

        void DrawShipFar(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto ship = reinterpret_cast<AShipNetProxy*>(actor);

            auto location = actor->K2_GetActorLocation();
            location.Z += 25 * 100;

            FVector2D position;
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Get distance
            const int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            if (distance < 1500)
            {
                return;
            }

            // Colour
            ImU32 colour = Drawing::Colour::Red;

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
                colour = Drawing::Colour::Orange;
            }

            if (UCrewFunctions::IsActorMemberOfCharactersCrew(ship, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
            {
                name = "My " + name;
                colour = Drawing::Colour::Green;
            }

            //Drawing::DrawCircleFilled(position, 3.f, colour);
            Drawing::DrawString(ICON_FA_SHIP, position, colour);

            if (!Utilities::NearCursor(position))
            {
                return;
            }

            name += " [" + std::to_string(distance) + "m]";

            // Draw name
            Drawing::DrawString(name, { position.X, position.Y - 15.f }, colour);
        }
    }
}
