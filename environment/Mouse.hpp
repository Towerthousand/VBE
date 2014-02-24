#ifndef MOUSE_HPP
#define MOUSE_HPP
#include "tools.hpp"

class Mouse {
	public:
		Mouse();

		enum Button {
			Left = 0,
			Middle,
			Right,
			X1,
			X2,
			_BUTTON_SIZE
		};

		bool isButtonPressed(Button b) const {return !buttonsHeldOld[b] && buttonsHeld[b];}
		bool isButtonReleased(Button b) const {return buttonsHeldOld[b] && !buttonsHeld[b];}
		bool isButtonHeld(Button b) const {return buttonsHeld[b];}

		vec2i getMousePos() const {return mousePos;}
		vec2i getMousePosRelative() const {return mousePosRel;}

		void setMousePos(vec2i pos) { setMousePos(pos.x, pos.y); }
		void setMousePos(int x, int y);

		void hideCursor();
		void showCursor();

		void setGrab(bool grab);

	private:
		friend class Environment;

		void processEvent(const SDL_Event& e);
		void update();

		Button sdlButtonToButton(int button);

		bool buttonsHeld[_BUTTON_SIZE];
		bool buttonsHeldOld[_BUTTON_SIZE];

		vec2i mousePos;
		vec2i mousePosRel;
};

#endif // MOUSE_HPP
