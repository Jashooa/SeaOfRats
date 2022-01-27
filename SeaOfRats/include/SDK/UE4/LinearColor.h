#pragma once

namespace SDK
{
    // ScriptStruct CoreUObject.LinearColor
    // 0x0010
    struct FLinearColor
    {
        float R; // 0x0000(0x0004)
        float G; // 0x0004(0x0004)
        float B; // 0x0008(0x0004)
        float A; // 0x000C(0x0004)

        inline FLinearColor() : R(0.f), G(0.f), B(0.f), A(0.f)
        {}

        inline FLinearColor(float InR, float InG, float InB, float InA = 1.f) : R(InR), G(InG), B(InB), A(InA)
        {}
    };
}
