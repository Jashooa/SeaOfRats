#include "Item.h"

#include <map>

#include "Utilities/Drawing.h"
#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        struct Prices
        {
            int Gold;
            int Doubloons;
            int AncientCoins;
        };

        std::map<std::string, Prices> RewardPrices;

        void Item::GetPrices(UWorld* world)
        {
            const auto gameInstance = reinterpret_cast<UAthenaGameInstance*>(world->OwningGameInstance);
            const auto gameContext = gameInstance->GameContext;
            const auto services = gameContext->ServiceCoordinator.Services;
            // const auto rewardService = reinterpret_cast<URewardService*>(services[4].Service);

            /*URewardService* rewardService = nullptr;
            for (int i = 0; i < services.Num(); ++i)
            {
                const auto service = services[i].Service;

                if (service->IsA(URewardService::StaticClass()))
                {
                    rewardService = reinterpret_cast<URewardService*>(service);
                    break;
                }
            }*/

            const auto rewardService = UObject::FindObject<URewardService>("RewardService Transient.AthenaGameContext_1.RewardService_1");

            if (!rewardService)
            {
                return;
            }

            for (const auto& rewardAsset : rewardService->RewardDefinitionAssets)
            {
                for (const auto& definition : rewardAsset->RewardDefinitions)
                {
                    auto id = definition.RewardIdentifier.GetName();
                    auto prices = Prices{};

                    for (const auto& reward : definition.Rewards)
                    {
                        if (reward->IsA(UGoldReward::StaticClass()))
                        {
                            auto goldReward = reinterpret_cast<UGoldReward*>(reward);

                            prices.Gold = (goldReward->MinGold + goldReward->MaxGold) / 2;
                        }
                        else if (reward->IsA(UWaywardTokensReward::StaticClass()))
                        {
                            auto doubloonReward = reinterpret_cast<UWaywardTokensReward*>(reward);

                            prices.Doubloons = (doubloonReward->MinWaywardTokens + doubloonReward->MaxWaywardTokens) / 2;
                        }
                        else if (reward->IsA(UPremiumCurrencyReward::StaticClass()))
                        {
                            auto ancientcoinsReward = reinterpret_cast<UPremiumCurrencyReward*>(reward);

                            prices.AncientCoins = (ancientcoinsReward->MinPremiumCurrency + ancientcoinsReward->MaxPremiumCurrency) / 2;
                        }
                    }

                    RewardPrices.insert({ id, prices });
                }
            }
        }

        void Item::Draw(UWorld* world, AActor* actor)
        {
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = playerController->Pawn;
            const auto item = reinterpret_cast<AFloatingItemProxy*>(actor);

            // Get distance
            const auto distance = localPlayer->GetDistanceTo(actor) * 0.01f;
            if (distance >= 500.f)
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
            auto bottomPosition = position;

            // Colour
            auto colour = Utilities::Drawing::Colour::White;

            // Get item info
            if (const auto itemInfo = item->ItemInfo)
            {
                if (itemInfo->IsA(ABootyItemInfo::StaticClass()))
                {
                    const auto bootyItemInfo = reinterpret_cast<ABootyItemInfo*>(itemInfo);

                    const auto rarity = bootyItemInfo->Rarity.GetName();
                    if (rarity == "Common")
                    {
                        colour = Utilities::Drawing::Colour::Grey;
                    }
                    else if (rarity == "Rare")
                    {
                        colour = Utilities::Drawing::Colour::Green;
                    }
                    else if (rarity == "Legendary")
                    {
                        colour = Utilities::Drawing::Colour::Purple;
                    }
                    else if (rarity == "Mythical")
                    {
                        colour = Utilities::Drawing::Colour::Orange;
                    }
                    else
                    {
                        colour = Utilities::Drawing::Colour::Blue;
                    }


                }

                Utilities::Drawing::DrawString(ICON_FA_GEM, position, colour);

                if (!Utilities::General::NearCursor(position))
                {
                    return;
                }

                if (const auto itemDesc = itemInfo->Desc)
                {
                    // Get name
                    auto name = itemDesc->Title.DisplayString->ToString();
                    name += " [" + std::to_string(static_cast<int>(distance)) + "m]";

                    // Draw name
                    Utilities::Drawing::DrawString(name, { topPosition.X, topPosition.Y -= 15.f }, colour);
                }

                // Draw prices
                if (itemInfo->IsA(ABootyItemInfo::StaticClass()))
                {
                    const auto bootyItemInfo = reinterpret_cast<ABootyItemInfo*>(itemInfo);

                    auto rewardId = bootyItemInfo->HandInRewardId.RewardId.GetName();
                    
                    if (rewardId != "None")
                    {
                        auto& prices = RewardPrices[rewardId];

                        Utilities::Drawing::DrawString("General: ", { bottomPosition.X, bottomPosition.Y += 15.f }, colour);
                        if (prices.Gold > 0)
                        {
                            Utilities::Drawing::DrawString("Gold: " + std::to_string(prices.Gold), { bottomPosition.X, bottomPosition.Y += 15.f}, colour);
                        }

                        if (prices.Doubloons > 0)
                        {
                            Utilities::Drawing::DrawString("Doubloons: " + std::to_string(prices.Doubloons), { bottomPosition.X, bottomPosition.Y += 15.f }, colour);
                        }

                        if (prices.AncientCoins > 0)
                        {
                            Utilities::Drawing::DrawString("Ancient Coins: " + std::to_string(prices.AncientCoins), { bottomPosition.X, bottomPosition.Y += 15.f }, colour);
                        }
                    }

                    for (const auto& id : bootyItemInfo->HandInRewardIdCompanySpecific)
                    {
                        rewardId = id.RewardId.RewardId.GetName();

                        Utilities::Drawing::DrawString("Company: " + id.CompanyId->GetName(), { bottomPosition.X, bottomPosition.Y += 15.f}, colour);
                        if (rewardId != "None")
                        {
                            auto& prices = RewardPrices[rewardId];

                            if (prices.Gold > 0)
                            {
                                Utilities::Drawing::DrawString("Gold: " + std::to_string(prices.Gold), { bottomPosition.X, bottomPosition.Y += 15.f }, colour);
                            }

                            if (prices.Doubloons > 0)
                            {
                                Utilities::Drawing::DrawString("Doubloons: " + std::to_string(prices.Doubloons), { bottomPosition.X, bottomPosition.Y += 15.f }, colour);
                            }

                            if (prices.AncientCoins > 0)
                            {
                                Utilities::Drawing::DrawString("Ancient Coins: " + std::to_string(prices.AncientCoins), { bottomPosition.X, bottomPosition.Y += 15.f }, colour);
                            }
                        }
                    }
                }
            }
        }
    }
}
