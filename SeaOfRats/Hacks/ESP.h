#pragma once

#include "include/SDK/SDK.h"

using namespace SDK;

namespace Hacks
{
    namespace ESP
    {
        void DrawPlayer(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawSkeleton(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawShark(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawKraken(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawKrakenTentacle(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawAnimal(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawMermaid(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawShip(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawShipFar(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawGhostShip(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawRowboat(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawItem(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawBarrel(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawShipwreck(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawStorm(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawEvent(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawMap(UGameViewportClient* client, AHUD* hud, AActor* actor);
        void DrawDebug(UGameViewportClient* client, AHUD* hud, AActor* actor);
    }
}
