#pragma once

#include <cstdint>
#include <format>
#include <string>

namespace SDK
{
    // ScriptStruct CoreUObject.Guid
    // 0x0010
    struct FGuid
    {
    public:
        uint32_t A; // 0x0000(0x0004)
        uint32_t B; // 0x0004(0x0004)
        uint32_t C; // 0x0008(0x0004)
        uint32_t D; // 0x000C(0x0004)

        inline FGuid() : A(0), B(0), C(0), D(0)
        {
        }

        inline FGuid(uint32_t InA, uint32_t InB, uint32_t InC, uint32_t InD) : A(InA), B(InB), C(InC), D(InD)
        {
        }

        friend bool operator==(const FGuid& X, const FGuid& Y)
        {
            return ((X.A ^ Y.A) | (X.B ^ Y.B) | (X.C ^ Y.C) | (X.D ^ Y.D)) == 0;
        }

        std::string ToString() const
        {
            return std::format("{:08X}-{:08X}-{:08X}-{:08X}", A, B, C, D);
        }
    };
}
