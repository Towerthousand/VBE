#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP
#include "tools.hpp"

///
/// @brief Provides interface for a keyboard device
///
class Keyboard {
	public:
		///
		/// \brief Contains all supported keys
		///
		enum Key {
			Num0 = SDLK_0,
			Num1 = SDLK_1,
			Num2 = SDLK_2,
			Num3 = SDLK_3,
			Num4 = SDLK_4,
			Num5 = SDLK_5,
			Num6 = SDLK_6,
			Num7 = SDLK_7,
			Num8 = SDLK_8,
			Num9 = SDLK_9,
			A = SDLK_a,
			AC_BACK = SDLK_AC_BACK,
			AC_BOOKMARKS = SDLK_AC_BOOKMARKS,
			AC_FORWARD = SDLK_AC_FORWARD,
			AC_HOME = SDLK_AC_HOME,
			AC_REFRESH = SDLK_AC_REFRESH,
			AC_SEARCH = SDLK_AC_SEARCH,
			AC_STOP = SDLK_AC_STOP,
			Again = SDLK_AGAIN,
			AltErase = SDLK_ALTERASE,
			Quote = SDLK_QUOTE,
			Application = SDLK_APPLICATION,
			AudioMute = SDLK_AUDIOMUTE,
			AudioNext = SDLK_AUDIONEXT,
			AudioPlay = SDLK_AUDIOPLAY,
			AudioPrev = SDLK_AUDIOPREV,
			AuidoStop = SDLK_AUDIOSTOP,
			B = SDLK_b,
			Backslash = SDLK_BACKSLASH,
			Backspace = SDLK_BACKSPACE,
			BrightnessDown = SDLK_BRIGHTNESSDOWN,
			BrightnessUp = SDLK_BRIGHTNESSUP,
			C = SDLK_c,
			Calculator = SDLK_CALCULATOR,
			Cancel = SDLK_CANCEL,
			Capslock = SDLK_CAPSLOCK,
			Clear = SDLK_CLEAR,
			ClearAgain = SDLK_CLEARAGAIN,
			Comma = SDLK_COMMA,
			Computer = SDLK_COMPUTER,
			Copy = SDLK_COPY,
			CrSel = SDLK_CRSEL,
			CurrencySubUnit = SDLK_CURRENCYSUBUNIT,
			CurrencyUnit = SDLK_CURRENCYUNIT,
			Cut = SDLK_CUT,
			D = SDLK_d,
			DecimalSeparator = SDLK_DECIMALSEPARATOR,
			Delete = SDLK_DELETE,
			DisplaySwitch = SDLK_DISPLAYSWITCH,
			Down = SDLK_DOWN,
			E = SDLK_e,
			Eject = SDLK_EJECT,
			End = SDLK_END,
			Equals = SDLK_EQUALS,
			Escape = SDLK_ESCAPE,
			Execute = SDLK_EXECUTE,
			Exsel = SDLK_EXSEL,
			F = SDLK_f,
			F1 = SDLK_F1,
			F10 = SDLK_F10,
			F11 = SDLK_F11,
			F12 = SDLK_F12,
			F13 = SDLK_F13,
			F14 = SDLK_F14,
			F15 = SDLK_F15,
			F16 = SDLK_F16,
			F17 = SDLK_F17,
			F18 = SDLK_F18,
			F19 = SDLK_F19,
			F2 = SDLK_F2,
			F20 = SDLK_F20,
			F21 = SDLK_F21,
			F22 = SDLK_F22,
			F23 = SDLK_F23,
			F24 = SDLK_F24,
			F3 = SDLK_F3,
			F4 = SDLK_F4,
			F5 = SDLK_F5,
			F6 = SDLK_F6,
			F7 = SDLK_F7,
			F8 = SDLK_F8,
			F9 = SDLK_F9,
			Find = SDLK_FIND,
			G = SDLK_g,
			BackQuote = SDLK_BACKQUOTE,
			H = SDLK_h,
			Help = SDLK_HELP,
			Home = SDLK_HOME,
			I = SDLK_i,
			Insert = SDLK_INSERT,
			J = SDLK_j,
			K = SDLK_k,
			KBDIllumDown = SDLK_KBDILLUMDOWN,
			KBDIllumToggle = SDLK_KBDILLUMTOGGLE,
			KBDIllumUp = SDLK_KBDILLUMUP,
			Keypad0 = SDLK_KP_0,
			Keypad00 = SDLK_KP_00,
			Keypad000 = SDLK_KP_000,
			Keypad1 = SDLK_KP_1,
			Keypad2 = SDLK_KP_2,
			Keypad3 = SDLK_KP_3,
			Keypad4 = SDLK_KP_4,
			Keypad5 = SDLK_KP_5,
			Keypad6 = SDLK_KP_6,
			Keypad7 = SDLK_KP_7,
			Keypad8 = SDLK_KP_8,
			Keypad9 = SDLK_KP_9,
			KeypadA = SDLK_KP_A,
			KeypadAmpersand = SDLK_KP_AMPERSAND,
			KeypadAt = SDLK_KP_AT,
			KeypadB = SDLK_KP_B,
			KeypadBackspace = SDLK_KP_BACKSPACE,
			KeypadBinary = SDLK_KP_BINARY,
			KeypadC = SDLK_KP_C,
			KeypadClear = SDLK_KP_CLEAR,
			KeypadClearEntry = SDLK_KP_CLEARENTRY,
			KeypadColon = SDLK_KP_COLON,
			KeypadComma = SDLK_KP_COMMA,
			KeypadD = SDLK_KP_D,
			KeypadDoubleAmpersand = SDLK_KP_DBLAMPERSAND,
			KeypadDoubleVerticalBar = SDLK_KP_DBLVERTICALBAR,
			KeypadDecimal = SDLK_KP_DECIMAL,
			KeypadDivide = SDLK_KP_DIVIDE,
			KeypadE = SDLK_KP_E,
			KeypadEnter = SDLK_KP_ENTER,
			KeypadEquals = SDLK_KP_EQUALS,
			KeypadEqualsAS400 = SDLK_KP_EQUALSAS400,
			KeypadExclamation = SDLK_KP_EXCLAM,
			KeypadF = SDLK_KP_F,
			KeypadGreater = SDLK_KP_GREATER,
			KeypadHash = SDLK_KP_HASH,
			KeypadHexadecimal = SDLK_KP_HEXADECIMAL,
			KeypadLBrace = SDLK_KP_LEFTBRACE,
			KeypadLParenthesis = SDLK_KP_LEFTPAREN,
			KeypadLess = SDLK_KP_LESS,
			KeypadMemAdd = SDLK_KP_MEMADD,
			KeypadMemClear = SDLK_KP_MEMCLEAR,
			KeypadMemDivide = SDLK_KP_MEMDIVIDE,
			KeypadMemMultiply = SDLK_KP_MEMMULTIPLY,
			KeypadMemRecall = SDLK_KP_MEMRECALL,
			KeypadMemStore = SDLK_KP_MEMSTORE,
			KeypadMemSubstract = SDLK_KP_MEMSUBTRACT,
			KeypadMinus = SDLK_KP_MINUS,
			KeypadMultiply = SDLK_KP_MULTIPLY,
			KeypadOctal = SDLK_KP_OCTAL,
			KeypadPercent = SDLK_KP_PERCENT,
			KeypadPeriod = SDLK_KP_PERIOD,
			KeypadPlus = SDLK_KP_PLUS,
			KeypadPlusMinus = SDLK_KP_PLUSMINUS,
			KeypadPower = SDLK_KP_POWER,
			KeypadRBrace = SDLK_KP_RIGHTBRACE,
			KeypadRParenthesis = SDLK_KP_RIGHTPAREN,
			KeypadSpace = SDLK_KP_SPACE,
			KeypadTab = SDLK_KP_TAB,
			KeypadVerticalBar = SDLK_KP_VERTICALBAR,
			KeypadXor = SDLK_KP_XOR,
			L = SDLK_l,
			LAlt = SDLK_LALT,
			LControl = SDLK_LCTRL,
			Left = SDLK_LEFT,
			LBracket = SDLK_LEFTBRACKET,
			LGUI = SDLK_LGUI,
			LShift = SDLK_LSHIFT,
			M = SDLK_m,
			Mail = SDLK_MAIL,
			MediaSelect = SDLK_MEDIASELECT,
			Menu = SDLK_MENU,
			Minus = SDLK_MINUS,
			Mode = SDLK_MODE,
			Mute = SDLK_MUTE,
			N = SDLK_n,
			NumLockClear = SDLK_NUMLOCKCLEAR,
			O = SDLK_o,
			Oper = SDLK_OPER,
			Out = SDLK_OUT,
			P = SDLK_p,
			PageDown = SDLK_PAGEDOWN,
			PageUp = SDLK_PAGEUP,
			Paste = SDLK_PASTE,
			Pause = SDLK_PAUSE,
			Period = SDLK_PERIOD,
			Power = SDLK_POWER,
			PrintScren = SDLK_PRINTSCREEN,
			Prior = SDLK_PRIOR,
			Q = SDLK_q,
			R = SDLK_r,
			RAlt = SDLK_RALT,
			RControl = SDLK_RCTRL,
			Return = SDLK_RETURN,
			Return2 = SDLK_RETURN2,
			RGUI = SDLK_RGUI,
			Right = SDLK_RIGHT,
			RBracket = SDLK_RIGHTBRACKET,
			RShift = SDLK_RSHIFT,
			S = SDLK_s,
			ScrollLock = SDLK_SCROLLLOCK,
			Select = SDLK_SELECT,
			Semicolont = SDLK_SEMICOLON,
			Separator = SDLK_SEPARATOR,
			Slash = SDLK_SLASH,
			Sleep = SDLK_SLEEP,
			Space = SDLK_SPACE,
			Stop = SDLK_STOP,
			Sysreq = SDLK_SYSREQ,
			T = SDLK_t,
			Tab = SDLK_TAB,
			ThousandsSeparator = SDLK_THOUSANDSSEPARATOR,
			U = SDLK_u,
			Undo = SDLK_UNDO,
			Unknown = SDLK_UNKNOWN,
			UP = SDLK_UP,
			V = SDLK_v,
			VolumeDown = SDLK_VOLUMEDOWN,
			VolumeUp = SDLK_VOLUMEUP,
			W = SDLK_w,
			WWW = SDLK_WWW,
			X = SDLK_x,
			Y = SDLK_y,
			Z = SDLK_z,
			Ampersand = SDLK_AMPERSAND,
			Asterisk = SDLK_ASTERISK,
			At = SDLK_AT,
			Caret = SDLK_CARET,
			Colon = SDLK_COLON,
			Dollar = SDLK_DOLLAR,
			Exclamation = SDLK_EXCLAIM,
			Greater = SDLK_GREATER,
			Hash = SDLK_HASH,
			LParenthesis = SDLK_LEFTPAREN,
			Less = SDLK_LESS,
			Percent = SDLK_PERCENT,
			Plus = SDLK_PLUS,
			Question = SDLK_QUESTION,
			DoubleQuote = SDLK_QUOTEDBL,
			RParenthesis = SDLK_RIGHTPAREN,
			Underscore = SDLK_UNDERSCORE
		};

		///
		/// \brief Tells wether the requested key is pressed
		///
		/// In this context, "pressed" is interpreted as
		/// being held in the current state and not in the previous state.
		///
		bool isKeyPressed(Key k) const {return (keysHeldOld.find(k) == keysHeldOld.end()) && (keysHeld.find(k) != keysHeld.end());}

		///
		/// \brief Tells wether the requested key is released
		///
		/// In this context, "released" is interpreted as
		/// not being held in the current state and being held in the previous state.
		///
		bool isKeyReleased(Key k) const {return (keysHeldOld.find(k) != keysHeldOld.end()) && (keysHeld.find(k) == keysHeld.end());}

		///
		/// \brief Tells wether the requested key is held
		///
		/// In this context, "held" is interpreted as
		/// being held in the current state.
		///
		bool isKeyHeld(Key k) const {return (keysHeld.find(k) != keysHeld.end());}
	private:
		Keyboard();
		~Keyboard();
		friend class Environment;
		void update();
		void processEvent(const SDL_Event& event);
		std::set<Key> keysHeld;
		std::set<Key> keysHeldOld;
		bool focus;
};

///
/// @class Keyboard Keyboard.hpp "enviroment/Keyboard.hpp"
/// @ingroup System
///
/// You can use this class within an init Environment to access the current
/// keyboard device's state. Not all keys are supported in all devices and will
/// not be ever marked as pressed. The state of this device will be updated to
/// match recieved events whenever Environment::update() is called.
///
/// A Key will just be pressed for one frame (one update()) call. Then held for
/// an indefinite number of frames and released right after. For Example, if the
/// user pressed the A Key on frame 1 and released it on frame 4, this would
/// register (updating the environment every frame of course):
///
/// - Frame 1
///   + Key Keyboard::A is pressed
///   + Key Keyboard::A is held
///   + Key Keyboard::A is not released
/// - Frame 2
///   + Key Keyboard::A is not pressed
///   + Key Keyboard::A is held
///   + Key Keyboard::A is not released
/// - Frame 3
///   + Key Keyboard::A is not pressed
///   + Key Keyboard::A is held
///   + Key Keyboard::A is not released
/// - Frame 4
///   + Key Keyboard::A is not pressed
///   + Key Keyboard::A is not held
///   + Key Keyboard::A is released
///
/// @see Environment

#endif // KEYBOARD_HPP
