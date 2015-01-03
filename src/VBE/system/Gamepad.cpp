#include <VBE/system/Gamepad.hpp>
#include <VBE/system/InputImpl.hpp>

//static
float Gamepad::axis(int id, Gamepad::Axis a) {
	return InputImpl::getGamepadAxis(id, a);
}

//static
bool Gamepad::pressed(int id, Gamepad::Button b) {
	return InputImpl::getGamepadButtonPressed(id, b);
}

//static
bool Gamepad::justPressed(int id, Gamepad::Button b) {
	return InputImpl::getGamepadButtonJustPressed(id, b);
}

//static
bool Gamepad::justReleased(int id, Gamepad::Button b) {
	return InputImpl::getGamepadButtonJustReleased(id, b);
}

//static
bool Gamepad::isConnected(int id) {
	return InputImpl::isGamepadConnected(id);
}
