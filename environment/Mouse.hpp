#ifndef MOUSE_HPP
#define MOUSE_HPP
#include "tools.hpp"

class Mouse {
	public:
		enum Button {
			Left = SDL_BUTTON_LEFT,
			Middle = SDL_BUTTON_MIDDLE,
			Right = SDL_BUTTON_RIGHT,
			X1 = SDL_BUTTON_X1,
			X2 = SDL_BUTTON_X2
		};

		bool isButtonPressed(Button k) const {return (buttonsHeldOld.find(k) == buttonsHeldOld.end()) && (buttonsHeld.find(k) != buttonsHeld.end());}
		bool isButtonReleased(Button k) const {return (buttonsHeldOld.find(k) != buttonsHeldOld.end()) && (buttonsHeld.find(k) == buttonsHeld.end());}
		bool isButtonHeld(Button k) const {return (buttonsHeld.find(k) != buttonsHeld.end());}

		vec2i getMousePos() const {return mousePos;}
		vec2i getMousePosRelative() const {return mousePosRel;}

		void setMousePos(vec2i pos) { setMousePos(pos.x, pos.y); }
		void setMousePos(int x, int y);

		void hideCursor();
		void showCursor();

		void setGrab(bool grab);

	private:
		Mouse();
		friend class Environment;

		void processEvent(const SDL_Event& e);
		void update();

		Button sdlButtonToButton(int button);

		std::set<Button> buttonsHeld;
		std::set<Button> buttonsHeldOld;

		vec2i mousePos;
		vec2i mousePosRel;
};

#endif // MOUSE_HPP
