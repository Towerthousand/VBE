#include "InputManager.hpp"

std::set<sf::Keyboard::Key> InputManager::keysPressed;
std::set<sf::Keyboard::Key> InputManager::keysDown;
std::set<sf::Keyboard::Key> InputManager::keysReleased;

std::set<sf::Mouse::Button> InputManager::mouseButtonsPressed;
std::set<sf::Mouse::Button> InputManager::mouseButtonsDown;
std::set<sf::Mouse::Button> InputManager::mouseButtonsReleased;

bool InputManager::focus(true);
vec2i InputManager::lastMousePos(0,0);
vec2i InputManager::mouseDisplacement(0,0);

InputManager::InputManager() {
}

InputManager::~InputManager() {
}

void InputManager::update(bool &isGameRunning,sf::Window &window) {
	keysPressed = std::set<sf::Keyboard::Key>();
	keysReleased = std::set<sf::Keyboard::Key>();
	mouseButtonsPressed = std::set<sf::Mouse::Button>();
	mouseButtonsReleased = std::set<sf::Mouse::Button>();
	lastMousePos += mouseDisplacement;
	mouseDisplacement = vec2i(0,0);
	sf::Event event;
	while(window.pollEvent(event)) {
		switch(event.type) {
			case sf::Event::Closed:
				isGameRunning = false;
				break;
			case sf::Event::Resized:
				SCRWIDTH = event.size.width;
				SCRHEIGHT = event.size.height;
				glViewport(0, 0, SCRWIDTH, SCRHEIGHT);
				break;
			case sf::Event::GainedFocus:
				focus = true;
				break;
			case sf::Event::LostFocus:
				focus = false;
				break;
			case sf::Event::MouseButtonPressed:
				mouseButtonsPressed.insert(event.mouseButton.button);
				mouseButtonsDown.insert(event.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:
				mouseButtonsReleased.insert(event.mouseButton.button);
				mouseButtonsDown.erase(event.mouseButton.button);
				break;
			case sf::Event::MouseMoved:
				mouseDisplacement = vec2i(event.mouseMove.x,event.mouseMove.y) - lastMousePos;
				break;
			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape)
					isGameRunning = false;
				keysPressed.insert(event.key.code);
				keysDown.insert(event.key.code);
				break;
			case sf::Event::KeyReleased:
				keysReleased.insert(event.key.code);
				keysDown.erase(event.key.code);
				break;
			default:
				break;
		}
	}
}

void InputManager::setMousePos(int x, int y, sf::Window& window) {
	sf::Mouse::setPosition(sf::Vector2i(x,y),window);
	lastMousePos = vec2i(x,y);
	mouseDisplacement = vec2i(0,0);
}
