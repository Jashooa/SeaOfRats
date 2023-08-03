#include "General.h"

#include <Windows.h>

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
			HWND windowHandle = GetForegroundWindow();
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
			static const std::string className = "UnrealWindow";
			static const std::string windowName = "Sea of Thieves";

			HWND windowHandle = FindWindow(className.c_str(), windowName.c_str());

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
	}
}
