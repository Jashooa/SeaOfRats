#include "Bones.h"

#include "Utilities/Drawing.h"

using namespace SDK;

namespace Hacks
{
    FVector GetBoneLocation(ACharacter* player, EBones bone)
    {
        auto boneLocation = FVector{};
        if (const auto mesh = player->Mesh)
        {
            if (!mesh->IsVisible())
            {
                return boneLocation;
            }

            const auto worldMatrix = mesh->K2_GetComponentToWorld().ToMatrixWithScale();
            const auto currentIndex = mesh->CurrentReadSpaceBases;

            const auto spaceBases = mesh->SpaceBasesArray[currentIndex];
            if (spaceBases.Num() < 1 || static_cast<uint8_t>(bone) >= spaceBases.Num())
            {
                return boneLocation;
            }

            const auto& boneTransform = spaceBases[static_cast<uint8_t>(bone)];
            const auto boneMatrix = boneTransform.ToMatrixWithScale();
            const auto worldBoneMatrix = boneMatrix * worldMatrix;
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

            const auto worldMatrix = mesh->K2_GetComponentToWorld().ToMatrixWithScale();
            const auto currentIndex = mesh->CurrentReadSpaceBases;
            const auto spaceBases = mesh->SpaceBasesArray[currentIndex];
            if (spaceBases.Num() < 1)
            {
                return;
            }

            for (const auto& bones : skeleton)
            {
                auto previousBone = FVector2D{};

                for (const auto& bone : bones)
                {
                    if (bone >= spaceBases.Num())
                    {
                        return;
                    }
                    const auto& boneTransform = spaceBases[static_cast<int>(bone)];
                    const auto boneMatrix = boneTransform.ToMatrixWithScale();
                    const auto worldBoneMatrix = boneMatrix * worldMatrix;
                    const auto boneLocation = worldBoneMatrix.GetOrigin();

                    auto bonePosition = FVector2D{};
                    if (!playerController->ProjectWorldLocationToScreen(boneLocation, &bonePosition))
                    {
                        continue;
                    }

                    if (previousBone.X != 0.f && previousBone.Y != 0.f)
                    {
                        Utilities::Drawing::DrawLine(previousBone, bonePosition, Utilities::Drawing::Colour::White);
                    }
                    previousBone = bonePosition;
                }
            }
        }
    }
}
