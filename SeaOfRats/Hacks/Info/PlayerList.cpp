#include "PlayerList.h"

#include "Drawing.h"

namespace Hacks
{
    namespace Info
    {
        void DrawPlayerList(UWorld* world)
        {
            auto gameState = world->GameState;
            if (!gameState)
            {
                return;
            }

            if (!gameState->IsA(AAthenaGameState::StaticClass()))
            {
                return;
            }

            auto athenaGameState = reinterpret_cast<AAthenaGameState*>(gameState);
            auto crewService = athenaGameState->CrewService;
            if (!crewService)
            {
                return;
            }

            auto crews = crewService->Crews;

            float positionX = 10.0f;
            float positionY = 120.0f;
            for (int32_t i = 0; i < crews.Num(); ++i)
            {
                FCrew crew = crews[i];
                auto players = crew.Players;
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
                //shipType = shipType + L" " + UKismetGuidLibrary::Conv_GuidToString(crew.CrewId).c_str();
                Drawing::DrawString(shipType, FVector2D(positionX, positionY), Drawing::Colour::White, false, false);
                positionY += 15.0f;
                for (int32_t j = 0; j < players.Num(); ++j)
                {
                    auto player = reinterpret_cast<AAthenaPlayerState*>(players[j]);
                    if (!player)
                    {
                        continue;
                    }

                    std::string activity = "";
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
                        name = name + " - " + activity;
                    }
                    Drawing::DrawString(name, FVector2D(positionX + 10.0f, positionY), Drawing::Colour::White, false, false);
                    positionY += 15.0f;
                }
                positionY += 10.0f;
            }
        }
    }
}
