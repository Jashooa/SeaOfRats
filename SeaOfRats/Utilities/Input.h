#pragma once

namespace Utilities
{
	namespace Input
	{
		bool IsKeyPressed(int key);
		void MouseMove(int x, int y);
		void MouseMoveTo(int x, int y);
		void KeyPress(int key);
		void KeyUp(int key);
		void KeyDown(int key);
		void KeyPressBackground(int key);
		void KeyUpBackground(int key);
		void KeyDownBackground(int key);
	}
}