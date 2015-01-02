#include <VBE/system/Gamepad.hpp>
#include <VBE/system/InputImpl.hpp>


float Gamepad::axis(Gamepad::Axis a)
{
	return InputImpl::getGamepadAxis(id, a);
}

bool Gamepad::pressed(Gamepad::Button b)
{
	return InputImpl::getGamepadButtonPressed(id, b);
}

bool Gamepad::justPressed(Gamepad::Button b)
{
	return InputImpl::getGamepadButtonJustPressed(id, b);
}

bool Gamepad::justReleased(Gamepad::Button b)
{
	return InputImpl::getGamepadButtonJustReleased(id, b);
}

bool Gamepad::isConnected()
{
	return InputImpl::isGamepadConnected(id);
}

Gamepad Gamepad::getGamepad(int id)
{
	return Gamepad(id);
}

Gamepad::Gamepad(int id) : id(id)
{

}
