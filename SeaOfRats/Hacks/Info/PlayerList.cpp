#include "PlayerList.h"

#include "Utilities/Drawing.h"

using namespace SDK;

namespace Hacks
{
    namespace Info
    {
        void PlayerList::Draw(UWorld* world)
        {
            const auto gameState = world->GameState;
            if (!gameState)
            {
                return;
            }

            if (!gameState->IsA(AAthenaGameState::StaticClass()))
            {
                return;
            }

            const auto athenaGameState = reinterpret_cast<AAthenaGameState*>(gameState);
            const auto crewService = athenaGameState->CrewService;
            if (!crewService)
            {
                return;
            }

            const auto crews = crewService->Crews;

            auto position = FVector2D{ 10.f, 200.f };
            for (const auto& crew : crews)
            {
                const auto players = crew.Players;
                auto shipType = std::string{};
                switch (crew.CrewSessionTemplate.MaxMatchmakingPlayers)
                {
                    case 2:
                        shipType = "Sloop";
                        break;
                    case 3:
                        shipType = "Brigantine";
                        break;
                    case 4:
                        shipType = "Galleon";
                        break;
                    default:
                        shipType = "";
                        break;
                }

                Utilities::Drawing::DrawString(shipType, { position.X, position.Y += 15.f }, Utilities::Drawing::Colour::White, false, false);
                for (const auto& player : players)
                {
                    if (!player)
                    {
                        continue;
                    }

                    auto activity = std::string{};
                    switch (reinterpret_cast<AAthenaPlayerState*>(player)->GetPlayerActivity())
                    {
                        case EPlayerActivityType::EPlayerActivityType__None:
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Bailing:
                            activity = "Bailing";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Cannon:
                            activity = "Cannon";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Cannon_END:
                            activity = "Cannon";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Capstan:
                            activity = "Capstan";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Capstan_END:
                            activity = "Capstan";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__CarryingBooty:
                            activity = "Carrying Booty";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__CarryingBooty_END:
                            activity = "Carrying Booty";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Dead:
                            activity = "Dead";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Dead_END:
                            activity = "Dead";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Digging:
                            activity = "Digging";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Dousing:
                            activity = "Dousing";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__EmptyingBucket:
                            activity = "Emptying Bucket";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Harpoon:
                            activity = "Harpoon";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Harpoon_END:
                            activity = "Harpoon";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__LoseHealth:
                            activity = "Losing Health";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Repairing:
                            activity = "Repairing";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Sails:
                            activity = "Sails";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Sails_END:
                            activity = "Sails";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__UndoingRepair:
                            activity = "Undoing Repair";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Wheel:
                            activity = "Wheel";
                            break;
                        case EPlayerActivityType::EPlayerActivityType__Wheel_END:
                            activity = "Wheel";
                            break;
                        default:
                            break;
                    }

                    auto name = player->PlayerName.ToString();

                    if (name.empty())
                    {
                        name = "Player";
                    }

                    if (!activity.empty())
                    {
                        name += " - " + activity;
                    }
                    Utilities::Drawing::DrawString(name, { position.X + 10.f, position.Y += 15.f }, Utilities::Drawing::Colour::White, false, false);
                }
                position.Y += 10.f;
            }
        }
    }
}
