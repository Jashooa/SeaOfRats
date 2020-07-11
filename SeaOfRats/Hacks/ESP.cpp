#include "ESP.h"

#include <cmath>
#include <string>
#include <vector>

#include "spdlog/spdlog.h"

#include "Config.h"
#include "Drawing.h"
#include "SDK.hpp"

using namespace SDK;

namespace Hacks
{
    void DrawPlayer(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;
        auto player = reinterpret_cast<AAthenaPlayerCharacter*>(actor);

        // Check if me
        if (player == localPlayer)
        {
            return;
        }

        // Check if on-screen
        auto location = actor->K2_GetActorLocation();
        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }

        // Check friendly
        bool friendly = UCrewFunctions::AreCharactersInSameCrew(reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer), player);
        FLinearColor colour = Drawing::Colour::Red;
        if (friendly)
        {
            colour = Drawing::Colour::Green;
        }
        Drawing::DrawBoundingBox(client, hud, actor, colour);

        // Get bounds
        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);

        // Get top coordinates
        auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
        FVector2D topScreen;
        if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
        {
            // Get name
            std::wstring playerName = player->PlayerState->PlayerName.c_str();
            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            playerName += L" [" + std::to_wstring(distance) + L"m]";

            // Draw name
            FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
            Drawing::DrawActorString(hud, playerName, nameScreen, colour);
        }

        // Get bottom coordinates
        auto bottomLocation = FVector(origin.X, origin.Y, origin.Z - extent.Z);
        FVector2D bottomScreen;
        if (playerController->ProjectWorldLocationToScreen(bottomLocation, &bottomScreen))
        {
            // Draw health bar
            auto healthComponent = player->HealthComponent;
            if (healthComponent)
            {
                FVector2D healthScreen = FVector2D(bottomScreen.X, bottomScreen.Y + 10.0f);
                FVector2D healthTopLeft = FVector2D(healthScreen.X - 50.0f, healthScreen.Y);
                FVector2D healthBottomRight = FVector2D(healthScreen.X + 50.0f, healthScreen.Y + 5.0f);
                Drawing::DrawHealthBar(hud, healthTopLeft, healthBottomRight, healthComponent->GetCurrentHealth(), healthComponent->GetMaxHealth());
            }

            // Draw item info
            auto wieldedItem = reinterpret_cast<AWieldableItem*>(player->WieldedItemComponent->CurrentlyWieldedItem);
            if (wieldedItem)
            {
                auto itemDesc = wieldedItem->ItemInfo->Desc;
                if (itemDesc)
                {
                    std::wstring itemName = UKismetTextLibrary::Conv_TextToString(itemDesc->Title).c_str();

                    FVector2D itemScreen = FVector2D(bottomScreen.X, bottomScreen.Y + 25.0f);
                    Drawing::DrawActorString(hud, itemName, itemScreen, Drawing::Colour::White);
                }
            }
        }
    }

    void DrawSkeleton(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;
        auto skeleton = reinterpret_cast<AAthenaAICharacter*>(actor);

        // Check if on-screen
        auto location = actor->K2_GetActorLocation();
        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }
        Drawing::DrawBoundingBox(client, hud, actor, Drawing::Colour::White);

        // Get bounds
        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);

        // Get top coordinates
        auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
        FVector2D topScreen;
        if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
        {
            // Get name
            std::wstring skeletonName = L"Skeleton";
            if (skeleton->AssignedMesh)
            {
                std::string meshName = skeleton->AssignedMesh->GetName();
                if (meshName.find("nme_skellyshadow") != std::string::npos)
                {
                    skeletonName = L"Shadow " + skeletonName;

                    if (skeleton->TeamColorTexture)
                    {
                        std::string skeletonColour = skeleton->TeamColorTexture->GetName();
                        if (skeletonColour.find("venom") != std::string::npos)
                        {
                            skeletonName = L"Purple " + skeletonName;
                        }
                        else if (skeletonColour.find("shark") != std::string::npos)
                        {
                            skeletonName = L"Blue " + skeletonName;
                        }
                        else if (skeletonColour.find("lightning") != std::string::npos)
                        {
                            skeletonName = L"White " + skeletonName;
                        }
                        else if (skeletonColour.find("player") != std::string::npos)
                        {
                            skeletonName = L"Pink " + skeletonName;
                        }
                        else if (skeletonColour.find("skeleton") != std::string::npos)
                        {
                            skeletonName = L"Green " + skeletonName;
                        }
                        else
                        {
                            skeletonName = std::wstring(skeletonColour.begin(), skeletonColour.end());
                        }
                    }
                }
                else if (meshName.find("nme_skellyash") != std::string::npos)
                {
                    skeletonName = L"Ashen " + skeletonName;
                }

                if (meshName.find("_cap_") != std::string::npos)
                {
                    skeletonName += L" Captain";
                }

                skeletonName += L" " + std::wstring(meshName.begin(), meshName.end());
            }
            //float worldDistance = localPlayer->GetDistanceTo(actor);
            

            auto namePlate = reinterpret_cast<UAINameplateComponent*>(skeleton->GetComponentByClass(UAINameplateComponent::StaticClass()));
            //bool isNameplateShown = false;
            if (!UKismetTextLibrary::TextIsEmpty(namePlate->DisplayNameAsText))
            {
                //isNameplateShown = worldDistance < namePlate->VisibleUntilWorldDistance;
                std::wstring namePlateText = UKismetTextLibrary::Conv_TextToString(namePlate->DisplayNameAsText).c_str();
                skeletonName = namePlateText + L" " + skeletonName;
            }

            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            skeletonName += L" [" + std::to_wstring(distance) + L"m]";

            // Draw name
            FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
            Drawing::DrawActorString(hud, skeletonName, nameScreen, Drawing::Colour::White);
        }

        // Get bottom coordinates
        auto bottomLocation = FVector(origin.X, origin.Y, origin.Z - extent.Z);
        FVector2D bottomScreen;
        if (playerController->ProjectWorldLocationToScreen(bottomLocation, &bottomScreen))
        {

            // Draw health bar
            /*auto healthComponent = skeleton->HealthComponent;
            if (healthComponent)
            {
                FVector2D healthScreen = FVector2D(bottomScreen.X, bottomScreen.Y + 10.0f);
                FVector2D healthTopLeft = FVector2D(healthScreen.X - 50.0f, healthScreen.Y);
                FVector2D healthBottomRight = FVector2D(healthTopLeft.X + 100.0f, healthTopLeft.Y + 5.0f);
                Drawing::DrawHealthBar(hud, healthTopLeft, healthBottomRight, healthComponent->GetCurrentHealth(), healthComponent->GetMaxHealth());
            }*/

            // Draw item info
            auto wieldedItem = reinterpret_cast<AWieldableItem*>(skeleton->WieldedItemComponent->CurrentlyWieldedItem);
            if (wieldedItem)
            {
                auto itemDesc = wieldedItem->ItemInfo->Desc;
                if (itemDesc)
                {
                    std::wstring itemName = UKismetTextLibrary::Conv_TextToString(itemDesc->Title).c_str();

                    FVector2D itemScreen = FVector2D(bottomScreen.X, bottomScreen.Y + 10.0f);
                    Drawing::DrawActorString(hud, itemName, itemScreen, Drawing::Colour::White);
                }
            }
        }
    }

    void DrawShark(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;
        auto shark = reinterpret_cast<ASharkPawn*>(actor);

        // Check if on-screen
        auto location = actor->K2_GetActorLocation();
        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }

        // Get bounds
        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);

        // Get top coordinates
        auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
        FVector2D topScreen;
        if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
        {
            // Get name
            std::wstring sharkName = L"Shark ";
            std::string sharkActorName = shark->GetName();
            sharkName += L" " + std::wstring(sharkActorName.begin(), sharkActorName.end());

            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            sharkName += L" [" + std::to_wstring(distance) + L"m]";

            // Draw name
            FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 25.0f);
            Drawing::DrawActorString(hud, sharkName, nameScreen, Drawing::Colour::White);

            // Draw health bar
            auto healthComponent = shark->HealthComponent;
            if (healthComponent)
            {
                FVector2D healthScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
                FVector2D healthTopLeft = FVector2D(healthScreen.X - 50.0f, healthScreen.Y);
                FVector2D healthBottomRight = FVector2D(healthTopLeft.X + 100.0f, healthTopLeft.Y + 5.0f);
                Drawing::DrawHealthBar(hud, healthTopLeft, healthBottomRight, healthComponent->GetCurrentHealth(), healthComponent->GetMaxHealth());
            }
        }
    }

    void DrawMermaid(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;
        auto mermaid = reinterpret_cast<AMermaid*>(actor);

        // Check if on-screen
        auto location = actor->K2_GetActorLocation();
        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }

        // Get bounds
        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);

        // Get top coordinates
        auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
        FVector2D topScreen;
        if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
        {
            // Get name
            std::wstring mermaidName = L"Mermaid ";

            // Check if my mermaid
            auto localCrewId = UCrewFunctions::GetCrewIdFromActor(client->World, localPlayer);
            auto crewIds = mermaid->GetCrewIdsResponsibleForSavingAsCopy();
            for (int32_t i = 0; i < crewIds.Num(); ++i)
            {
                if (UKismetGuidLibrary::EqualEqual_GuidGuid(crewIds[i], localCrewId))
                {
                    mermaidName = L"My " + mermaidName;
                }
            }

            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            mermaidName += L" [" + std::to_wstring(distance) + L"m]";

            // Draw name
            FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
            Drawing::DrawActorString(hud, mermaidName, nameScreen, Drawing::Colour::White);
        }
    }

    void DrawShip(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
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

        std::string actorName = actor->GetName();
        std::wstring shipText;
        if (actorName.find("Large") != std::string::npos)
        {
            shipText = L"Galleon";
        }
        else if (actorName.find("Medium") != std::string::npos)
        {
            shipText = L"Brigantine";
        }
        else if (actorName.find("Small") != std::string::npos)
        {
            shipText = L"Sloop";
        }

        if (actorName.find("AI") != std::string::npos)
        {
            shipText = L"Skeleton " + shipText;
        }

        if (UCrewFunctions::IsActorMemberOfCharactersCrew(ship, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
        {
            shipText = L"My " + shipText;
        }

        shipText += L" [" + std::to_wstring(distance) + L"m]";

        FVector2D nameScreen = FVector2D(screen.X, screen.Y - 25.0f);
        Drawing::DrawActorString(hud, shipText, nameScreen, Drawing::Colour::White);

        auto waterInfo = ship->GetInternalWater();
        if (waterInfo)
        {
            FVector2D healthScreen = FVector2D(screen.X, screen.Y - 10.0f);
            FVector2D healthTopLeft = FVector2D(healthScreen.X - 50.0f, healthScreen.Y);
            FVector2D healthBottomRight = FVector2D(healthScreen.X + 50.0f, healthScreen.Y + 5.0f);
            float waterMax = waterInfo->InternalWaterParams.MaxWaterAmount;
            float waterLevel = waterMax - waterInfo->WaterAmount;
            Drawing::DrawHealthBar(hud, healthTopLeft, healthBottomRight, waterLevel, waterMax);
        }
    }

    void DrawShipFar(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
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
        std::wstring shipType;
        if (actorName.find("Large") != std::string::npos)
        {
            shipType = L"Galleon";
        }
        else if (actorName.find("Medium") != std::string::npos)
        {
            shipType = L"Brigantine";
        }
        else if (actorName.find("Small") != std::string::npos)
        {
            shipType = L"Sloop";
        }

        if (actorName.find("AI") != std::string::npos)
        {
            shipType = L"Skeleton " + shipType;
        }

        if (UCrewFunctions::IsActorMemberOfCharactersCrew(ship, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
        {
            shipType = L"My " + shipType;
        }

        std::wstring shipText = shipType + L" [" + std::to_wstring(distance) + L"m]";

        FVector2D nameScreen = FVector2D(screen.X, screen.Y - 10.0f);
        Drawing::DrawActorString(hud, shipText, nameScreen, Drawing::Colour::White);
    }

    void DrawRowboat(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;
        auto rowboat = reinterpret_cast<ARowboat*>(actor);

        // Check if on-screen
        auto location = actor->K2_GetActorLocation();
        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }

        // Get bounds
        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);

        // Get top coordinates
        auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
        FVector2D topScreen;
        if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
        {
            // Get name
            std::wstring rowboatName = L"Rowboat ";

            std::string actorName = actor->GetName();
            if (actorName.find("Harpoon") != std::string::npos)
            {
                rowboatName = L"Harpoon " + rowboatName;
            }

            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            rowboatName += L" [" + std::to_wstring(distance) + L"m]";

            // Draw name
            FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
            Drawing::DrawActorString(hud, rowboatName, nameScreen, Drawing::Colour::White);
        }
    }

    void DrawItem(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;
        auto item = reinterpret_cast<ABootyProxy*>(actor);

        // Check if on-screen
        auto location = actor->K2_GetActorLocation();
        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }

        // Get item info
        auto itemInfo = reinterpret_cast<ABootyItemInfo*>(item->ItemInfo);
        if (!itemInfo)
        {
            spdlog::warn("ItemInfo null");
            return;
        }

        // Get bounds
        FVector origin, extent;
        actor->GetActorBounds(true, &origin, &extent);

        // Get top coordinates
        auto topLocation = FVector(origin.X, origin.Y, origin.Z + extent.Z);
        FVector2D topScreen;
        if (playerController->ProjectWorldLocationToScreen(topLocation, &topScreen))
        {
            // Get colour
            std::string rarity = itemInfo->Rarity.GetName();
            FLinearColor colour = Drawing::Colour::Blue;
            if (rarity == "Common")
            {
                colour = Drawing::Colour::Grey;
            }
            else if (rarity == "Rare")
            {
                colour = Drawing::Colour::Green;
            }
            else if (rarity == "Legendary")
            {
                colour = Drawing::Colour::Purple;
            }
            else if (rarity == "Mythical")
            {
                colour = Drawing::Colour::Orange;
            }

            // Get name
            int32_t distance = static_cast<int32_t>(localPlayer->GetDistanceTo(actor) * 0.01f);
            std::wstring itemName = UKismetTextLibrary::Conv_TextToString(itemInfo->Desc->Title).c_str();
            std::wstring itemText = itemName + L" [" + std::to_wstring(distance) + L"m]";

            // Draw name
            FVector2D nameScreen = FVector2D(topScreen.X, topScreen.Y - 10.0f);
            Drawing::DrawActorString(hud, itemText, nameScreen, colour);
        }
    }

    void DrawMap(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;
        auto localPlayer = playerController->Pawn;
        auto table = reinterpret_cast<AMapTable*>(actor);

        auto parentShip = actor->GetAttachParentActor();
        /*auto currentShip = reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)->GetCurrentShip();
        if (parentShip != currentShip)
        {
            return;
        }*/

        if (!UCrewFunctions::IsActorMemberOfCharactersCrew(parentShip, reinterpret_cast<AAthenaPlayerCharacter*>(localPlayer)))
        {
            return;
        }

        auto pins = table->MapPins;

        for (int32_t i = 0; i < pins.Num(); ++i)
        {
            auto pin = pins[i];
            FVector location((pin.X * 100.0f), (pin.Y * 100.0f), 100.0f);

            FVector2D screen;
            if (!playerController->ProjectWorldLocationToScreen(location, &screen))
            {
                continue;
            }

            int32_t distance = static_cast<int32_t>(UVectorMaths::Distance(localPlayer->RootComponent->K2_GetComponentLocation(), location) * 0.01f);
            std::wstring pinText = L"Map Pin [" + std::to_wstring(distance) + L"m]";
            Drawing::DrawActorString(hud, pinText, screen, Drawing::Colour::White);
        }
    }

    void DrawDebug(UGameViewportClient* client, AHUD* hud, AActor* actor)
    {
        auto playerController = client->GameInstance->LocalPlayers[0]->PlayerController;

        auto location = actor->K2_GetActorLocation();
        FVector2D screen;
        if (!playerController->ProjectWorldLocationToScreen(location, &screen))
        {
            return;
        }

        std::string name = actor->GetName();
        if (name.find("_") != std::string::npos)
            return;
        if (name.find("cmn") != std::string::npos)
            return;
        if (name.find("wsp") != std::string::npos)
            return;
        if (name.find("water") != std::string::npos)
            return;
        if (name.find("Light") != std::string::npos)
            return;
        if (name.find("vfx") != std::string::npos)
            return;
        if (name.find("ske") != std::string::npos)
            return;
        if (name.find("wld") != std::string::npos)
            return;
        if (name.find("dvr") != std::string::npos)
            return;
        if (name.find("ref") != std::string::npos)
            return;
        if (name.find("volume") != std::string::npos)
            return;
        if (name.find("Volume") != std::string::npos)
            return;
        if (name.find("rocks") != std::string::npos)
            return;
        if (name.find("jetty") != std::string::npos)
            return;
        if (name.find("shop") != std::string::npos)
            return;
        if (name.find("bp") != std::string::npos)
            return;
        if (name.find("bld") != std::string::npos)
            return;
        if (name.find("bsp") != std::string::npos)
            return;
        if (name.find("Nav") != std::string::npos)
            return;
        if (name.find("Water") != std::string::npos)
            return;
        if (name.find("FishCreature") != std::string::npos)
            return;

        name = actor->GetFullName();
        std::wstring namew(name.begin(), name.end());
        Drawing::DrawActorString(hud, namew, screen, Drawing::Colour::Red);
    }

    void RenderESP(UGameViewportClient* client, AHUD* hud)
    {
        UWorld* world = client->World;
        if (!world)
        {
            spdlog::warn("World null");
            return;
        }

        /*auto levels = world->Levels;

        for (int32_t i = 6; i < levels.Num(); ++i)
        {
            auto actors = levels[i]->AActors;

            for (int32_t j = 0; j < actors.Num(); ++j)
            {
                AActor* actor = actors[j];

                if (!actor)
                {
                    continue;
                }
            }
        }*/

        ULevel* level = world->PersistentLevel;
        if (!level)
        {
            spdlog::warn("PersistentLevel null");
            return;
        }

        auto actors = level->AActors;

        for (int32_t i = 0; i < actors.Num(); ++i)
        {
            AActor* actor = actors[i];

            if (!actor)
            {
                continue;
            }

            if (actor == client->GameInstance->LocalPlayers[0]->PlayerController)
            {
                continue;
            }

            if (actor->IsA(AAthenaPlayerCharacter::StaticClass()) && config->playerESP)
            {
                spdlog::debug("DrawPlayer Before");
                DrawPlayer(client, hud, actor);
                spdlog::debug("DrawPlayer After");
                continue;
            }

            if (actor->IsA(AAthenaAICharacter::StaticClass()) && config->skeletonESP)
            {
                spdlog::debug("DrawSkeleton Before");
                DrawSkeleton(client, hud, actor);
                spdlog::debug("DrawSkeleton After");
                continue;
            }

            if (actor->IsA(ASharkPawn::StaticClass()) && config->sharkESP)
            {
                spdlog::debug("DrawShark Before");
                DrawShark(client, hud, actor);
                spdlog::debug("DrawShark After");
                continue;
            }

            if (actor->IsA(AMermaid::StaticClass()) && config->mermaidESP)
            {
                spdlog::debug("DrawMermaid Before");
                DrawMermaid(client, hud, actor);
                spdlog::debug("DrawMermaid After");
                continue;
            }

            if (actor->IsA(AShip::StaticClass()) && config->shipESP)
            {
                spdlog::debug("DrawShip Before");
                DrawShip(client, hud, actor);
                spdlog::debug("DrawShip After");
                continue;
            }

            if (actor->IsA(AShipNetProxy::StaticClass()) && config->shipFarESP)
            {
                spdlog::debug("DrawShipFar Before");
                DrawShipFar(client, hud, actor);
                spdlog::debug("DrawShipFar After");
                continue;
            }

            if (actor->IsA(ARowboat::StaticClass()) && config->rowboatESP)
            {
                spdlog::debug("DrawRowboat Before");
                DrawRowboat(client, hud, actor);
                spdlog::debug("DrawRowboat After");
                continue;
            }

            if (actor->IsA(ABootyProxy::StaticClass()) && config->itemESP)
            {
                spdlog::debug("DrawItem Before");
                DrawItem(client, hud, actor);
                spdlog::debug("DrawItem After");
                continue;
            }

            if (actor->IsA(AMapTable::StaticClass()) && config->mapESP)
            {
                spdlog::debug("DrawMapPins Before");
                DrawMap(client, hud, actor);
                spdlog::debug("DrawMapPins After");
                continue;
            }

            if (config->debugESP)
            {
                DrawDebug(client, hud, actor);
            }
        }
    }
}