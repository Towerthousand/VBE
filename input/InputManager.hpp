#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP
#include "tools.hpp"

class InputManager {
	public:
		InputManager();
		~InputManager();
		void pressKey(sf::Keyboard::Key key);
		void releaseKey(sf::Keyboard::Key key);
		void pressMouse(sf::Mouse::Button key);
		void releaseMouse(sf::Mouse::Button key);
		void moveMouse(int dx, int dy);
		void setMousePos(int x, int y);

		void gainFocus();
		void loseFocus();

		void resizeWindow(int newHeight, int newWidth, mat4f &mat);

		void update();

		std::set<sf::Keyboard::Key> keysPressed;
		std::set<sf::Keyboard::Key> keysDown;
		std::set<sf::Keyboard::Key> keysReleased;

		std::set<sf::Mouse::Button> mouseButtonsPressed;
		std::set<sf::Mouse::Button> mouseButtonsDown;
		std::set<sf::Mouse::Button> mouseButtonsReleased;

		vec2i lastMousePos;
		vec2i mouseDisplacement;

		bool focus;
};

#endif // INPUTMANAGER_HPP
