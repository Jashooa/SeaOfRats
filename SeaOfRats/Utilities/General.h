#pragma once

#include <utility>

namespace Utilities
{
    template <typename Enum>
    constexpr std::enable_if_t<std::is_enum<Enum>::value, std::underlying_type_t<Enum>> to_underlying(const Enum value)
    {
        return static_cast<std::underlying_type_t<Enum>>(value);
    }
}
