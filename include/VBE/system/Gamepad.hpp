#ifndef GAMEPAD_HPP
#define GAMEPAD_HPP

///
/// \brief The Gamepad provides multiple game gamepad support
///
class Gamepad {
    public:
        ///
        /// \brief Represents the maximum number of concurrent gamepads
        ///
        static constexpr int COUNT = 4;

        ///
        /// \brief All the supported gamepad axis
        ///
        enum Axis {
            AxisInvalid = -1,
            AxisLeftX,
            AxisLeftY,
            AxisRightX,
            AxisRightY,
            AxisTriggerLeft,
            AxisTriggerRight,
            AxisCount
        };

        ///
        /// \brief All the supported gamepad buttons
        ///
        enum Button {
            ButtonInvalid = -1,
            ButtonA,
            ButtonB,
            ButtonX,
            ButtonY,
            ButtonBack,
            ButtonGuide,
            ButtonStart,
            ButtonLeftStick,
            ButtonRightStick,
            ButtonLeftShoulder,
            ButtonRightShoulder,
            ButtonDUp,
            ButtonDDown,
            ButtonDLeft,
            ButtonDRight,
            ButtonCount
        };

        ///
        /// \brief Returns the state of an axis
        /// \param id The ID of the gamepad, must be between 0 and COUNT-1
        /// \param a the axis being queried
        /// \return A floating point number in [-1.0, 1.0]
        ///
        static float axis(int id, Axis a);

        ///
        /// \brief Returns whether a button is pressed
        /// \param id The ID of the gamepad, must be between 0 and COUNT-1
        /// \param b the button being queried
        /// \return Whether or not this button was pressed or not during this frame
        ///
        static bool pressed(int id, Button b);

        ///
        /// \brief Returns whether a button is just pressed
        /// \param id The ID of the gamepad, must be between 0 and COUNT-1
        /// \param b the button being queried
        /// \return Whether or not this button was just pressed or not during this frame
        ///
        static bool justPressed(int id, Button b);

        ///
        /// \brief Returns whether a button is just released
        /// \param id The ID of the gamepad, must be between 0 and COUNT-1
        /// \param b the button being queried
        /// \return Whether or not this button was just released or not during this frame
        ///
        static bool justReleased(int id, Button b);

        ///
        /// \brief Returns whether there is a gamepad connected at the fiven port ID.
        /// If only 1 gamepad is connected, then isConnected(3) will return false.
        /// \param id The port being queried
        /// \return Whether a gamepad is connected or not at the given port
        ///
        static bool isConnected(int id);

    private:
        static void init();
        static void update();

        static bool buttonsOld[COUNT][ButtonCount];

        friend class Window;
};
///
/// \class Gamepad Gamepad.hpp <VBE/system/Gamepad.hpp>
/// \ingroup System
///
/// This class will show no input (the states won't change) on mobile devices.
///

#endif // GAMEPAD_HPP
