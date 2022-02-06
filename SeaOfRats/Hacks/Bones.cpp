#include "Bones.h"

#include "include/SDK/SDK.h"

#include "Drawing.h"

namespace Hacks
{
    FVector GetBoneLocation(ACharacter* player, EBones bone)
    {
        FVector boneLocation(0.0f, 0.0f, 0.0f);
        auto mesh = player->Mesh;
        if (mesh)
        {
            if (!mesh->IsVisible())
            {
                return boneLocation;
            }

            FMatrix worldMatrix = mesh->K2_GetComponentToWorld().ToMatrixWithScale();
            auto currentIndex = mesh->CurrentReadSpaceBases;

            auto spaceBases = mesh->SpaceBasesArray[currentIndex];
            if (spaceBases.Num() < 1 || static_cast<uint8_t>(bone) >= spaceBases.Num())
            {
                return boneLocation;
            }

            FTransform boneTransform = spaceBases[static_cast<uint8_t>(bone)];
            FMatrix boneMatrix = boneTransform.ToMatrixWithScale();
            FMatrix worldBoneMatrix = boneMatrix * worldMatrix;
            boneLocation = worldBoneMatrix.GetOrigin();

            return boneLocation;
        }

        return boneLocation;
    }

    void DrawBones(UWorld* world, AActor* actor)
    {
        std::list<std::list<uint8_t>> skeleton;

        if (actor->IsA(AAthenaPlayerCharacter::StaticClass()))
        {
            skeleton = player_skeleton;
        }
        else if (actor->IsA(AAthenaAICharacter::StaticClass()))
        {
            skeleton = ai_skeleton;
        }
        else
        {
            return;
        }

        auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
        auto character = reinterpret_cast<ACharacter*>(actor);

        auto mesh = character->Mesh;
        if (mesh)
        {
            if (!mesh->IsVisible())
            {
                return;
            }

            FMatrix worldMatrix = mesh->K2_GetComponentToWorld().ToMatrixWithScale();
            auto currentIndex = mesh->CurrentReadSpaceBases;
            auto spaceBases = mesh->SpaceBasesArray[currentIndex];
            if (spaceBases.Num() < 1)
            {
                return;
            }

            for (const auto& bones : skeleton)
            {
                FVector2D previousBone;

                for (const auto bone : bones)
                {
                    if (bone >= spaceBases.Num())
                    {
                        return;
                    }
                    FTransform boneTransform = spaceBases[static_cast<int>(bone)];
                    FMatrix boneMatrix = boneTransform.ToMatrixWithScale();
                    FMatrix worldBoneMatrix = boneMatrix * worldMatrix;
                    FVector boneLocation = worldBoneMatrix.GetOrigin();

                    FVector2D screenBone;
                    if (!playerController->ProjectWorldLocationToScreen(boneLocation, &screenBone))
                    {
                        continue;
                    }

                    if (previousBone.X != 0.0f && previousBone.Y != 0.0f)
                    {
                        Drawing::DrawLine(previousBone, screenBone, Drawing::Colour::White);
                    }
                    previousBone = screenBone;
                }
            }
        }
    }
}