#include "PlayerList.h"

#include "Drawing.h"

namespace Hacks
{
    namespace Info
    {
        void DrawPlayerList(UWorld* world)
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

            float positionX = 10.f;
            float positionY = 200.f;
            for (auto crewIndex = 0; crewIndex < crews.Num(); ++crewIndex)
            {
                const FCrew crew = crews[crewIndex];
                const auto players = crew.Players;
                std::string shipType;
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

                Drawing::DrawString(shipType, { positionX, positionY += 15.f }, Drawing::Colour::White, false, false);
                for (auto playerIndex = 0; playerIndex < players.Num(); ++playerIndex)
                {
                    const auto player = reinterpret_cast<AAthenaPlayerState*>(players[playerIndex]);
                    if (!player)
                    {
                        continue;
                    }

                    std::string activity{};
                    switch (player->GetPlayerActivity())
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

                    std::string name = player->PlayerName.ToString();
                    if (!activity.empty())
                    {
                        name += " - " + activity;
                    }
                    Drawing::DrawString(name, { positionX + 10.f, positionY += 15.f }, Drawing::Colour::White, false, false);
                }
                positionY += 10.f;
            }
        }
    }
}
