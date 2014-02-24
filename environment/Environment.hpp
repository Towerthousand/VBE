#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "Screen.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

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

#endif // Environment_HPP
