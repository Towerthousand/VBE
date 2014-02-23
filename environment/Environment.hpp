#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "tools.hpp"
#include "Screen.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

class Environment {
	public:
		static void startUp();
		static void shutDown();

		static void update();

		static Screen* getScreen();
		static Keyboard* getKeyboard() { return keyboard; }
		static Mouse* getMouse() { return mouse; }
	private:
		Environment();
		~Environment();

		static bool running;
		static Screen* screen;
		static Keyboard* keyboard;
		static Mouse* mouse;
};

#endif // Environment_HPP
