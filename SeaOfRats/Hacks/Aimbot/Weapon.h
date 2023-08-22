#pragma once

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace Aimbot
    {
        class Weapon
        {
        public:
            static void InitAim(SDK::UWorld* world);
            static void CalculateAim(SDK::UWorld* world, SDK::AActor* actor);
            static void Aim(SDK::UWorld* world);

        private:
            struct BestAim
            {
                SDK::AActor* target = nullptr;
                SDK::FVector location;
                SDK::FRotator delta;
                float best = FLT_MAX;
            };

            static constexpr float aimRadius = 100.f;

            static BestAim bestAim;
            static SDK::FVector cameraLocation;
            static SDK::FRotator cameraRotation;
            static SDK::AProjectileWeapon* weapon;
            static SDK::FVector2D centreScreen;
        };
    }
}
