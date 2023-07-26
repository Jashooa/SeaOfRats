#include "TreasureMap.h"

#include <algorithm>
#include <vector>

#include "include/spdlog/spdlog.h"

#include "Drawing.h"
#include "Utilities/General.h"
#include "Utilities/Math.h"

namespace Hacks
{
    namespace ESP
    {
        void GetIslandRiddleActorByName(UWorld* world, std::string islandName, std::string actorName, std::vector<AActor*>* outActors)
        {
            const auto levels = world->Levels;
            ULevel* level{};
            const std::string islandRiddlesName(islandName + "_riddles");
            for (auto i = 6; i < levels.Num(); ++i)
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

            //spdlog::info("Looking for: {}", actorName);

            const auto actors = level->AActors;
            for (auto i = 0; i < actors.Num(); ++i)
            {
                const auto actor = actors[i];
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

                //spdlog::info(actor->GetName());
                if (actor->GetName().find(actorName) != std::string::npos)
                {
                    //spdlog::info("Found");
                    outActors->push_back(actor);
                }
            }
        }

        void DrawRiddleMap(UWorld* world, AActor* actor)
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

            const auto islandDataEntries = islandDataAsset->IslandDataEntries;

            for (auto islandDataIndex = 0; islandDataIndex < islandDataEntries.Num(); ++islandDataIndex)
            {
                const auto islandDataEntry = islandDataEntries[islandDataIndex];
                if (!islandDataEntry)
                {
                    continue;
                }

                const auto worldMapData = islandDataEntry->WorldMapData;
                if (!worldMapData)
                {
                    continue;
                }

                const std::string islandName = islandDataEntry->IslandName.GetName();

                if (riddleMap->MapInventoryTexturePath.AssetLongPathname.ToString().find(islandName) != std::string::npos)
                {
                    const auto worldMapCaptureParams = worldMapData->CaptureParams;
                    auto worldMapPosition = worldMapCaptureParams.WorldSpaceCameraPosition;
                    worldMapPosition.Z = 0.f;
                    const auto distance = static_cast<int32_t>((localPlayer->K2_GetActorLocation() - worldMapPosition).Size() * 0.01f);

                    if (distance < 400)
                    {
                        const auto riddleMapContents = riddleMap->Contents;
                        const auto progress = riddleMapContents.Progress;
                        const auto steps = riddleMapContents.Text.Num();

                        //float x = Drawing::Window->Size.x * 0.5f;
                        //float y = 200.f;

                        //Drawing::DrawString("Progress: " + std::to_string(progress) + "/" + std::to_string(steps), FVector2D(x, y), Drawing::Colour::White, false);

                        for (auto stepIndex = progress; stepIndex < steps; ++stepIndex)
                        {
                            const auto& text = riddleMapContents.Text[stepIndex];
                            //Drawing::DrawString("Step: " + std::to_string(stepIndex + 1), FVector2D(x, y += 15.f), Drawing::Colour::White, false);

                            std::string location{};
                            std::string paces_word{};
                            std::string target{};
                            std::string compass_direction{};
                            std::string CD{};

                            const auto substitutions = text.Substitutions;
                            for (auto substitutionIndex = 0; substitutionIndex < substitutions.Num(); ++substitutionIndex)
                            {
                                const auto& substitution = substitutions[substitutionIndex];
                                //Drawing::DrawString(substitution.Name.ToString() + ": " + UKismetTextLibrary::Conv_TextToString(substitution.Substitution).ToString(), FVector2D(x + 10.f, y += 15.f), Drawing::Colour::White, false);

                                const auto name = substitution.Name.ToString();
                                auto subText = UKismetTextLibrary::Conv_TextToString(substitution.Substitution).ToString();
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
                                    //location = subText;
                                    spdlog::info(location);
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
                                std::vector<AActor*> locationActors{};
                                GetIslandRiddleActorByName(world, islandName, location, &locationActors);
                                AActor* theLocation = Utilities::ClosestRelativeActorToBearing(worldMapPosition, locationActors, CD);
                                for (auto locationIndex = 0; locationIndex < locationActors.size(); ++locationIndex)
                                //if (theLocation)
                                {
                                    const auto locationActor = locationActors[locationIndex];
                                    //const auto locationActor = theLocation;
                                    if (!locationActor)
                                    {
                                        continue;
                                    }

                                    if (!locationActor->IsA(ALandmark::StaticClass()))
                                    {
                                        continue;
                                    }

                                    const auto landmark = reinterpret_cast<ALandmark*>(locationActor);

                                    FVector2D landmarkPosition;
                                    if (playerController->ProjectWorldLocationToScreen(landmark->K2_GetActorLocation(), &landmarkPosition))
                                    {
                                        ImU32 colour = Drawing::Colour::White;
                                        //Drawing::DrawCircleFilled(position, 3.f, colour);
                                        Drawing::DrawString(ICON_FA_LOCATION_PIN, landmarkPosition, colour);

                                        if (!Utilities::NearCursor(landmarkPosition))
                                        {
                                            continue;
                                        }

                                        std::string landmarkText = "Step " + std::to_string(stepIndex + 1);

                                        const auto landmarkDistance = static_cast<int32_t>(localPlayer->GetDistanceTo(landmark) * 0.01f);
                                        landmarkText += " [" + std::to_string(landmarkDistance) + "m]";
                                        /*if (!CD.empty())
                                        {
                                            landmarkText += " " + CD;
                                        }*/

                                        if (locationActor == theLocation)
                                        {
                                            landmarkText = "This " + landmarkText;
                                        }

                                        Drawing::DrawString(landmarkText, { landmarkPosition.X, landmarkPosition.Y - 15.f }, Drawing::Colour::White);

                                        std::string instruction{};
                                        if (!paces_word.empty())
                                        {
                                            instruction += paces_word;
                                        }

                                        if (!compass_direction.empty())
                                        {
                                            instruction += " " + compass_direction;
                                        }

                                        Drawing::DrawString(instruction, { landmarkPosition.X, landmarkPosition.Y + 15.f }, Drawing::Colour::White);
                                        if (!target.empty())
                                        {
                                            Drawing::DrawString("Target: " + target, { landmarkPosition.X, landmarkPosition.Y + 30.f }, Drawing::Colour::White);
                                        }

                                        /*std::string actions{};
                                        for (auto reactionIndex = 0; reactionIndex < landmark->Reactions.Num(); ++reactionIndex)
                                        {
                                            const auto& reaction = landmark->Reactions[reactionIndex];

                                            for (auto actionIndex = 0; actionIndex < reaction.ActionsThatTriggerThisReaction.Num(); ++actionIndex)
                                            {
                                                const auto& action = reaction.ActionsThatTriggerThisReaction[actionIndex];
                                                switch (action)
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
                                            Drawing::DrawString(actions, FVector2D(landmarkScreen.X, landmarkScreen.Y + 45.f), Drawing::Colour::White);
                                        }*/
                                    }

                                    /*if (!target.empty())
                                    {
                                        std::wstring targetName(target.begin(), target.end());

                                        if (const auto targetActor = UActorFunctionLibrary::FindActorByName(world, FString(targetName.c_str())))
                                        {
                                            FVector2D targetScreen;
                                            const auto targetDistance = static_cast<int32_t>(localPlayer->GetDistanceTo(targetActor) * 0.01f);
                                            if (playerController->ProjectWorldLocationToScreen(targetActor->K2_GetActorLocation(), &targetScreen))
                                            {
                                                Drawing::DrawCircleFilled(targetScreen, 3.f, Drawing::Colour::White);
                                                std::string targetText = "Step " + std::to_string(stepIndex + 1) + " Target";
                                                if (targetDistance > 20)
                                                {
                                                    targetText += " [" + std::to_string(targetDistance) + "m]";
                                                }
                                                Drawing::DrawString(targetText, FVector2D(targetScreen.X, targetScreen.Y - 15.f), Drawing::Colour::White);
                                            }
                                        }
                                    }*/
                                }
                            }
                        }
                    }
                    else
                    {
                        FVector2D position;
                        if (playerController->ProjectWorldLocationToScreen(worldMapPosition, &position))
                        {
                            ImU32 colour = Drawing::Colour::White;
                            //Drawing::DrawCircleFilled(position, 3.f, colour);
                            Drawing::DrawString(ICON_FA_MAP_LOCATION, position, colour);

                            if (!Utilities::NearCursor(position))
                            {
                                return;
                            }

                            std::string name = "RiddleMap:";
                            name += " " + UKismetTextLibrary::Conv_TextToString(islandDataEntry->LocalisedName).ToString();
                            name += " [" + std::to_string(distance) + "m]";
                            Drawing::DrawString(name, { position.X, position.Y - 15.f }, Drawing::Colour::White);
                        }
                    }
                }
            }
        }

        void DrawXMarksTheSpotMap(UWorld* world, AActor* actor)
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

            const auto islandDataEntries = islandDataAsset->IslandDataEntries;
            for (auto islandDataIndex = 0; islandDataIndex < islandDataEntries.Num(); ++islandDataIndex)
            {
                const auto islandDataEntry = islandDataEntries[islandDataIndex];
                if (!islandDataEntry)
                {
                    continue;
                }

                const auto worldMapData = islandDataEntry->WorldMapData;
                if (!worldMapData)
                {
                    continue;
                }

                const std::string islandName = islandDataEntry->IslandName.GetName();

                if (xMarksTheSpotMap->MapTexturePath.ToString().find(islandName) != std::string::npos)
                {
                    const auto worldMapCaptureParams = worldMapData->CaptureParams;
                    auto worldMapLocation = worldMapCaptureParams.WorldSpaceCameraPosition;
                    worldMapLocation.Z = 0.f;
                    const auto distance = static_cast<int32_t>((localPlayer->K2_GetActorLocation() - worldMapLocation).Size() * 0.01f);

                    if (distance < 400)
                    {
                        const auto scale = worldMapCaptureParams.CameraOrthoWidth;
                        const static FVector2D orthoMapCentre(0.5f, 0.5f);

                        const auto marks = xMarksTheSpotMap->Marks;
                        for (auto markIndex = 0; markIndex < marks.Num(); ++markIndex)
                        {
                            const auto& mark = marks[markIndex];
                            const auto markPosition = orthoMapCentre - mark.Position;
                            const auto rotatedMapPosition = markPosition.GetRotated(xMarksTheSpotMap->Rotation + 180.f);

                            FVector xMarkWorldLocation(
                                worldMapCaptureParams.WorldSpaceCameraPosition.X + (rotatedMapPosition.X * scale),
                                worldMapCaptureParams.WorldSpaceCameraPosition.Y + (rotatedMapPosition.Y * scale),
                                worldMapCaptureParams.WorldSpaceCameraPosition.Z
                            );

                            const FVector endTracePosition(xMarkWorldLocation.X, xMarkWorldLocation.Y, -500.f);
                            FHitResult hitResult;
                            if (UKismetSystemLibrary::LineTraceSingle_NEW(world, xMarkWorldLocation, endTracePosition, ETraceTypeQuery::TraceTypeQuery4, false, TArray<AActor*>(), EDrawDebugTrace::EDrawDebugTrace__None, true, &hitResult))
                            {
                                xMarkWorldLocation = hitResult.Location;
                            }

                            FVector2D position;
                            if (playerController->ProjectWorldLocationToScreen(xMarkWorldLocation, &position))
                            {
                                ImU32 colour = Drawing::Colour::Red;
                                if (mark.IsUnderground)
                                {
                                    colour = Drawing::Colour::Orange;
                                }
                                /*Drawing::DrawCircleFilled(position, 8.f, Drawing::Colour::White);
                                Drawing::DrawCircleFilled(position, 6.f, colour);
                                Drawing::DrawCircleFilled(position, 4.f, Drawing::Colour::White);
                                Drawing::DrawCircleFilled(position, 2.f, colour);*/

                                Drawing::DrawString(ICON_FA_LOCATION_DOT, position, colour);

                                if (!Utilities::NearCursor(position))
                                {
                                    return;
                                }

                                std::string markName = "Mark " + std::to_string(markIndex + 1);

                                const int32_t markDistance = static_cast<int32_t>((localPlayer->K2_GetActorLocation() - xMarkWorldLocation).Size() * 0.01f);
                                markName += " [" + std::to_string(markDistance) + "m]";
                                Drawing::DrawString(markName, { position.X, position.Y - 15.f }, colour);
                            }
                        }
                    }
                    else
                    {
                        FVector2D position;
                        if (playerController->ProjectWorldLocationToScreen(worldMapLocation, &position))
                        {
                            ImU32 colour = Drawing::Colour::White;
                            //Drawing::DrawCircleFilled(position, 3.f, colour);
                            Drawing::DrawString(ICON_FA_MAP_LOCATION_DOT, position, colour);

                            if (!Utilities::NearCursor(position))
                            {
                                return;
                            }

                            std::string name = "XMarksTheSpotMap:";
                            name += " " + UKismetTextLibrary::Conv_TextToString(islandDataEntry->LocalisedName).ToString();
                            name += " [" + std::to_string(distance) + "m]";
                            Drawing::DrawString(name, { position.X, position.Y - 15.f }, Drawing::Colour::White);
                        }
                    }
                }
            }
        }

        void DrawTornMap(UWorld* world, AActor* actor)
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

            float x = 200.f;
            float y = 200.f;
            /*auto children = tornMap->BlueprintCreatedComponents;
            for (auto i = 0; i < children.Num(); ++i)
            {
                auto& child = children[i];
                Drawing::DrawString(child->GetName(), FVector2D(x, y += 15.f), Drawing::Colour::White, false);
            }*/

            Drawing::DrawString(tornMap->GetFullName(), { x, y += 15.f }, Drawing::Colour::White, false);

            const auto marks = tornMap->TargetVisibility;
            for (auto markIndex = 0; markIndex < marks.Num(); ++markIndex)
            {
                const auto& mark = marks[markIndex];

                FVector2D position;
                if (playerController->ProjectWorldLocationToScreen(mark, &position))
                {
                    ImU32 colour = Drawing::Colour::Red;
                    Drawing::DrawCircleFilled(position, 8.f, Drawing::Colour::White);
                    Drawing::DrawCircleFilled(position, 6.f, colour);
                    Drawing::DrawCircleFilled(position, 4.f, Drawing::Colour::White);
                    Drawing::DrawCircleFilled(position, 2.f, colour);
                    const int32_t markDistance = static_cast<int32_t>((localPlayer->K2_GetActorLocation() - mark).Size() * 0.01f);
                    if (markDistance > 20)
                    {
                        Drawing::DrawString(" [" + std::to_string(markDistance) + "m]", { position.X + 8.f, position.Y - 1.f }, Drawing::Colour::White, false);
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
                for (auto i = 0; i < treasureMaps.Num(); ++i)
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
    }
}
