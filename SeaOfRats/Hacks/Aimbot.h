#pragma once

#include "SDK/SDK.h"

using namespace SDK;

namespace Hacks
{
    namespace Aimbot
    {
        void Init(AHUD* hud);
        void SetNearest(UGameViewportClient* client, AActor* actor);
        void Aim(UGameViewportClient* client, AHUD* hud);
    }
}