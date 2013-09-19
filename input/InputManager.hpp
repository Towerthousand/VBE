#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP
#include "tools.hpp"

class InputManager {
	public:
		static void update(bool& isGameRunning, sf::Window &window);
		static bool isKeyPressed(sf::Keyboard::Key k) {return (keysPressed.find(k) != keysPressed.end());}
		static bool isKeyDown(sf::Keyboard::Key k) {return (keysDown.find(k) != keysDown.end());}
		static bool isKeyReleased(sf::Keyboard::Key k) {return (keysReleased.find(k) != keysReleased.end());}

		static bool isMousePressed(sf::Mouse::Button b) {return (mouseButtonsPressed.find(b) != mouseButtonsPressed.end());}
		static bool isMouseDown(sf::Mouse::Button b) {return (mouseButtonsDown.find(b) != mouseButtonsDown.end());}
		static bool isMouseReleased(sf::Mouse::Button b) {return (mouseButtonsReleased.find(b) != mouseButtonsReleased.end());}

		static vec2i getMousePos() {return lastMousePos;}
		static vec2i getMouseDisplacement() {return mouseDisplacement;}

		static void setMousePos(int x, int y, sf::Window &Window);

		static std::set<sf::Keyboard::Key> keysPressed;
		static std::set<sf::Keyboard::Key> keysDown;
		static std::set<sf::Keyboard::Key> keysReleased;

		static std::set<sf::Mouse::Button> mouseButtonsPressed;
		static std::set<sf::Mouse::Button> mouseButtonsDown;
		static std::set<sf::Mouse::Button> mouseButtonsReleased;

	private:
		static bool focus;
		static vec2i lastMousePos;
		static vec2i mouseDisplacement;
		InputManager();
		~InputManager();
};

#endif // INPUTMANAGER_HPP
