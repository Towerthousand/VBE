#ifndef INPUTIMPL_HPP
#define INPUTIMPL_HPP

#include <VBE/system/Mouse.hpp>
#include <VBE/system/Keyboard.hpp>

class InputImpl {
    public:
        static void init();
        //		static void processEvent(const SDL_Event& e);

        static const bool* getKeyPresses();
        static const bool* getMouseButtonPresses();

        static void setMousePosition(int x, int y);

        static vec2i getMousePosition() { return mousePos; }
        static vec2i getMouseWheelPosition() { return mouseWheelPos; }

        static void setCursorVisible(bool visible);
        static void setGrab(bool grab);
        static void setRelativeMouseMode(bool relative);

    private:
        static bool keyPresses[Keyboard::KeyCount];
        static bool mouseButtonPresses[Mouse::ButtonCount];
        static vec2i mousePos;
        static vec2i mouseWheelPos;
        static bool relativeMouse;
};

#endif // INPUTIMPL_HPP
