#include "InputManager.hpp"

InputManager::InputManager() :
	lastMousePos(0,0), mouseDisplacement(0,0), focus(true) {
}

InputManager::~InputManager() {
}

void InputManager::update() {
	keysPressed = std::set<sf::Keyboard::Key>();
	keysReleased = std::set<sf::Keyboard::Key>();
	mouseButtonsPressed = std::set<sf::Mouse::Button>();
	mouseButtonsReleased = std::set<sf::Mouse::Button>();
	lastMousePos += mouseDisplacement;
	mouseDisplacement = vec2i(0,0);
}

void InputManager::pressKey(sf::Keyboard::Key key) {
	keysPressed.insert(key);
	keysDown.insert(key);
}

void InputManager::releaseKey(sf::Keyboard::Key key) {
	keysReleased.insert(key);
	keysDown.erase(key);
}

void InputManager::pressMouse(sf::Mouse::Button key) {
	mouseButtonsPressed.insert(key);
	mouseButtonsDown.insert(key);
}

void InputManager::releaseMouse(sf::Mouse::Button key) {
	mouseButtonsReleased.insert(key);
	mouseButtonsDown.erase(key);
}

void InputManager::gainFocus() {
	focus = true;
}

void InputManager::loseFocus() {
	focus = false;
}

void InputManager::moveMouse(int dx, int dy) {
	mouseDisplacement = vec2i(dx,dy) - lastMousePos;
}

void InputManager::setMousePos(int x, int y) {
	lastMousePos = vec2i(x,y);
	mouseDisplacement = vec2i(0,0);
}

void InputManager::resizeWindow(int newHeight, int newWidth, mat4f& mat) {
	SCRWIDTH = newWidth;
	SCRHEIGHT = newHeight;
	glViewport(0, 0, SCRWIDTH, SCRHEIGHT);
	mat = glm::perspective(FOV,float(SCRWIDTH)/float(SCRHEIGHT), ZNEAR, ZFAR);
}
