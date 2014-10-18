#ifndef INPUTIMPL_HPP
#define INPUTIMPL_HPP

#include <VBE/system/Mouse.hpp>
#include <VBE/system/Keyboard.hpp>

#include <SDL2/SDL.h>


class InputImpl {
	public:
		static void init();
		static void update();
		static void processEvent(const SDL_Event& e);


		enum KeyState {
			Released,
			JustPressed,
			Pressed,
			JustReleased
		};

		static KeyState getKeyState(Keyboard::Key key);
		static KeyState getMouseButtonState(Mouse::Button button);

		static void setMousePosition(int x, int y);

		static vec2i getMousePosition() { return mousePos; }
		static vec2i getMouseWheelMovement() { return mouseWheel; }

		static void setCursorVisible(bool visible);
		static void setGrab(bool grab);
		static void setRelativeMouseMode(bool relative);

	private:
		static Mouse::Button convertSdlButton(int button);
		static Keyboard::Key convertSdlKey(int key);
		static KeyState nextState(KeyState state);

		static KeyState keyboardState[Keyboard::KeyCount];
		static KeyState mouseButtonState[Mouse::ButtonCount];
		static vec2i mousePos;
		static vec2i mouseWheel;
		static bool relativeMouse;
};

#endif // INPUTIMPL_HPP
