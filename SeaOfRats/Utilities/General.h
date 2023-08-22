#pragma once

#include <type_traits>

#include "include/SDK/SDK.h"

namespace Utilities
{
	namespace General
	{
		template <typename Enum>
		constexpr std::enable_if_t<std::is_enum<Enum>::value, std::underlying_type_t<Enum>> to_underlying(const Enum value)
		{
			return static_cast<std::underlying_type_t<Enum>>(value);
		}

		bool IsWindowActive();
		HWND GetWindow();
		bool NearCursor(const SDK::FVector2D& position);
		std::string tolower(const std::string& input);
	}
}
