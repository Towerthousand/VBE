#include <VBE/system/Keyboard.hpp>
#include <VBE/system/InputImpl.hpp>

// static
bool Keyboard::pressed(Keyboard::Key k) {
    return InputImpl::getKeyPresses()[k];
}

// static
bool Keyboard::justPressed(Keyboard::Key k) {
    return InputImpl::getKeyPresses()[k] && !oldKeyPresses[k];
}

// static
bool Keyboard::justReleased(Keyboard::Key k) {
    return !InputImpl::getKeyPresses()[k] && oldKeyPresses[k];
}

// static
void Keyboard::init() {
    for(int i = 0; i < Keyboard::KeyCount; i++)
        oldKeyPresses[i] = false;
}

// static
void Keyboard::update() {
    for(int i = 0; i < Keyboard::KeyCount; i++)
        oldKeyPresses[i] = InputImpl::getKeyPresses()[i];
}

// static
bool Keyboard::oldKeyPresses[Keyboard::KeyCount];
