#ifndef GAMEHPP
#define GAMEHPP

class Gamepad {
	public:
		static constexpr int COUNT = 4;

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

		static float axis(int id, Axis a);
		static bool pressed(int id, Button b);
		static bool justPressed(int id, Button b);
		static bool justReleased(int id, Button b);
		static bool isConnected(int id);
};

#endif // GAMEHPP
