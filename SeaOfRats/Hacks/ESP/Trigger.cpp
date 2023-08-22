#include "Trigger.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void Trigger::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto trigger = reinterpret_cast<UMechanismTriggerComponent*>(actor->GetComponentByClass(UMechanismTriggerComponent::StaticClass()));

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            auto topPosition = position;

            // Colour
            const auto colour = Utilities::Drawing::Colour::White;
            Utilities::Drawing::DrawString(ICON_FA_GEARS, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            auto name = trigger->GetName();

            switch (trigger->TriggerState)
            {
            case EMechanismTriggerState::EMechanismTriggerState__Active:
                name += ": Active";
                break;
            case EMechanismTriggerState::EMechanismTriggerState__Inactive:
                name += ": Inactive";
                break;
            case EMechanismTriggerState::EMechanismTriggerState__Disabled:
                name += ": Disabled";
                break;
            }

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }

        void Trigger::DrawSwitch(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto trigger = reinterpret_cast<ASwitchMechanismTrigger*>(actor);

            // Ignore if ship component
            if (actor->ParentComponentActor.Actor && actor->ParentComponentActor.Actor->IsA(AShip::StaticClass()))
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

            auto topPosition = position;

            // Colour
            const auto colour = Utilities::Drawing::Colour::White;
            Utilities::Drawing::DrawString(ICON_FA_GEARS, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            auto name = std::string{ "Switch" };
            name += " " + trigger->SwitchNameText.DisplayString->ToString();

            switch (trigger->MechanismTriggerComponent->TriggerState)
            {
            case EMechanismTriggerState::EMechanismTriggerState__Active:
                name += ": Active";
                break;
            case EMechanismTriggerState::EMechanismTriggerState__Inactive:
                name += ": Inactive";
                break;
            case EMechanismTriggerState::EMechanismTriggerState__Disabled:
                name += ": Disabled";
                break;
            }

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }

        void Trigger::DrawPressurePlate(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto trigger = reinterpret_cast<APressurePlateMechanismTriggerBase*>(actor);

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            auto topPosition = position;

            // Colour
            const auto colour = Utilities::Drawing::Colour::White;
            Utilities::Drawing::DrawString(ICON_FA_GEARS, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            auto name = std::string{ "Pressure Plate" };

            switch (trigger->MechanismTriggerComponent->TriggerState)
            {
            case EMechanismTriggerState::EMechanismTriggerState__Active:
                name += ": Active";
                break;
            case EMechanismTriggerState::EMechanismTriggerState__Inactive:
                name += ": Inactive";
                break;
            case EMechanismTriggerState::EMechanismTriggerState__Disabled:
                name += ": Disabled";
                break;
            }

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }

        void Trigger::DrawTripwire(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto trigger = reinterpret_cast<ATripwireMechanismTrigger*>(actor);

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            auto topPosition = position;

            // Colour
            const auto colour = Utilities::Drawing::Colour::White;
            Utilities::Drawing::DrawString(ICON_FA_GEARS, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            auto name = std::string{ "Tripwire" };

            switch (trigger->MechanismTriggerComponent->TriggerState)
            {
            case EMechanismTriggerState::EMechanismTriggerState__Active:
                name += ": Active";
                break;
            case EMechanismTriggerState::EMechanismTriggerState__Inactive:
                name += ": Inactive";
                break;
            case EMechanismTriggerState::EMechanismTriggerState__Disabled:
                name += ": Disabled";
                break;
            }

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }

        void Trigger::DrawVolume(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto trigger = reinterpret_cast<AVolumeMechanismTrigger*>(actor);

            // Check if on-screen
            const auto location = actor->K2_GetActorLocation();
            auto position = FVector2D{};
            if (!playerController->ProjectWorldLocationToScreen(location, &position))
            {
                return;
            }

            auto topPosition = position;

            // Colour
            const auto colour = Utilities::Drawing::Colour::White;
            Utilities::Drawing::DrawString(ICON_FA_GEARS, position, colour);

            if (!Utilities::General::NearCursor(position))
            {
                return;
            }

            // Get name
            auto name = std::string{ "Volume" };

            switch (trigger->MechanismTriggerComponent->TriggerState)
            {
            case EMechanismTriggerState::EMechanismTriggerState__Active:
                name += ": Active";
                break;
            case EMechanismTriggerState::EMechanismTriggerState__Inactive:
                name += ": Inactive";
                break;
            case EMechanismTriggerState::EMechanismTriggerState__Disabled:
                name += ": Disabled";
                break;
            }

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

            // Draw name
            Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
        }
    }
}
