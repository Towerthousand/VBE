#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <VBE/math.hpp>

///
/// \brief The Mouse class provides support to read the mouse device.
///
class Mouse {
    public:
        ///
        /// \brief The Button enum contains all supported mouse buttons
        ///
        enum Button {
            Left,
            Middle,
            Right,
            X1,
            X2,
            ButtonCount ///< Not an actual button
        };

        ///
        /// \brief Tells whether the given mouse button is pressed (held down)
        ///
        static bool pressed(Button k);

        ///
        /// \brief Tells whether the given mouse button has just been pressed (It was not pressed on the last frame and now it is.)
        ///
        static bool justPressed(Button k);

        ///
        /// \brief Tells whether the given mouse button has just been released (It was pressed on the last frame and it's now released.)
        ///
        static bool justReleased(Button k);

        ///
        /// \brief Get mouse position.
        /// In absolute mode, the position will be an absolute pixel position to the window.
        /// In relative mode, the position is not relative to the window, but to the last
        /// frame's position. See setRelativeMode for details.
        /// \return the mouse position.
        ///
        static vec2i position();

        ///
        /// \brief Get mouse movement since last frame.
        /// \return the mouse movement.
        ///
        static vec2i movement();

        ///
        /// \brief Gets the mouse wheel position. Mouse wheel ticks are accumulated
        /// in this value, similar to the relative mouse mode.
        /// \return the mouse wheel position.
        ///
        static vec2i wheelPosition();

        ///
        /// \brief Gets the mouse wheel movement since last frame.
        /// \return the mouse wheel movement.
        ///
        static vec2i wheelMovement();

        ///
        /// \brief Sets the mouse position relative to the game window.
        /// \param pos New position in pixels.
        ///
        static void setPosition(vec2i pos);

        ///
        /// \brief Sets the mouse position relative to the game window.
        /// \param x New X position in pixels.
        /// \param y New Y position in pixels.
        ///
        static void setPosition(int x, int y);

        ///
        /// \brief Shows or hides the mouse cursor.
        /// \param visible Whether to make the cursor visible or not.
        ///
        static void setCursorVisible(bool visible);

        ///
        /// \brief Enables or disables mouse grab. If mouse grab is enabled,
        /// the mouse will never move out of the game window.
        /// \param grab whether to enable or disable mosue grab.
        ///
        static void setGrab(bool grab);

        ///
        /// \brief Enable or disable mouse relative mode. In relative mode,
        /// when the mouse moves against the edge of the window or the screen, its position will
        /// continue to change as if it went past it. It's useful for games like FPS's, where
        /// all you care about is the relative position with respect to the last frame, and
        /// you don't want the movement to stop if the mouse hits the edge of the screen.
        /// \param relative whether to enable or disable relative mode.
        ///
        static void setRelativeMode(bool relative);


    private:
        static void init();
        static void update();
        static bool oldMouseButtonPresses[Mouse::ButtonCount];
        static vec2i oldMousePos;
        static vec2i oldMouseWheelPos;

        friend class Window;
};
///
/// \class Mouse Mouse.hpp <VBE/system/Mouse.hpp>
/// \ingroup System
///
/// This class will show no input (the states won't change) on mobile devices.
///

#endif // MOUSE_HPP
