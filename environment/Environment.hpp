#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "tools.hpp"

class Screen;
class Keyboard;
class Mouse;
class Environment {
	public:
		static void startUp();
		static void shutDown();

		static void processEvents();

		static Screen* getScreen();
		//Keyboard* getKeyboard() const { return keyboard; }
		Mouse* getMouse() const { return mouse; }
	private:
		Environment();
		~Environment();

		static bool running;
		static Screen* screen;
		static Keyboard* keyboard;
		static Mouse* mouse;
};

#endif // Environment_HPP
