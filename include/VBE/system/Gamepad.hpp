#ifndef GAMEHPP
#define GAMEHPP

class Gamepad final {
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

		float axis(Axis a);

		bool pressed(Button b);

		bool justPressed(Button b);

		bool justReleased(Button b);

		bool isConnected();

		static Gamepad getGamepad(int id);

private:
		Gamepad(int id);

		int id;
};

#endif // GAMEHPP
