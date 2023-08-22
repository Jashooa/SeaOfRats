#include "TreasureMap.h"

#include <algorithm>

#include "include/spdlog/spdlog.h"

#include "Utilities/Drawing.h"
#include "Utilities/General.h"
#include "Utilities/Unreal.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void TreasureMap::DrawRiddleMap(UWorld* world, AActor* actor)
        {
            const auto gameState = reinterpret_cast<AAthenaGameState*>(world->GameState);
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(playerController->Pawn);
            const auto riddleMap = reinterpret_cast<ARiddleMap*>(actor);

            // Not mine
            if (actor->GetAttachParentActor() != localPlayer)
            {
                return;
            }

            const auto islandService = gameState->IslandService;
            if (!islandService)
            {
                return;
            }

            const auto islandDataAsset = islandService->IslandDataAsset;
            if (!islandDataAsset)
            {
                return;
            }

            for (const auto& islandDataEntry : islandDataAsset->IslandDataEntries)
            {
                if (!islandDataEntry)
                {
                    continue;
                }

                const auto worldMapData = islandDataEntry->WorldMapData;
                if (!worldMapData)
                {
                    continue;
                }

                const auto islandName = islandDataEntry->IslandName.GetName();

                if (riddleMap->MapInventoryTexturePath.AssetLongPathname.ToString().find(islandName) != std::string::npos)
                {
                    const auto worldMapCaptureParams = worldMapData->CaptureParams;
                    auto worldMapLocation = worldMapCaptureParams.WorldSpaceCameraPosition;
                    worldMapLocation.Z = 0.f;

                    // Get distance
                    const auto distance = FVector::Dist(localPlayer->K2_GetActorLocation(), worldMapLocation) * 0.01f;

                    if (distance < 400.f)
                    {
                        const auto riddleMapContents = riddleMap->Contents;
                        const auto progress = riddleMapContents.Progress;
                        const auto steps = riddleMapContents.Text.Num();

                        auto x = Utilities::Drawing::Window->Size.x * 0.5f;
                        auto y = 200.f;

                        Utilities::Drawing::DrawString("Progress: " + std::to_string(progress) + "/" + std::to_string(steps), FVector2D(x, y), Utilities::Drawing::Colour::White, false);

                        int stepIndex = progress;
                        //for (int stepIndex = progress; stepIndex < steps; ++stepIndex)
                        {
                            const auto& text = riddleMapContents.Text[stepIndex];
                            Utilities::Drawing::DrawString("Step: " + std::to_string(stepIndex + 1), { x, y += 15.f }, Utilities::Drawing::Colour::White, false);

                            std::string location{};
                            std::string paces_word{};
                            std::string target{};
                            std::string compass_direction{};
                            std::string CD{};

                            for (const auto& substitution : text.Substitutions)
                            {
                                Utilities::Drawing::DrawString(substitution.Name.ToString() + ": " + substitution.Substitution.DisplayString->ToString(), FVector2D(x + 10.f, y += 15.f), Utilities::Drawing::Colour::White, false);

                                const auto name = substitution.Name.ToString();
                                auto subText = substitution.Substitution.DisplayString->ToString();
                                if (name == "location")
                                {
                                    //spdlog::info(subText);
                                    subText.erase(std::remove(subText.begin(), subText.end(), ' '), subText.end());
                                    subText.erase(std::remove(subText.begin(), subText.end(), '\''), subText.end());
                                    subText.erase(std::remove(subText.begin(), subText.end(), '\u2019'), subText.end());
                                    subText.erase(std::remove(subText.begin(), subText.end(), -0x1E), subText.end());
                                    subText.erase(std::remove(subText.begin(), subText.end(), -0x80), subText.end());
                                    subText.erase(std::remove(subText.begin(), subText.end(), -0x67), subText.end());
                                    subText.erase(std::remove(subText.begin(), subText.end(), '{'), subText.end());
                                    subText.erase(std::remove(subText.begin(), subText.end(), '}'), subText.end());
                                    location = Utilities::General::tolower(subText);
                                    // spdlog::info(location);
                                }
                                else if (name == "paces_word")
                                {
                                    paces_word = subText;
                                }
                                else if (name == "target")
                                {
                                    target = subText;
                                }
                                else if (name == "compass_direction")
                                {
                                    compass_direction = subText;
                                }
                                else if (name == "CD")
                                {
                                    CD = subText;
                                }
                            }

                            if (!location.empty())
                            {
                                auto locationActors = std::vector<AActor*>{};
                                getIslandRiddleActorByName(world, islandName, location, &locationActors);
                                auto theLocation = Utilities::Unreal::ClosestRelativeActorToBearing(worldMapLocation, locationActors, CD);
                                for (const auto& locationActor : locationActors)
                                {
                                    if (!locationActor)
                                    {
                                        continue;
                                    }

                                    if (!locationActor->IsA(ALandmark::StaticClass()))
                                    {
                                        continue;
                                    }

                                    const auto landmark = reinterpret_cast<ALandmark*>(locationActor);

                                    auto landmarkPosition = FVector2D{};
                                    if (playerController->ProjectWorldLocationToScreen(landmark->K2_GetActorLocation(), &landmarkPosition))
                                    {
                                        auto colour = Utilities::Drawing::Colour::White;
                                        Utilities::Drawing::DrawString(ICON_FA_LOCATION_PIN, landmarkPosition, colour);

                                        if (!Utilities::General::NearCursor(landmarkPosition))
                                        {
                                            continue;
                                        }

                                        auto landmarkText = "Step " + std::to_string(stepIndex + 1);

                                        const auto landmarkDistance = localPlayer->GetDistanceTo(landmark) * 0.01f;
                                        landmarkText += " [" + std::to_string(static_cast<int>(landmarkDistance)) + "m]";
                                        /*if (!CD.empty())
                                        {
                                            landmarkText += " " + CD;
                                        }*/

                                        if (locationActors.size() > 1)
                                        {
                                            if (locationActor == theLocation)
                                            {
                                                landmarkText = "This " + landmarkText;
                                            }
                                            else
                                            {
                                                landmarkText = "Other " + landmarkText;
                                            }
                                        }

                                        auto landmarkPositionTop = landmarkPosition;
                                        Utilities::Drawing::DrawString(landmarkText, { landmarkPositionTop.X, landmarkPositionTop.Y -= 15.f }, Utilities::Drawing::Colour::White);

                                        auto instruction = std::string{};
                                        if (!paces_word.empty())
                                        {
                                            instruction += paces_word;
                                        }

                                        if (!compass_direction.empty())
                                        {
                                            instruction += " " + compass_direction;
                                        }

                                        auto landmarkPositionBottom = landmarkPosition;
                                        if (!instruction.empty())
                                        {
                                            Utilities::Drawing::DrawString(instruction, { landmarkPositionBottom.X, landmarkPositionBottom.Y += 15.f }, Utilities::Drawing::Colour::White);
                                        }

                                        if (!target.empty())
                                        {
                                            Utilities::Drawing::DrawString("Target: " + target, { landmarkPositionBottom.X, landmarkPositionBottom.Y += 15.f }, Utilities::Drawing::Colour::White);
                                        }

                                        auto pattern = text.Pattern.DisplayString->ToString();
                                        pattern = Utilities::General::tolower(pattern);
                                        auto action = std::string{};
                                        if (pattern.find(" lantern") != std::string::npos
                                            || pattern.find(" flame") != std::string::npos
                                            || pattern.find(" beacon") != std::string::npos)
                                        {
                                            action = "Raise Lantern";
                                        }
                                        else if (pattern.find(" tune") != std::string::npos
                                            || pattern.find(" music") != std::string::npos
                                            || pattern.find(" instrument") != std::string::npos
                                            || pattern.find(" play") != std::string::npos
                                            || pattern.find(" shanty") != std::string::npos)
                                        {
                                            action = "Play Instrument";
                                        }
                                        else if (pattern.find("this map") != std::string::npos
                                            || pattern.find(" read ") != std::string::npos)
                                        {
                                            action = "Look at Map";
                                        }
                                        else
                                        {
                                            action = "Dig";
                                        }

                                        if (!action.empty())
                                        {
                                            Utilities::Drawing::DrawString(action, { landmarkPositionBottom.X, landmarkPositionBottom.Y += 15.f }, Utilities::Drawing::Colour::White);
                                        }

                                        
                                        /*std::string actions{};
                                        for (const auto& reaction : landmark->Reactions)
                                        {
                                            for (const auto& action : reaction.ActionsThatTriggerThisReaction)
                                            {
                                                switch (action.GetValue())
                                                {
                                                    case ERiddleActions::ERiddleActions__RaiseLanternAnyone:
                                                        actions += "Raise Lantern\n";
                                                        break;
                                                    case ERiddleActions::ERiddleActions__PlayAnyInstrumentAnyone:
                                                        actions += "Play Instrument\n";
                                                        break;
                                                    case ERiddleActions::ERiddleActions__Dig:
                                                        actions += "Dig\n";
                                                        break;
                                                    case ERiddleActions::ERiddleActions__LookAtMap:
                                                        actions += "Look at Map\n";
                                                        break;
                                                    default:
                                                        break;
                                                }
                                            }
                                        }
                                        
                                        if (!actions.empty())
                                        {
                                            Utilities::Drawing::DrawString(actions, { landmarkPositionBottom.X, landmarkPositionBottom.Y += 15.f }, Utilities::Drawing::Colour::White);
                                        }*/
                                        
                                    }

                                    /*if (!target.empty())
                                    {
                                        std::wstring targetName(target.begin(), target.end());

                                        if (const auto targetActor = UActorFunctionLibrary::FindActorByName(world, FString(targetName.c_str())))
                                        {
                                            FVector2D targetScreen;
                                            const auto targetDistance = localPlayer->GetDistanceTo(targetActor) * 0.01f;
                                            if (playerController->ProjectWorldLocationToScreen(targetActor->K2_GetActorLocation(), &targetScreen))
                                            {
                                                Utilities::Drawing::DrawCircleFilled(targetScreen, 3.f, Utilities::Drawing::Colour::White);
                                                std::string targetText = "Step " + std::to_string(i + 1) + " Target";
                                                if (targetDistance > 20.f)
                                                {
                                                    targetText += " [" + std::to_string(static_cast<int>(targetDistance)) + "m]";
                                                }
                                                Utilities::Drawing::DrawString(targetText, FVector2D(targetScreen.X, targetScreen.Y - 15.f), Utilities::Drawing::Colour::White);
                                            }
                                        }
                                    }*/
                                }
                            }
                        }
                    }
                    else
                    {
                        auto position = FVector2D{};
                        if (playerController->ProjectWorldLocationToScreen(worldMapLocation, &position))
                        {
                            const auto colour = Utilities::Drawing::Colour::White;
                            Utilities::Drawing::DrawString(ICON_FA_MAP_LOCATION, position, colour);

                            if (!Utilities::General::NearCursor(position))
                            {
                                return;
                            }

                            auto name = std::string{ "RiddleMap:" };
                            name += " " + islandDataEntry->LocalisedName.DisplayString->ToString();
                            name += " [" + std::to_string(distance) + "m]";
                            Utilities::Drawing::DrawString(name, { position.X, position.Y - 15.f }, Utilities::Drawing::Colour::White);
                        }
                    }
                }
            }
        }

        void TreasureMap::DrawXMarksTheSpotMap(UWorld* world, AActor* actor)
        {
            const auto gameState = reinterpret_cast<AAthenaGameState*>(world->GameState);
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(playerController->Pawn);
            const auto xMarksTheSpotMap = reinterpret_cast<AXMarksTheSpotMap*>(actor);

            // Not mine
            if (actor->GetAttachParentActor() != localPlayer)
            {
                return;
            }

            const auto islandService = gameState->IslandService;
            if (!islandService)
            {
                return;
            }

            const auto islandDataAsset = islandService->IslandDataAsset;
            if (!islandDataAsset)
            {
                return;
            }

            for (const auto& islandDataEntry : islandDataAsset->IslandDataEntries)
            {
                if (!islandDataEntry)
                {
                    continue;
                }

                const auto worldMapData = islandDataEntry->WorldMapData;
                if (!worldMapData)
                {
                    continue;
                }

                const auto islandName = islandDataEntry->IslandName.GetName();

                if (xMarksTheSpotMap->MapTexturePath.ToString().find(islandName) != std::string::npos)
                {
                    const auto worldMapCaptureParams = worldMapData->CaptureParams;
                    auto worldMapLocation = worldMapCaptureParams.WorldSpaceCameraPosition;
                    worldMapLocation.Z = 0.f;

                    // Get distance
                    const auto distance = FVector::Dist(localPlayer->K2_GetActorLocation(), worldMapLocation) * 0.01f;

                    if (distance < 400.f)
                    {
                        const auto scale = worldMapCaptureParams.CameraOrthoWidth;
                        const static auto orthoMapCentre = FVector2D{ 0.5f, 0.5f };

                        const auto marks = xMarksTheSpotMap->Marks;
                        for (int markIndex = 0; markIndex < marks.Num(); ++markIndex)
                        {
                            const auto& mark = marks[markIndex];
                            const auto markPosition = orthoMapCentre - mark.Position;
                            const auto rotatedMapPosition = markPosition.GetRotated(xMarksTheSpotMap->Rotation + 180.f);

                            auto xMarkWorldLocation = FVector{
                                worldMapCaptureParams.WorldSpaceCameraPosition.X + (rotatedMapPosition.X * scale),
                                worldMapCaptureParams.WorldSpaceCameraPosition.Y + (rotatedMapPosition.Y * scale),
                                worldMapCaptureParams.WorldSpaceCameraPosition.Z
                            };

                            const auto endTraceLocation = FVector{ xMarkWorldLocation.X, xMarkWorldLocation.Y, -500.f };
                            auto hitResult = FHitResult{};
                            if (UKismetSystemLibrary::LineTraceSingle_NEW(world, xMarkWorldLocation, endTraceLocation, ETraceTypeQuery::TraceTypeQuery4, false, TArray<AActor*>{}, EDrawDebugTrace::EDrawDebugTrace__None, true, &hitResult))
                            {
                                xMarkWorldLocation = hitResult.Location;
                            }

                            auto position = FVector2D{};
                            if (playerController->ProjectWorldLocationToScreen(xMarkWorldLocation, &position))
                            {
                                auto colour = Utilities::Drawing::Colour::Red;
                                if (mark.IsUnderground)
                                {
                                    colour = Utilities::Drawing::Colour::Orange;
                                }
                                /*Utilities::Drawing::DrawCircleFilled(position, 8.f, Utilities::Drawing::Colour::White);
                                Utilities::Drawing::DrawCircleFilled(position, 6.f, colour);
                                Utilities::Drawing::DrawCircleFilled(position, 4.f, Utilities::Drawing::Colour::White);
                                Utilities::Drawing::DrawCircleFilled(position, 2.f, colour);*/

                                Utilities::Drawing::DrawString(ICON_FA_LOCATION_DOT, position, colour);

                                if (!Utilities::General::NearCursor(position))
                                {
                                    return;
                                }

                                auto markName = "Mark " + std::to_string(markIndex + 1);

                                const auto markDistance = FVector::Dist(localPlayer->K2_GetActorLocation(), xMarkWorldLocation) * 0.01f;
                                markName += " [" + std::to_string(static_cast<int>(markDistance)) + "m]";
                                Utilities::Drawing::DrawString(markName, { position.X, position.Y - 15.f }, colour);
                            }
                        }
                    }
                    else
                    {
                        auto position = FVector2D{};
                        if (playerController->ProjectWorldLocationToScreen(worldMapLocation, &position))
                        {
                            const auto colour = Utilities::Drawing::Colour::White;
                            //Utilities::Drawing::DrawCircleFilled(position, 3.f, colour);
                            Utilities::Drawing::DrawString(ICON_FA_MAP_LOCATION_DOT, position, colour);

                            if (!Utilities::General::NearCursor(position))
                            {
                                return;
                            }

                            auto name = std::string{ "XMarksTheSpotMap:" };
                            name += " " + islandDataEntry->LocalisedName.DisplayString->ToString();
                            name += " [" + std::to_string(static_cast<int>(distance)) + "m]";
                            Utilities::Drawing::DrawString(name, { position.X, position.Y - 15.f }, Utilities::Drawing::Colour::White);
                        }
                    }
                }
            }
        }

        void TreasureMap::DrawTornMap(UWorld* world, AActor* actor)
        {
            //const auto gameState = reinterpret_cast<AAthenaGameState*>(world->GameState);
            const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            const auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(playerController->Pawn);
            const auto tornMap = reinterpret_cast<ATornMap*>(actor);

            // Not mine
            if (actor->GetAttachParentActor() != localPlayer)
            {
                return;
            }

            auto x = 200.f;
            auto y = 200.f;
            /*auto children = tornMap->BlueprintCreatedComponents;
            for (int i = 0; i < children.Num(); ++i)
            {
                const auto child = children[i];
                Utilities::Drawing::DrawString(child->GetName(), { x, y += 15.f }, Utilities::Drawing::Colour::White, false);
            }*/

            Utilities::Drawing::DrawString(tornMap->GetFullName(), { x, y += 15.f }, Utilities::Drawing::Colour::White, false);

            for (const auto& mark : tornMap->TargetVisibility)
            {
                auto position = FVector2D{};
                if (playerController->ProjectWorldLocationToScreen(mark, &position))
                {
                    const auto colour = Utilities::Drawing::Colour::Red;
                    Utilities::Drawing::DrawCircleFilled(position, 8.f, Utilities::Drawing::Colour::White);
                    Utilities::Drawing::DrawCircleFilled(position, 6.f, colour);
                    Utilities::Drawing::DrawCircleFilled(position, 4.f, Utilities::Drawing::Colour::White);
                    Utilities::Drawing::DrawCircleFilled(position, 2.f, colour);
                    const auto markDistance = FVector::Dist(localPlayer->K2_GetActorLocation(), mark) * 0.01f;
                    if (markDistance > 20.f)
                    {
                        Utilities::Drawing::DrawString(" [" + std::to_string(static_cast<int>(markDistance)) + "m]", { position.X + 8.f, position.Y - 1.f }, Utilities::Drawing::Colour::White, false);
                    }
                }
            }
        }

        /*void DrawTreasureMap(UWorld* world)
        {
            auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
            auto localPlayer = reinterpret_cast<AAthenaPlayerCharacter*>(playerController->Pawn);

            if (const auto treasureMapCollection = localPlayer->TreasureMapCollectionComponent)
            {
                const auto treasureMaps = treasureMapCollection->TreasureMaps;
                for (int i = 0; i < treasureMaps.Num(); ++i)
                {
                    const auto treasureMap = treasureMaps[i];

                    if (treasureMap->IsA(AXMarksTheSpotMap::StaticClass()))
                    {
                        DrawXMarksTheSpotMap(world, treasureMap);
                        continue;
                    }
                }
            }
        }*/

        void TreasureMap::getIslandRiddleActorByName(UWorld* world, std::string islandName, std::string actorName, std::vector<AActor*>* outActors)
        {
            const auto levels = world->Levels;
            ULevel* level = nullptr;
            const auto islandRiddlesName = islandName + "_riddles";
            for (int i = 6; i < levels.Num(); ++i)
            {
                if (levels[i]->GetFullName().find(islandRiddlesName) != std::string::npos)
                {
                    level = levels[i];
                    break;
                }
            }

            if (!level)
            {
                return;
            }

            // spdlog::info("Looking for: {}", actorName);

            for (const auto& actor : level->AActors)
            {
                if (!actor)
                {
                    continue;
                }

                if (actorName == "thebarrelcartinthesmugglerscamp")
                {
                    if (actor->GetName() == "t")
                    {
                        outActors->push_back(actor);
                    }
                }

                auto actorSearchName = Utilities::General::tolower(actor->GetName());

                // spdlog::info(actorSearchName);
                if (actorSearchName.find(actorName) != std::string::npos)
                {
                    // spdlog::info("Found");
                    outActors->push_back(actor);
                }
            }
        }
    }
}
