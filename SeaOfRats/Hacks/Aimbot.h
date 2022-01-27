#pragma once

#include "include/SDK/SDK.h"

using namespace SDK;

namespace Hacks
{
    namespace Aimbot
    {
        void Init(UGameViewportClient* client);
        void CalculateAim(UGameViewportClient* client, AActor* actor);
        void Aim(UGameViewportClient* client, AHUD* hud);
    }
}