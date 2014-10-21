#include <VBE/system/Mouse.hpp>
#include <VBE/system/Log.hpp>

#include <VBE/system/InputImpl.hpp>

// static
bool Mouse::pressed(Button k) {
	InputImpl::KeyState state = InputImpl::getMouseButtonState(k);
	return state == InputImpl::Pressed || state == InputImpl::JustPressed;
}

// static
bool Mouse::justPressed(Button k) {
	InputImpl::KeyState state = InputImpl::getMouseButtonState(k);
	return state == InputImpl::JustPressed;
}

// static
bool Mouse::justReleased(Button k) {
	InputImpl::KeyState state = InputImpl::getMouseButtonState(k);
	return state == InputImpl::JustReleased;
}

// static
vec2i Mouse::position() {
	return InputImpl::getMousePosition();
}

vec2i Mouse::displacement() {
	return InputImpl::getMouseDisplacement();
}

// static
vec2i Mouse::wheelMovement() {
	return InputImpl::getMouseWheelMovement();
}

// static
void Mouse::setPosition(vec2i pos) {
	setPosition(pos.x, pos.y);
}

// static
void Mouse::setPosition(int x, int y) {
	return InputImpl::setMousePosition(x, y);
}

// static
void Mouse::setCursorVisible(bool visible) {
	InputImpl::setCursorVisible(visible);
}

// static
void Mouse::setGrab(bool grab) {
	InputImpl::setGrab(grab);
}

// static
void Mouse::setRelativeMode(bool relative) {
	InputImpl::setRelativeMouseMode(relative);
}
