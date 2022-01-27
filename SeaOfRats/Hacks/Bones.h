#pragma once

#include <list>

#include "include/SDK/SDK.h"

#include "Utilities/General.h"

using namespace SDK;

namespace Hacks
{
    enum class EBones : uint8_t
    {
        MOVEMENT__Skeleton = 0,
        SCALE__Skeleton = 1,
        BASE__Skeleton = 2,
        UPPER_BODY_LOCK__Skeleton = 3,
        WAIST__Skeleton = 4,
        TORSO__Skeleton = 5,
        CHEST__Skeleton = 6,
        NECK1__Skeleton = 7,
        NECK2__Skeleton = 8,
        HEAD__Skeleton = 9,
        JAW__Skeleton = 10,
        MID_FACE_UNDER_CHIN__Skeleton = 11,
        MID_FACE_LOWERLIP_OUTER__Skeleton = 12,
        MID_FACE_LOWERLIP_INNER__Skeleton = 13,
        LF_FACE_LOWERLIP_OUTER__Skeleton = 14,
        LF_FACE_LOWERLIP_INNER__Skeleton = 15,
        RT_FACE_LOWERLIP_INNER__Skeleton = 16,
        RT_FACE_LOWERLIP_OUTER__Skeleton = 17,
        LF_EYE__Skeleton = 18,
        MID_FACE_UPPERLIP_OUTER__Skeleton = 19,
        MID_FACE_NOSE__Skeleton = 20,
        MID_FACE_UPPERLIP_INNER__Skeleton = 21,
        LF_FACE_BROW_OUTER__Skeleton = 22,
        LF_FACE_BROW_MID__Skeleton = 23,
        LF_FACE_CHEEK_MID__Skeleton = 24,
        LF_FACE_UPPERLID_MID__Skeleton = 25,
        LF_FACE_UPPERLID_OUTER__Skeleton = 26,
        LF_FACE_LOWERLID_OUTER__Skeleton = 27,
        LF_FACE_LOWERLID_INNER__Skeleton = 28,
        LF_FACE_MOUTHFOLD_LOWER__Skeleton = 29,
        LF_FACE_LIPCORNER__Skeleton = 30,
        LF_FACE_MOUTHFOLD_UPPER__Skeleton = 31,
        LF_FACE_UPPERLIP_OUTER__Skeleton = 32,
        LF_FACE_BROW_INNER__Skeleton = 33,
        LF_FACE_UPPERLID_INNER__Skeleton = 34,
        LF_FACE_UPPERLIP_INNER__Skeleton = 35,
        RT_EYE__Skeleton = 36,
        RT_FACE_BROW_INNER__Skeleton = 37,
        RT_FACE_BROW_MID__Skeleton = 38,
        RT_FACE_BROW_OUTER__Skeleton = 39,
        RT_FACE_CHEEK_MID__Skeleton = 40,
        RT_FACE_LIPCORNER__Skeleton = 41,
        RT_FACE_LOWERLID_INNER__Skeleton = 42,
        RT_FACE_LOWERLID_OUTER__Skeleton = 43,
        RT_FACE_MOUTHFOLD_LOWER__Skeleton = 44,
        RT_FACE_MOUTHFOLD_UPPER__Skeleton = 45,
        RT_FACE_UPPERLID_INNER__Skeleton = 46,
        RT_FACE_UPPERLID_MID__Skeleton = 47,
        RT_FACE_UPPERLID_OUTER__Skeleton = 48,
        RT_FACE_UPPERLIP_INNER__Skeleton = 49,
        RT_FACE_UPPERLIP_OUTER__Skeleton = 50,
        LF_CLAVICLE__Skeleton = 51,
        LF_SHOULDER__Skeleton = 52,
        LF_ELBOW__Skeleton = 53,
        LF_WRIST__Skeleton = 54,
        LF_FINGD_ROOT__Skeleton = 55,
        LF_FINGD__Skeleton = 56,
        LF_FINGD1__Skeleton = 57,
        LF_FINGD2__Skeleton = 58,
        LF_FINGC_ROOT__Skeleton = 59,
        LF_FINGC__Skeleton = 60,
        LF_FINGC1__Skeleton = 61,
        LF_FINGC2__Skeleton = 62,
        LF_FINGB__Skeleton = 63,
        LF_FINGB1__Skeleton = 64,
        LF_FINGB2__Skeleton = 65,
        LF_FINGA__Skeleton = 66,
        LF_FINGA1__Skeleton = 67,
        LF_FINGA2__Skeleton = 68,
        LF_THUMB_ROOT__Skeleton = 69,
        LF_THUMB1__Skeleton = 70,
        LF_THUMB2__Skeleton = 71,
        LF_PROP__Skeleton = 72,
        LF_TWIST_WRIST__Skeleton = 73,
        LF_TWIST_SHOULDER__Skeleton = 74,
        CAMERA_ROOT__Skeleton = 75,
        CAMERA__Skeleton = 76,
        CAMERA_PROP__Skeleton = 77,
        LF_CAMERA_IK_HAND__Skeleton = 78,
        RT_CAMERA_IK_HAND__Skeleton = 79,
        RT_CLAVICLE__Skeleton = 80,
        RT_SHOULDER__Skeleton = 81,
        RT_ELBOW__Skeleton = 82,
        RT_WRIST__Skeleton = 83,
        RT_FINGD_ROOT__Skeleton = 84,
        RT_FINGD__Skeleton = 85,
        RT_FINGD1__Skeleton = 86,
        RT_FINGD2__Skeleton = 87,
        RT_FINGC_ROOT__Skeleton = 88,
        RT_FINGC__Skeleton = 89,
        RT_FINGC1__Skeleton = 90,
        RT_FINGC2__Skeleton = 91,
        RT_FINGB__Skeleton = 92,
        RT_FINGB1__Skeleton = 93,
        RT_FINGB2__Skeleton = 94,
        RT_FINGA__Skeleton = 95,
        RT_FINGA1__Skeleton = 96,
        RT_FINGA2__Skeleton = 97,
        RT_THUMB_ROOT__Skeleton = 98,
        RT_THUMB1__Skeleton = 99,
        RT_THUMB2__Skeleton = 100,
        RT_PROP__Skeleton = 101,
        RT_TWIST_WRIST__Skeleton = 102,
        RT_TWIST_SHOULDER__Skeleton = 103,
        LF_DRIVEN_CHEST_RISE__Skeleton = 104,
        RT_DRIVEN_CHEST_RISE__Skeleton = 105,
        LF_HIP__Skeleton = 106,
        LF_KNEE__Skeleton = 107,
        LF_ANKLE__Skeleton = 108,
        LF_TOE__Skeleton = 109,
        LF_TWIST_HIP__Skeleton = 110,
        RT_HIP__Skeleton = 111,
        RT_KNEE__Skeleton = 112,
        RT_ANKLE__Skeleton = 113,
        RT_TOE__Skeleton = 114,
        RT_TWIST_HIP__Skeleton = 115,
        LF_DRIVEN_BUTT__Skeleton = 116,
        RT_DRIVEN_BUTT__Skeleton = 117,
        LF_IK_FOOT__Skeleton = 118,
        IK_HANDS__Skeleton = 119,
        LF_IK_HAND__Skeleton = 120,
        RT_IK_HAND__Skeleton = 121,
        RT_IK_FOOT__Skeleton = 122,
    };

    enum class EBonesSkeleton : uint8_t
    {
        MOVEMENT__Skeleton = 0,
        SCALE__Skeleton = 1,
        BASE__Skeleton = 2,
        UPPER_BODY_LOCK__Skeleton = 3,
        WAIST__Skeleton = 4,
        TORSO__Skeleton = 5,
        CHEST__Skeleton = 6,
        NECK1__Skeleton = 7,
        NECK2__Skeleton = 8,
        HEAD__Skeleton = 9,
        JAW__Skeleton = 10,
        LF_CLAVICLE__Skeleton = 11,
        LF_SHOULDER__Skeleton = 12,
        LF_ELBOW__Skeleton = 13,
        LF_WRIST__Skeleton = 14,
        LF_FINGD_ROOT__Skeleton = 15,
        LF_FINGD__Skeleton = 16,
        LF_FINGD1__Skeleton = 17,
        LF_FINGD2__Skeleton = 18,
        LF_FINGC_ROOT__Skeleton = 19,
        LF_FINGC__Skeleton = 20,
        LF_FINGC1__Skeleton = 21,
        LF_FINGC2__Skeleton = 22,
        LF_FINGB__Skeleton = 23,
        LF_FINGB1__Skeleton = 24,
        LF_FINGB2__Skeleton = 25,
        LF_FINGA__Skeleton = 26,
        LF_FINGA1__Skeleton = 27,
        LF_FINGA2__Skeleton = 28,
        LF_THUMB_ROOT__Skeleton = 29,
        LF_THUMB1__Skeleton = 30,
        LF_THUMB2__Skeleton = 31,
        LF_PROP__Skeleton = 32,
        LF_TWIST_WRIST__Skeleton = 33,
        LF_TWIST_SHOULDER__Skeleton = 34,
        CAMERA_ROOT__Skeleton = 35,
        CAMERA__Skeleton = 36,
        CAMERA_PROP__Skeleton = 37,
        LF_CAMERA_IK_HAND__Skeleton = 38,
        RT_CAMERA_IK_HAND__Skeleton = 39,
        RT_CLAVICLE__Skeleton = 40,
        RT_SHOULDER__Skeleton = 41,
        RT_ELBOW__Skeleton = 42,
        RT_WRIST__Skeleton = 43,
        RT_FINGD_ROOT__Skeleton = 44,
        RT_FINGD__Skeleton = 45,
        RT_FINGD1__Skeleton = 46,
        RT_FINGD2__Skeleton = 47,
        RT_FINGC_ROOT__Skeleton = 48,
        RT_FINGC__Skeleton = 49,
        RT_FINGC1__Skeleton = 50,
        RT_FINGC2__Skeleton = 51,
        RT_FINGB__Skeleton = 52,
        RT_FINGB1__Skeleton = 53,
        RT_FINGB2__Skeleton = 54,
        RT_FINGA__Skeleton = 55,
        RT_FINGA1__Skeleton = 56,
        RT_FINGA2__Skeleton = 57,
        RT_THUMB_ROOT__Skeleton = 58,
        RT_THUMB1__Skeleton = 59,
        RT_THUMB2__Skeleton = 60,
        RT_PROP__Skeleton = 61,
        RT_TWIST_WRIST__Skeleton = 62,
        RT_TWIST_SHOULDER__Skeleton = 63,
        LF_DRIVEN_CHEST_RISE__Skeleton = 64,
        RT_DRIVEN_CHEST_RISE__Skeleton = 65,
        LF_HIP__Skeleton = 66,
        LF_KNEE__Skeleton = 67,
        LF_ANKLE__Skeleton = 68,
        LF_TOE__Skeleton = 69,
        LF_TWIST_HIP__Skeleton = 70,
        RT_HIP__Skeleton = 71,
        RT_KNEE__Skeleton = 72,
        RT_ANKLE__Skeleton = 73,
        RT_TOE__Skeleton = 74,
        RT_TWIST_HIP__Skeleton = 75,
        LF_DRIVEN_BUTT__Skeleton = 76,
        RT_DRIVEN_BUTT__Skeleton = 77,
        LF_IK_FOOT__Skeleton = 78,
        IK_HANDS__Skeleton = 79,
        LF_IK_HAND__Skeleton = 80,
        RT_IK_HAND__Skeleton = 81,
        RT_IK_FOOT__Skeleton = 82,
    };

    const std::list<uint8_t> player_left_arm = {
        Utilities::to_underlying(EBones::LF_FINGB__Skeleton),
        Utilities::to_underlying(EBones::LF_ELBOW__Skeleton),
        Utilities::to_underlying(EBones::LF_TWIST_SHOULDER__Skeleton),
        Utilities::to_underlying(EBones::NECK1__Skeleton)
    };
    const std::list<uint8_t> player_right_arm = {
        Utilities::to_underlying(EBones::RT_FINGB__Skeleton),
        Utilities::to_underlying(EBones::RT_ELBOW__Skeleton),
        Utilities::to_underlying(EBones::RT_TWIST_SHOULDER__Skeleton),
        Utilities::to_underlying(EBones::NECK1__Skeleton)
    };
    const std::list<uint8_t> player_left_leg = {
        Utilities::to_underlying(EBones::LF_ANKLE__Skeleton),
        Utilities::to_underlying(EBones::LF_KNEE__Skeleton),
        Utilities::to_underlying(EBones::LF_TWIST_HIP__Skeleton),
        Utilities::to_underlying(EBones::WAIST__Skeleton)
    };
    const std::list<uint8_t> player_right_leg = {
        Utilities::to_underlying(EBones::RT_ANKLE__Skeleton),
        Utilities::to_underlying(EBones::RT_KNEE__Skeleton),
        Utilities::to_underlying(EBones::RT_TWIST_HIP__Skeleton),
        Utilities::to_underlying(EBones::WAIST__Skeleton)
    };
    const std::list<uint8_t> player_spine = {
        Utilities::to_underlying(EBones::WAIST__Skeleton),
        Utilities::to_underlying(EBones::TORSO__Skeleton),
        Utilities::to_underlying(EBones::CHEST__Skeleton),
        Utilities::to_underlying(EBones::NECK1__Skeleton),
        Utilities::to_underlying(EBones::HEAD__Skeleton)
    };

    const std::list<uint8_t> ai_left_arm = {
        Utilities::to_underlying(EBonesSkeleton::LF_FINGB__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::LF_ELBOW__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::LF_TWIST_SHOULDER__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::NECK1__Skeleton)
    };
    const std::list<uint8_t> ai_right_arm = {
        Utilities::to_underlying(EBonesSkeleton::RT_FINGB__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::RT_ELBOW__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::RT_TWIST_SHOULDER__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::NECK1__Skeleton)
    };
    const std::list<uint8_t> ai_left_leg = {
        Utilities::to_underlying(EBonesSkeleton::LF_ANKLE__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::LF_KNEE__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::LF_TWIST_HIP__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::WAIST__Skeleton)
    };
    const std::list<uint8_t> ai_right_leg = {
        Utilities::to_underlying(EBonesSkeleton::RT_ANKLE__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::RT_KNEE__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::RT_TWIST_HIP__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::WAIST__Skeleton)
    };
    const std::list<uint8_t> ai_spine = {
        Utilities::to_underlying(EBonesSkeleton::WAIST__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::TORSO__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::CHEST__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::NECK1__Skeleton),
        Utilities::to_underlying(EBonesSkeleton::HEAD__Skeleton)
    };

    static const std::list<std::list<uint8_t>> player_skeleton = {
        player_left_arm,
        player_right_arm,
        player_left_leg,
        player_right_leg,
        player_spine
    };

    static const std::list<std::list<uint8_t>> ai_skeleton = {
        ai_left_arm,
        ai_right_arm,
        ai_left_leg,
        ai_right_leg,
        ai_spine
    };

    FVector GetBoneLocation(ACharacter* player, EBones bone);
    void DrawBones(UGameViewportClient* client, AHUD* hud, AActor* actor);
}
