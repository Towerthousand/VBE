#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "Screen.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

///
/// @brief Handles environment management and I/O devices
///
class Environment {
	public:
		static StartingConfig& setup();
		static void startUp();
		static void shutDown();

		static void update();

		static Screen* getScreen();
		static Keyboard* getKeyboard() { return keyboard; }
		static Mouse* getMouse() { return mouse; }
		static float getClock();
	private:
		Environment();
		~Environment();

		static bool running;
		static Screen* screen;
		static Keyboard* keyboard;
		static Mouse* mouse;
		static StartingConfig initialConfig;
};
///
/// @class Environment Environment.hpp "environment/Environment.hpp"
///	@ingroup System
///
/// This is the central class for everything system and I/O related.
///
/// Before starting up the application you can config the Environment
/// variables, specified in @ref StartingConfig
///
#endif // Environment_HPP
