#include "Bones.h"

#include "Drawing.h"

using namespace SDK;

namespace Hacks
{
    FVector GetBoneLocation(ACharacter* player, EBones bone)
    {
        FVector boneLocation(0.f, 0.f, 0.f);
        if (const auto mesh = player->Mesh)
        {
            if (!mesh->IsVisible())
            {
                return boneLocation;
            }

            const FMatrix worldMatrix = mesh->K2_GetComponentToWorld().ToMatrixWithScale();
            const auto currentIndex = mesh->CurrentReadSpaceBases;

            const auto spaceBases = mesh->SpaceBasesArray[currentIndex];
            if (spaceBases.Num() < 1 || static_cast<uint8_t>(bone) >= spaceBases.Num())
            {
                return boneLocation;
            }

            const FTransform boneTransform = spaceBases[static_cast<uint8_t>(bone)];
            FMatrix boneMatrix = boneTransform.ToMatrixWithScale();
            const FMatrix worldBoneMatrix = boneMatrix * worldMatrix;
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

        const auto playerController = world->OwningGameInstance->LocalPlayers[0]->PlayerController;
        const auto character = reinterpret_cast<ACharacter*>(actor);

        if (const auto mesh = character->Mesh)
        {
            if (!mesh->IsVisible())
            {
                return;
            }

            const FMatrix worldMatrix = mesh->K2_GetComponentToWorld().ToMatrixWithScale();
            const auto currentIndex = mesh->CurrentReadSpaceBases;
            const auto spaceBases = mesh->SpaceBasesArray[currentIndex];
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
                    const FTransform boneTransform = spaceBases[static_cast<int>(bone)];
                    FMatrix boneMatrix = boneTransform.ToMatrixWithScale();
                    const FMatrix worldBoneMatrix = boneMatrix * worldMatrix;
                    const FVector boneLocation = worldBoneMatrix.GetOrigin();

                    FVector2D screenBone;
                    if (!playerController->ProjectWorldLocationToScreen(boneLocation, &screenBone))
                    {
                        continue;
                    }

                    if (previousBone.X != 0.f && previousBone.Y != 0.f)
                    {
                        Drawing::DrawLine(previousBone, screenBone, Drawing::Colour::White);
                    }
                    previousBone = screenBone;
                }
            }
        }
    }
}
