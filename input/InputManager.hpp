#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP
#include "tools.hpp"

class InputManager {
	public:
		static void update(bool& isGameRunning, sf::Window& window);
		static bool isKeyPressed(sf::Keyboard::Key k);
		static bool isKeyDown(sf::Keyboard::Key k);
		static bool isKeyReleased(sf::Keyboard::Key k);

		static bool isMousePressed(sf::Mouse::Button b);
		static bool isMouseDown(sf::Mouse::Button b);
		static bool isMouseReleased(sf::Mouse::Button b);

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
