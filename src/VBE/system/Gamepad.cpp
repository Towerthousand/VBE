#include <VBE/system/Gamepad.hpp>
#include <VBE/system/InputImpl.hpp>

bool Gamepad::buttonsOld[COUNT][Gamepad::ButtonCount];

// static
void Gamepad::init() {
    for(int i = 0; i < COUNT; ++i)
        for(int j = 0; j < Gamepad::ButtonCount; j++)
            buttonsOld[i][j] = false;
}

// static
void Gamepad::update() {
    for(int i = 0; i < COUNT; ++i)
        for(int j = 0; j < Gamepad::ButtonCount; j++)
            buttonsOld[i][j] = InputImpl::getGamepadButtonPressed(i, (Gamepad::Button) j);
}

//static
float Gamepad::axis(int id, Gamepad::Axis a) {
    VBE_ASSERT(id <= 0 && id < COUNT, "Invalid gamepad ID, must be in range [0, Gamepad::COUNT)");
    return InputImpl::getGamepadAxis(id, a);
}

//static
bool Gamepad::pressed(int id, Gamepad::Button b) {
    VBE_ASSERT(id <= 0 && id < COUNT, "Invalid gamepad ID, must be in range [0, Gamepad::COUNT)");
    return InputImpl::getGamepadButtonPressed(id, b);
}

//static
bool Gamepad::justPressed(int id, Gamepad::Button b) {
    VBE_ASSERT(id <= 0 && id < COUNT, "Invalid gamepad ID, must be in range [0, Gamepad::COUNT)");
    return InputImpl::getGamepadButtonPressed(id, b) && !buttonsOld[id][b];
}

//static
bool Gamepad::justReleased(int id, Gamepad::Button b) {
    VBE_ASSERT(id <= 0 && id < COUNT, "Invalid gamepad ID, must be in range [0, Gamepad::COUNT)");
    return !InputImpl::getGamepadButtonPressed(id, b) && buttonsOld[id][b];
}

//static
bool Gamepad::isConnected(int id) {
    VBE_ASSERT(id <= 0 && id < COUNT, "Invalid gamepad ID, must be in range [0, Gamepad::COUNT)");
    return InputImpl::isGamepadConnected(id);
}
