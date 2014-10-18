#include <VBE/system/Keyboard.hpp>
#include <VBE/system/InputImpl.hpp>

// static
bool Keyboard::pressed(Keyboard::Key k) {
	InputImpl::KeyState state = InputImpl::getKeyState(k);
	return state == InputImpl::Pressed || state == InputImpl::JustPressed;
}

// static
bool Keyboard::justPressed(Keyboard::Key k) {
	InputImpl::KeyState state = InputImpl::getKeyState(k);
	return state == InputImpl::JustPressed;
}

// static
bool Keyboard::justReleased(Keyboard::Key k) {
	InputImpl::KeyState state = InputImpl::getKeyState(k);
	return state == InputImpl::JustReleased;
}
