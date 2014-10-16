#ifndef MOUSE_HPP
#define MOUSE_HPP

class Mouse {
	public:
		enum Button {
			Left,
			Middle,
			Right,
			X1,
			X2
		};

		static bool justPressed(Button k);
		static bool justReleased(Button k);
		static bool pressed(Button k);

		static vec2i position();
		static vec2i mouseWheelMovement();

		static void setPosition(vec2i pos);
		static void setPosition(int x, int y);

		static void hideCursor();
		static void showCursor();

		static void setGrab(bool grab);
		static void setRelativeMode(bool relative);

	private:
		Mouse();
		~Mouse();
};

#endif // MOUSE_HPP
