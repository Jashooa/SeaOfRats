#include "Bones.h"

#include "include/SDK/SDK.h"

namespace Hacks
{
    namespace Bones
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

                FTransform boneTransform = mesh->SpaceBasesArray[currentIndex][static_cast<int>(bone)];
                FMatrix boneMatrix = boneTransform.ToMatrixWithScale();
                FMatrix worldBoneMatrix = boneMatrix * worldMatrix;
                boneLocation = worldBoneMatrix.Translation();

                return boneLocation;
            }

            return boneLocation;
        }
    }
}