#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

///
/// \brief The Keyboard class provides support to read the keyboard.
///
class Keyboard {
    public:
        ///
        /// \brief Contains all supported keys.
        ///
        enum Key {
            Num0,
            Num1,
            Num2,
            Num3,
            Num4,
            Num5,
            Num6,
            Num7,
            Num8,
            Num9,
            A,
            AC_BACK,
            AC_BOOKMARKS,
            AC_FORWARD,
            AC_HOME,
            AC_REFRESH,
            AC_SEARCH,
            AC_STOP,
            Again,
            AltErase,
            Quote,
            Application,
            AudioMute,
            AudioNext,
            AudioPlay,
            AudioPrev,
            AuidoStop,
            B,
            Backslash,
            Backspace,
            BrightnessDown,
            BrightnessUp,
            C,
            Calculator,
            Cancel,
            Capslock,
            Clear,
            ClearAgain,
            Comma,
            Computer,
            Copy,
            CrSel,
            CurrencySubUnit,
            CurrencyUnit,
            Cut,
            D,
            DecimalSeparator,
            Delete,
            DisplaySwitch,
            Down,
            E,
            Eject,
            End,
            Equals,
            Escape,
            Execute,
            Exsel,
            F,
            F1,
            F10,
            F11,
            F12,
            F13,
            F14,
            F15,
            F16,
            F17,
            F18,
            F19,
            F2,
            F20,
            F21,
            F22,
            F23,
            F24,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            Find,
            G,
            BackQuote,
            H,
            Help,
            Home,
            I,
            Insert,
            J,
            K,
            KBDIllumDown,
            KBDIllumToggle,
            KBDIllumUp,
            Keypad0,
            Keypad00,
            Keypad000,
            Keypad1,
            Keypad2,
            Keypad3,
            Keypad4,
            Keypad5,
            Keypad6,
            Keypad7,
            Keypad8,
            Keypad9,
            KeypadA,
            KeypadAmpersand,
            KeypadAt,
            KeypadB,
            KeypadBackspace,
            KeypadBinary,
            KeypadC,
            KeypadClear,
            KeypadClearEntry,
            KeypadColon,
            KeypadComma,
            KeypadD,
            KeypadDoubleAmpersand,
            KeypadDoubleVerticalBar,
            KeypadDecimal,
            KeypadDivide,
            KeypadE,
            KeypadEnter,
            KeypadEquals,
            KeypadEqualsAS400,
            KeypadExclamation,
            KeypadF,
            KeypadGreater,
            KeypadHash,
            KeypadHexadecimal,
            KeypadLBrace,
            KeypadLParenthesis,
            KeypadLess,
            KeypadMemAdd,
            KeypadMemClear,
            KeypadMemDivide,
            KeypadMemMultiply,
            KeypadMemRecall,
            KeypadMemStore,
            KeypadMemSubstract,
            KeypadMinus,
            KeypadMultiply,
            KeypadOctal,
            KeypadPercent,
            KeypadPeriod,
            KeypadPlus,
            KeypadPlusMinus,
            KeypadPower,
            KeypadRBrace,
            KeypadRParenthesis,
            KeypadSpace,
            KeypadTab,
            KeypadVerticalBar,
            KeypadXor,
            L,
            LAlt,
            LControl,
            Left,
            LBracket,
            LGUI,
            LShift,
            M,
            Mail,
            MediaSelect,
            Menu,
            Minus,
            Mode,
            Mute,
            N,
            NumLockClear,
            O,
            Oper,
            Out,
            P,
            PageDown,
            PageUp,
            Paste,
            Pause,
            Period,
            Power,
            PrintScren,
            Prior,
            Q,
            R,
            RAlt,
            RControl,
            Return,
            Return2,
            RGUI,
            Right,
            RBracket,
            RShift,
            S,
            ScrollLock,
            Select,
            Semicolont,
            Separator,
            Slash,
            Sleep,
            Space,
            Stop,
            Sysreq,
            T,
            Tab,
            ThousandsSeparator,
            U,
            Undo,
            Unknown,
            UP,
            V,
            VolumeDown,
            VolumeUp,
            W,
            WWW,
            X,
            Y,
            Z,
            Ampersand,
            Asterisk,
            At,
            Caret,
            Colon,
            Dollar,
            Exclamation,
            Greater,
            Hash,
            LParenthesis,
            Less,
            Percent,
            Plus,
            Question,
            DoubleQuote,
            RParenthesis,
            Underscore,
            KeyCount ///< Not an actual key
        };

        ///
        /// \brief Tells whether the given key is pressed (held down)
        ///
        static bool pressed(Key k);

        ///
        /// \brief Tells whether the given key has just been pressed (It was not pressed on the last frame and now it is.)
        ///
        static bool justPressed(Key k);

        ///
        /// \brief Tells whether the given key has just been released (It was pressed on the last frame and it's now released.)
        ///
        static bool justReleased(Key k);


    private:
        static void init();
        static void update();
        static bool oldKeyPresses[Keyboard::KeyCount];

        friend class Window;
};

///
/// \class Keyboard Keyboard.hpp <VBE/system/Keyboard.hpp>
/// \ingroup System
///
/// You can use this class within an init environment (one that has a window) to access the current
/// keyboard device's state. Not all keys are supported in all devices and may
/// never be marked as pressed (depends on the driver). The state of this device will be updated to
/// match recieved events whenever Window::update() is called.
///
/// A Key will be 'just pressed' for only one frame (one update()) call. Then held for
/// an indefinite number of frames and released right after. For Example, if the
/// user pressed the A Key on frame 1 and released it on frame 4, this would
/// register (updating the window every frame of course):
///
/// - Frame 1
///   + Key Keyboard::A is just pressed
///   + Key Keyboard::A is pressed
///   + Key Keyboard::A is not just released
/// - Frame 2
///   + Key Keyboard::A is not just pressed
///   + Key Keyboard::A is pressed
///   + Key Keyboard::A is not just released
/// - Frame 3
///   + Key Keyboard::A is not just pressed
///   + Key Keyboard::A is pressed
///   + Key Keyboard::A is not just released
/// - Frame 4
///   + Key Keyboard::A is not just pressed
///   + Key Keyboard::A is not pressed
///   + Key Keyboard::A is just released
///

#endif // KEYBOARD_HPP
