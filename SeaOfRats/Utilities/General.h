#pragma once

#include <utility>

#include "Drawing.h"

#include "Math.h"

namespace Utilities
{
    template <typename Enum>
    constexpr std::enable_if_t<std::is_enum<Enum>::value, std::underlying_type_t<Enum>> to_underlying(const Enum value)
    {
        return static_cast<std::underlying_type_t<Enum>>(value);
    }

    static inline bool NearCursor(FVector2D position)
    {
        return PointInCircle(position, Drawing::GetScreenCentre(), 10.f) || (GetAsyncKeyState('R') & 0x8000);
    }
}
