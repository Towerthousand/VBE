#include "Input.hpp"

std::set<sf::Keyboard::Key> Input::keysPressed;
std::set<sf::Keyboard::Key> Input::keysDown;
std::set<sf::Keyboard::Key> Input::keysReleased;

std::set<sf::Mouse::Button> Input::mouseButtonsPressed;
std::set<sf::Mouse::Button> Input::mouseButtonsDown;
std::set<sf::Mouse::Button> Input::mouseButtonsReleased;

bool Input::focus(true);
vec2i Input::lastMousePos(0, 0);
vec2i Input::mouseDisplacement(0, 0);

Input::Input() {
}

Input::~Input() {
}

void Input::update(bool &isGameRunning, sf::Window &window) {
	keysPressed = std::set<sf::Keyboard::Key>();
	keysReleased = std::set<sf::Keyboard::Key>();
	mouseButtonsPressed = std::set<sf::Mouse::Button>();
	mouseButtonsReleased = std::set<sf::Mouse::Button>();
	lastMousePos += mouseDisplacement;
	mouseDisplacement = vec2i(0, 0);
	sf::Event event;
	while(window.pollEvent(event)) {
		switch(event.type) {
			case sf::Event::Closed:
				isGameRunning = false;
				break;
			case sf::Event::Resized:
				SCRWIDTH = event.size.width;
				SCRHEIGHT = event.size.height;
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
				mouseDisplacement = vec2i(event.mouseMove.x, event.mouseMove.y) - lastMousePos;
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

void Input::setMousePos(int x, int y, sf::Window& window) {
	sf::Mouse::setPosition(sf::Vector2i(x, y), window);
	lastMousePos = vec2i(x, y);
	mouseDisplacement = vec2i(0, 0);
}
