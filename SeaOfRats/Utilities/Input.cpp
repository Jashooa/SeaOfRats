#include "Input.h"

#include <Windows.h>

#include "Utilities/General.h"

namespace Utilities
{
	namespace Input
	{
		bool IsKeyPressed(int key)
		{
			if (!General::IsWindowActive())
			{
				return false;
			}

			return (GetAsyncKeyState(key) & 0x8000) != 0;
		}

		void GetNormalizedPoint(LPPOINT point)
		{
			const auto screenWidth = GetSystemMetrics(SM_CXVIRTUALSCREEN) - 1;
			const auto screenHeight = GetSystemMetrics(SM_CYVIRTUALSCREEN) - 1;
			const auto virtualLeft = GetSystemMetrics(SM_XVIRTUALSCREEN);
			const auto virtualTop = GetSystemMetrics(SM_YVIRTUALSCREEN);

			point->x -= virtualLeft;
			point->y -= virtualTop;

			// point->x = (point->x * 65535.f) / screenWidth;
			// point->y = (point->y * 65535.f) / screenHeight;
			point->x = MulDiv(point->x, 65535, screenWidth);
			point->y = MulDiv(point->y, 65535, screenHeight);
		}

		void MouseMove(int x, int y)
		{
			INPUT input{};
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_MOVE;
			input.mi.dx = x;
			input.mi.dy = y;
			input.mi.time = 0;
			input.mi.dwExtraInfo = NULL;

			SendInput(1, &input, sizeof(INPUT));
		}

		void MouseMoveTo(int x, int y)
		{
			POINT point{ x, y };
			ClientToScreen(General::GetWindow(), &point);
			GetNormalizedPoint(&point);

			INPUT input{};
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK;
			input.mi.dx = point.x;
			input.mi.dy = point.y;
			input.mi.time = 0;
			input.mi.dwExtraInfo = NULL;

			SendInput(1, &input, sizeof(INPUT));
		}

		void MouseMoveBackground(int x, int y)
		{
			/*HGLOBAL hRaw = ::GlobalAlloc(GHND, sizeof(RAWINPUT));
			if (hRaw == NULL)
			{
				return;
			}

			RAWINPUT* rawInput = reinterpret_cast<RAWINPUT*>(::GlobalLock(hRaw));
			rawInput->header.hDevice = RIM_TYPEMOUSE;
			rawInput->header.dwSize = sizeof(rawInput);
			rawInput->header.wParam = 0;
			rawInput->data.mouse.usFlags = MOUSE_MOVE_RELATIVE;
			rawInput->data.mouse.lLastX = x;
			rawInput->data.mouse.lLastY = y;
			::GlobalUnlock(hRaw);

			HWND windowHandle = General::GetWindow();
			SendMessage(windowHandle, WM_INPUT, 0, (LPARAM)hRaw);*/

			SendMessage(General::GetWindow(), WM_MOUSEMOVE, 0, MAKELPARAM(x, y));
		}

		uint32_t GetScanCode(int key)
		{
			return MapVirtualKey(key, MAPVK_VK_TO_VSC);
		}

		LPARAM GetLParam(int repeatCount, int key, int extended, int context, int previousState, int transition)
		{
			const auto scanCode = GetScanCode(key);

			const auto lParam = repeatCount
				| (scanCode << 16)
				| (extended << 24)
				| (context << 29)
				| (previousState << 30)
				| (transition << 31);

			return static_cast<LPARAM>(lParam);
		}

		void KeyPress(int key)
		{
			INPUT inputs[2] = {};
			ZeroMemory(inputs, sizeof(inputs));

			inputs[0].type = INPUT_KEYBOARD;
			inputs[0].ki.wVk = static_cast<WORD>(key);
			inputs[0].ki.wScan = GetScanCode(key) & 0xFF;

			inputs[1].type = INPUT_KEYBOARD;
			inputs[1].ki.wVk = static_cast<WORD>(key);
			inputs[1].ki.wScan = GetScanCode(key) & 0xFF;
			inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

			SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
		}

		void KeyDown(int key)
		{
			INPUT input{};
			input.type = INPUT_KEYBOARD;
			input.ki.wVk = static_cast<WORD>(key);
			input.ki.wScan = GetScanCode(key) & 0xFF;

			SendInput(1, &input, sizeof(INPUT));
		}

		void KeyUp(int key)
		{
			INPUT input{};
			input.type = INPUT_KEYBOARD;
			input.ki.wVk = static_cast<WORD>(key);
			input.ki.wScan = GetScanCode(key) & 0xFF;
			input.ki.dwFlags = KEYEVENTF_KEYUP;

			SendInput(1, &input, sizeof(INPUT));
		}

		void KeyPressBackground(int key)
		{
			const auto windowHandle = General::GetWindow();
			SendMessage(windowHandle, WM_KEYDOWN, key, GetLParam(1, key, 0, 0, 0, 0));
			SendMessage(windowHandle, WM_KEYUP, key, GetLParam(1, key, 0, 0, 1, 1));
		}

		void KeyDownBackground(int key)
		{
			const auto windowHandle = General::GetWindow();
			SendMessage(windowHandle, WM_KEYDOWN, key, GetLParam(1, key, 0, 0, 0, 0));
		}

		void KeyUpBackground(int key)
		{
			const auto windowHandle = General::GetWindow();
			SendMessage(windowHandle, WM_KEYUP, key, GetLParam(1, key, 0, 0, 1, 1));
		}
	}
}
