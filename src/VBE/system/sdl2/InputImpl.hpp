#ifndef INPUTIMPL_HPP
#define INPUTIMPL_HPP

#include <VBE/system/Mouse.hpp>
#include <VBE/system/Keyboard.hpp>
#include <VBE/system/Gamepad.hpp>
#include <VBE/system/Touch.hpp>
#include <VBE/system/sdl2/sdl2.hpp>

class InputImpl {
    public:
        static void init();
        static void update();
        static void processEvent(const SDL_Event& e);

        static const bool* getKeyPresses();
        static const bool* getMouseButtonPresses();

        static void setMousePosition(int x, int y);

        static vec2i getMousePosition() { return mousePos; }
        static vec2i getMouseWheelPosition() { return mouseWheelPos; }

        static bool isGamepadConnected(int id);
        static float getGamepadAxis(int id, int axis);
        static bool getGamepadButtonPressed(int id, Gamepad::Button but);
        static bool getGamepadButtonJustPressed(int id, int but);
        static bool getGamepadButtonJustReleased(int id, int but);

        static void setCursorVisible(bool visible);
        static void setGrab(bool grab);
        static void setRelativeMouseMode(bool relative);

        static int getControllerIndex(SDL_JoystickID instance);

        static const std::vector<Touch::Finger>& getFingers();
    private:
        struct GamepadImpl {
                GamepadImpl();
                typedef short GamepadAxisType;

                SDL_GameController *gamepad;
                SDL_Haptic *haptic;
                SDL_JoystickID instanceId;
                bool state[Gamepad::ButtonCount];
                GamepadAxisType axis[Gamepad::AxisCount];
                bool connected;

                void open(int device);
                void close();
        };

        static GamepadImpl controllers[Gamepad::COUNT];

        static Mouse::Button convertSdlButton(int button);
        static Keyboard::Key convertSdlKey(int key);
        static Gamepad::Button convertSdlControllerButton(Uint8 button);
        static Gamepad::Axis convertSdlControllerAxis(int axis);

        static bool keyPresses[Keyboard::KeyCount];
        static bool mouseButtonPresses[Mouse::ButtonCount];
        static vec2i mousePos;
        static vec2i mouseWheelPos;
        static bool relativeMouse;

        static std::vector<Touch::Finger> fingers;
};

#endif // INPUTIMPL_HPP
