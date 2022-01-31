#include "Ship.h"

#include "Drawing.h"

namespace Hacks
{
    namespace ESP
    {
        void DrawShip(UWorld* world, AActor* actor)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto ship = reinterpret_cast<AShip*>(actor);

            auto location = actor->K2_GetActorLocation();
            location.Z += 25 * 100;

            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            if (distance >= 1300)
            {
                return;
            }

            //Drawing::DrawBoundingBox(world, ship, Drawing::Colour::White);

            std::string actorName = actor->GetName();
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
            }

            if (UCrewFunctions::IsActorMemberOfCharactersCrew(ship, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
            {
                name = "My " + name;
            }

            name += " [" + std::to_string(distance) + "m]";

            FVector2D nameScreen = FVector2D(screen.X, screen.Y - 25.0f);
            Drawing::DrawString(name, nameScreen, Drawing::Colour::White);

            auto waterInfo = ship->GetInternalWater();
            if (waterInfo)
            {
                FVector2D healthScreen = FVector2D(screen.X, screen.Y - 10.0f);
                FVector2D healthTopLeft = FVector2D(healthScreen.X - 50.0f, healthScreen.Y);
                FVector2D healthBottomRight = FVector2D(healthScreen.X + 50.0f, healthScreen.Y + 5.0f);
                float waterMax = waterInfo->InternalWaterParams.MaxWaterAmount;
                float waterLevel = waterMax - waterInfo->WaterAmount;
                Drawing::DrawHealthBar(healthTopLeft, healthBottomRight, waterLevel, waterMax);
            }
        }

        void DrawShipFar(UWorld* world, AActor* actor)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = playerController->Pawn;
            auto ship = reinterpret_cast<AShipNetProxy*>(actor);

            auto location = actor->K2_GetActorLocation();
            location.Z += 25 * 100;

            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                return;
            }

            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            if (distance < 1300)
            {
                return;
            }

            std::string actorName = actor->GetName();
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
            }

            if (UCrewFunctions::IsActorMemberOfCharactersCrew(ship, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
            {
                name = "My " + name;
            }

            name += " [" + std::to_string(distance) + "m]";

            FVector2D nameScreen = FVector2D(screen.X, screen.Y - 10.0f);
            Drawing::DrawString(name, nameScreen, Drawing::Colour::White);
        }
    }
}
