#include "TreasureMap.h"

#include <algorithm>

#include "Drawing.h"

bool done = false;

namespace Hacks
{
    namespace ESP
    {
        void GetIslandRiddleActorByName(UWorld* world, std::string islandName, std::string actorName, TArray<class AActor*>* outActors)
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

            const auto actors = level->AActors;
            for (auto i = 0; i < actors.Num(); ++i)
            {
                const auto actor = actors[i];
                if (!actor)
                {
                    continue;
                }
                if (actor->GetName().find(actorName) != std::string::npos)
                {
                    outActors->Push(actor);
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
                            const auto text = riddleMapContents.Text[stepIndex];
                            //Drawing::DrawString("Step: " + std::to_string(i + 1), FVector2D(x, y += 15.f), Drawing::Colour::White, false);

                            std::string location{};
                            std::string paces_word{};
                            std::string target{};
                            std::string compass_direction{};
                            std::string CD{};

                            const auto substitutions = text.Substitutions;
                            for (auto substitutionIndex = 0; substitutionIndex < substitutions.Num(); ++substitutionIndex)
                            {
                                const auto substitution = substitutions[substitutionIndex];
                                //Drawing::DrawString(substitution.Name.ToString() + ": " + UKismetTextLibrary::Conv_TextToString(substitution.Substitution).ToString(), FVector2D(x + 10.f, y += 15.f), Drawing::Colour::White, false);

                                const auto name = substitution.Name.ToString();
                                auto subText = UKismetTextLibrary::Conv_TextToString(substitution.Substitution).ToString();
                                if (name == "location")
                                {
                                    subText.erase(std::remove(subText.begin(), subText.end(), ' '), subText.end());
                                    subText.erase(std::remove(subText.begin(), subText.end(), '\''), subText.end());
                                    subText.erase(std::remove(subText.begin(), subText.end(), '{'), subText.end());
                                    subText.erase(std::remove(subText.begin(), subText.end(), '}'), subText.end());
                                    location = subText;
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
                                TArray<AActor*> locationActors{};
                                GetIslandRiddleActorByName(world, islandName, location, &locationActors);
                                for (auto locationIndex = 0; locationIndex < locationActors.Num(); ++locationIndex)
                                {
                                    const auto locationActor = locationActors[locationIndex];
                                    if (!locationActor)
                                    {
                                        continue;
                                    }

                                    if (!locationActor->IsA(ALandmark::StaticClass()))
                                    {
                                        continue;
                                    }

                                    const auto landmark = reinterpret_cast<ALandmark*>(locationActor);

                                    FVector2D landmarkScreen;
                                    const auto landmarkDistance = static_cast<int32_t>(localPlayer->GetDistanceTo(landmark) * 0.01f);
                                    if (playerController->ProjectWorldLocationToScreen(landmark->K2_GetActorLocation(), &landmarkScreen))
                                    {
                                        Drawing::DrawCircleFilled(landmarkScreen, 3.0f, Drawing::Colour::White);
                                        std::string landmarkText = "Step " + std::to_string(stepIndex + 1);
                                        if (landmarkDistance > 20)
                                        {
                                            landmarkText += " [" + std::to_string(landmarkDistance) + "m]";
                                        }
                                        if (!CD.empty())
                                        {
                                            landmarkText += " " + CD;
                                        }

                                        Drawing::DrawString(landmarkText, FVector2D(landmarkScreen.X, landmarkScreen.Y - 15.f), Drawing::Colour::White);

                                        std::string sentence{};
                                        if (!paces_word.empty())
                                        {
                                            sentence += paces_word;
                                        }

                                        if (!compass_direction.empty())
                                        {
                                            sentence += " " + compass_direction;
                                        }

                                        Drawing::DrawString(sentence, FVector2D(landmarkScreen.X, landmarkScreen.Y + 15.f), Drawing::Colour::White);
                                        if (!target.empty())
                                        {
                                            Drawing::DrawString("Target: " + target, FVector2D(landmarkScreen.X, landmarkScreen.Y + 30.f), Drawing::Colour::White);
                                        }

                                        std::string actions{};
                                        for (auto reactionIndex = 0; reactionIndex < landmark->Reactions.Num(); ++reactionIndex)
                                        {
                                            const auto reaction = landmark->Reactions[reactionIndex];

                                            for (auto actionIndex = 0; actionIndex < reaction.ActionsThatTriggerThisReaction.Num(); ++actionIndex)
                                            {
                                                const auto action = reaction.ActionsThatTriggerThisReaction[actionIndex];
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
                                        }
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
                                                Drawing::DrawCircleFilled(targetScreen, 3.0f, Drawing::Colour::White);
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
                        FVector2D screen;
                        if (playerController->ProjectWorldLocationToScreen(worldMapPosition, &screen))
                        {
                            auto name = UKismetTextLibrary::Conv_TextToString(islandDataEntry->LocalisedName).ToString();
                            name += " [" + std::to_string(distance) + "m]";
                            Drawing::DrawString(name, FVector2D(screen.X, screen.Y - 15.f), Drawing::Colour::White);
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
                    auto worldMapPosition = worldMapCaptureParams.WorldSpaceCameraPosition;
                    worldMapPosition.Z = 0.f;
                    const auto distance = static_cast<int32_t>((localPlayer->K2_GetActorLocation() - worldMapPosition).Size() * 0.01f);

                    if (distance < 400)
                    {
                        const auto scale = worldMapCaptureParams.CameraOrthoWidth;
                        const static FVector2D orthoMapCentre(0.5f, 0.5f);

                        const auto marks = xMarksTheSpotMap->Marks;
                        for (auto markIndex = 0; markIndex < marks.Num(); ++markIndex)
                        {
                            const auto mark = marks[markIndex];
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

                            FVector2D screen;
                            if (playerController->ProjectWorldLocationToScreen(xMarkWorldLocation, &screen))
                            {
                                ImU32 colour = Drawing::Colour::Red;
                                if (mark.IsUnderground)
                                {
                                    colour = Drawing::Colour::Orange;
                                }
                                Drawing::DrawCircleFilled(screen, 8.0f, Drawing::Colour::White);
                                Drawing::DrawCircleFilled(screen, 6.0f, colour);
                                Drawing::DrawCircleFilled(screen, 4.0f, Drawing::Colour::White);
                                Drawing::DrawCircleFilled(screen, 2.0f, colour);
                                const int32_t markDistance = static_cast<int32_t>((localPlayer->K2_GetActorLocation() - xMarkWorldLocation).Size() * 0.01f);
                                if (markDistance > 20)
                                {
                                    Drawing::DrawString(" [" + std::to_string(markDistance) + "m]", FVector2D(screen.X + 8.f, screen.Y - 1.f), Drawing::Colour::White, false);
                                }
                            }
                        }
                    }
                    else
                    {
                        FVector2D screen;
                        if (playerController->ProjectWorldLocationToScreen(worldMapPosition, &screen))
                        {
                            auto name = UKismetTextLibrary::Conv_TextToString(islandDataEntry->LocalisedName).ToString();
                            name += " [" + std::to_string(distance) + "m]";
                            Drawing::DrawString(name, FVector2D(screen.X, screen.Y - 15.f), Drawing::Colour::White);
                        }
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
