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
        void printInfo(AActor* actor)
        {
            auto angular_velocity = actor->ReplicatedMovement.AngularVelocity;
            auto tangential_velocity = actor->ReplicatedMovement.LinearVelocity;
            tangential_velocity.Z = 0.f;
            auto speed = FVector(tangential_velocity.X, tangential_velocity.Y, 0.f).Size();

            auto yaw_degrees = FVector(0.f, 0.f, angular_velocity.Z).Size();
            auto yaw_radians = (yaw_degrees * PI) / 180.f;

            auto turn_radius = speed / yaw_radians;
            bool left = angular_velocity.Z > 0.f;
            auto right = actor->GetActorRightVector();
            right.Z = 0.f;
            auto rotated_center_unit = left ? right : right * -1;
            auto actor_location = actor->K2_GetActorLocation();
            actor_location.Z = 5.f * 100.f;
            auto center_of_rotation = (rotated_center_unit * turn_radius) + actor_location;
            UKismetSystemLibrary::DrawDebugCircle(actor, center_of_rotation, turn_radius, 180, { 1.f, 1.f, 1.f, 1.f }, 0.f, 10.f, { 1.f, 0.f, 0.f }, { 0.f, 1.f, 0.f }, true);

            auto velocity = actor->GetVelocity();

            float x = 800.f;
            float y = 200.f;
            Utilities::Drawing::DrawString("Location X: " + std::to_string(actor_location.X), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Location Y: " + std::to_string(actor_location.Y), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Angular velocity Z: " + std::to_string(angular_velocity.Z), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Tangential velocity X: " + std::to_string(tangential_velocity.X), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Tangential velocity Y: " + std::to_string(tangential_velocity.Y), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Velocity X: " + std::to_string(velocity.X), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Velocity Y: " + std::to_string(velocity.Y), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Speed xy-plane: " + std::to_string(speed), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw degrees: " + std::to_string(yaw_degrees), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Yaw radians: " + std::to_string(yaw_radians), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("Turn radius: " + std::to_string(turn_radius), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            float thetaRad = std::atan2(tangential_velocity.Y, tangential_velocity.X) + PI / 2;
            thetaRad = std::fmod(thetaRad, 2.f * PI);
            if (thetaRad < 0.f)
            {
                thetaRad += 2.f * PI;
            }

            float thetaDeg = FMath::RadiansToDegrees(thetaRad);
            Utilities::Drawing::DrawString("thetaRad: " + std::to_string(thetaRad), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("thetaDeg: " + std::to_string(thetaDeg), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);

            if (angular_velocity.Z < 0.f)
            {
                if (tangential_velocity.X < 0.f)
                {
                    thetaRad = (FMath::Atan2((-1.f * tangential_velocity.X), tangential_velocity.Y));
                }
                else if (tangential_velocity.X > 0.f)
                {
                    thetaRad = (FMath::Atan2((-1.f * tangential_velocity.X), tangential_velocity.Y)) + 2 * PI;
                }
            }
            else if (angular_velocity.Z > 0.f)
            {
                thetaRad = (FMath::Atan2((-1.f * tangential_velocity.X), tangential_velocity.Y)) + PI;
            }

            thetaDeg = FMath::RadiansToDegrees(thetaRad);
            Utilities::Drawing::DrawString("thetaRad: " + std::to_string(thetaRad), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
            Utilities::Drawing::DrawString("thetaDeg: " + std::to_string(thetaDeg), { x, y += 15.f }, Utilities::Drawing::Colour::Red, false);
        }

        void Ship::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto ship = reinterpret_cast<AShip*>(actor);

            /*if (UCrewFunctions::IsActorMemberOfCharactersCrew(ship, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
            {
                printInfo(actor);
            }*/

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

            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Colour
            auto colour = Utilities::Drawing::Colour::Red;

            // Draw water level as health bar
            auto topPosition = position;
            if (const auto waterInfo = ship->GetInternalWater())
            {
                const auto waterMax = waterInfo->InternalWaterParams.MaxWaterAmount;
                const auto waterLevel = waterMax - waterInfo->WaterAmount;
                Utilities::Drawing::DrawHealthBar({ topPosition.X, topPosition.Y -= 15.f }, waterLevel, waterMax);
            }

            // Get name
            auto name = std::string{ "Ship" };
            const auto actorName = actor->GetName();
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
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
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

            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            // Colour
            auto colour = Utilities::Drawing::Colour::Red;

            // Get name
            auto name = std::string{ "Ship" };
            const auto actorName = actor->GetName();
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
