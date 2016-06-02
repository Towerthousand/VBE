#include <VBE/system/Mouse.hpp>
#include <VBE/system/Log.hpp>

#include <VBE/system/InputImpl.hpp>

// static
bool Mouse::pressed(Button k) {
    return InputImpl::getMouseButtonPresses()[k];
}

// static
bool Mouse::justPressed(Button k) {
    return InputImpl::getMouseButtonPresses()[k] && !oldMouseButtonPresses[k];
}

// static
bool Mouse::justReleased(Button k) {
    return !InputImpl::getMouseButtonPresses()[k] && oldMouseButtonPresses[k];
}

// static
vec2i Mouse::position() {
    return InputImpl::getMousePosition();
}

vec2i Mouse::movement() {
    return InputImpl::getMousePosition() - oldMousePos;
}

// static
vec2i Mouse::wheelPosition() {
    return InputImpl::getMouseWheelPosition();
}

// static
vec2i Mouse::wheelMovement() {
    return InputImpl::getMouseWheelPosition() - oldMouseWheelPos;
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

// static
void Mouse::init() {
    for(int i = 0; i < Button::ButtonCount; i++)
        oldMouseButtonPresses[i] = false;

    oldMousePos = vec2i(0, 0);
    oldMouseWheelPos = vec2i(0, 0);
}

// static
void Mouse::update() {
    for(int i = 0; i < Button::ButtonCount; i++)
        oldMouseButtonPresses[i] = InputImpl::getMouseButtonPresses()[i];

    oldMousePos = InputImpl::getMousePosition();
    oldMouseWheelPos = InputImpl::getMouseWheelPosition();
}

// static
bool Mouse::oldMouseButtonPresses[Mouse::ButtonCount];
// static
vec2i Mouse::oldMousePos = vec2i(0.0f);
// static
vec2i Mouse::oldMouseWheelPos = vec2i(0.0f);

