#ifndef TOUCH_HPP
#define TOUCH_HPP

#include <VBE/math.hpp>
#include <vector>

class InputImpl;

///
/// \brief The Touch class provides support to read touch and multi-touch screens
///
class Touch {
    public:
        ///
        /// \brief The Finger class represents one of the user's fingers
        ///
        class Finger {
            public:
                ///
                /// \brief Returns the ID of this finger
                ///
                int getId() const;
                ///
                /// \brief Returns whether this finger just made contact with the display in this frame
                ///
                bool justPressed() const;
                ///
                /// \brief Returns the current position of the finger in normalized (0..1) coordinates
                ///
                vec2f position() const;
                ///
                /// \brief Returns the movement relative to the last frame
                ///
                vec2f movement() const;

            private:
                int id;
                vec2f pos;
                vec2f oldPos;
                bool isNew;

                friend class Touch;
                friend class InputImpl;
        };
        ///
        /// \class Finger Window.hpp <VBE/system/Touch.hpp>
        /// \ingroup System
        ///
        /// Each user finger is tracked from the moment of contact until release, and it will
        /// maintain the same ID throughout the whole gesture.
        ///
        /// \see Touch
        ///

        ///
        /// \brief Returns all the tracked fingers
        ///
        static const std::vector<Finger>& getFingers();
};
/// \class Touch Touch.hpp <VBE/system/Touch.hpp>
/// \ingroup System
///
///  The total number of fingers is only limited by the actual device.
///

#endif
