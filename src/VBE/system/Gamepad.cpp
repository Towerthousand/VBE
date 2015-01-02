#include <VBE/system/Gamepad.hpp>
#include <VBE/system/InputImpl.hpp>

float Gamepad::axis(int id, Gamepad::Axis a) {
	return InputImpl::getGamepadAxis(id, a);
}

bool Gamepad::pressed(int id, Gamepad::Button b) {
	return InputImpl::getGamepadButtonPressed(id, b);
}

bool Gamepad::justPressed(int id, Gamepad::Button b) {
	return InputImpl::getGamepadButtonJustPressed(id, b);
}

bool Gamepad::justReleased(int id, Gamepad::Button b) {
	return InputImpl::getGamepadButtonJustReleased(id, b);
}

bool Gamepad::isConnected(int id) {
	return InputImpl::isGamepadConnected(id);
}
