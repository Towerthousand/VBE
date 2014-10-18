#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <VBE/math.hpp>

class Mouse {
	public:
		enum Button {
			Left,
			Middle,
			Right,
			X1,
			X2,
			ButtonCount
		};

		static bool pressed(Button k);
		static bool justPressed(Button k);
		static bool justReleased(Button k);

		static vec2i position();
		static vec2i wheelMovement();

		static void setPosition(vec2i pos);
		static void setPosition(int x, int y);

		static void setCursorVisible(bool visible);
		static void setGrab(bool grab);
		static void setRelativeMode(bool relative);

	private:
		Mouse();
		~Mouse();
};

#endif // MOUSE_HPP
