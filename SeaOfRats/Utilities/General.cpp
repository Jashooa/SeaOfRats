#include "General.h"

#include <Windows.h>

#include <algorithm>
#include <cctype>
#include <string>

#include "Utilities/Drawing.h"
#include "Utilities/Input.h"
#include "Utilities/Math.h"

using namespace SDK;

namespace Utilities
{
	namespace General
	{
		bool IsWindowActive()
		{
			const auto windowHandle = GetForegroundWindow();
			if (windowHandle == NULL)
			{
				return false;
			}

			DWORD foregroundProcessId{};
			if (GetWindowThreadProcessId(windowHandle, &foregroundProcessId) == 0)
			{
				return false;
			}

			return foregroundProcessId == GetCurrentProcessId();
		}

		HWND GetWindow()
		{
			static const auto className = "UnrealWindow";
			static const auto windowName = "Sea of Thieves";

			HWND windowHandle = FindWindow(className, windowName);

			DWORD windowProcessId{};
			GetWindowThreadProcessId(windowHandle, &windowProcessId);

			if (windowProcessId == GetCurrentProcessId())
			{
				return windowHandle;
			}

			return NULL;
		}

		bool NearCursor(const FVector2D& position)
		{
			return Math::PointInCircle(position, Drawing::GetScreenCentre(), 32.f) || Utilities::Input::IsKeyPressed('R');
		}

		std::string tolower(const std::string& input)
		{
			std::string result = input;
			std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return static_cast<unsigned char>(std::tolower(static_cast<int>(c))); });
			return result;
		}
	}
}
