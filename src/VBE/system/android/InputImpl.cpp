#include <VBE/system/android/InputImpl.hpp>
#include <VBE/system/android/WindowImpl.hpp>
#include <VBE/system/Log.hpp>

// static
bool InputImpl::keyPresses[Keyboard::KeyCount];
bool InputImpl::mouseButtonPresses[Mouse::ButtonCount];
vec2i InputImpl::mousePos;
vec2i InputImpl::mouseWheelPos;
bool InputImpl::relativeMouse;

// static
void InputImpl::init() {
    mousePos = vec2i(0, 0);
    mouseWheelPos = vec2i(0, 0);
    relativeMouse = false;

    for(int i = 0; i < Keyboard::KeyCount; i++)
        keyPresses[i] = false;
    for(int i = 0; i < Mouse::ButtonCount; i++)
        mouseButtonPresses[i] = false;
}

// static
const bool* InputImpl::getKeyPresses() {
    return keyPresses;
}

// static
const bool* InputImpl::getMouseButtonPresses() {
    return mouseButtonPresses;
}

void InputImpl::setMousePosition(int x, int y) {
    // There's no way to move the mouse in Android
}

void InputImpl::setCursorVisible(bool visible) {
    // TODO
}

void InputImpl::setGrab(bool grab) {
    // Not applicable in Android
}

void InputImpl::setRelativeMouseMode(bool relative) {
    // TODO
    relativeMouse = relative;
}

