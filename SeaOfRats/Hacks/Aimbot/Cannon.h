#pragma once

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace Aimbot
    {
        class Cannon
        {
        public:
            static void InitAim(SDK::UWorld* world);
            static void CalculateAim(SDK::UWorld* world, SDK::AActor* actor);
            static void Aim(SDK::UWorld* world);
            static void TracePath(SDK::UWorld* world);

        private:
            struct BestAim
            {
                SDK::AActor* target = nullptr;
                SDK::FVector location;
                SDK::FRotator delta;
                float best = FLT_MAX;
            };

            static SDK::FVector pickHoleToAim(SDK::AHullDamage* damage, SDK::APawn* localPlayer);

            static BestAim bestAim;
            static SDK::FVector cameraLocation;
            static SDK::ACannon* cannon;
            static SDK::FVector2D centreScreen;
        };
    }
}
