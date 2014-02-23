#ifndef ENVIORMENT_HPP
#define ENVIORMENT_HPP
#include "tools.hpp"

class Screen;
class Enviorment {
	public:
		static void startUp();
		static void shutDown();

		static void processEvents();

		static Screen* getScreen();
		//Keyboard* getKeyboard() const { return keyboard; }
		//Mouse* getMouse() const { return mouse; }
	private:
		Enviorment();
		~Enviorment();

		static bool running;
		static Screen* screen;
		//Keyboard* keyboard;
		//Mouse* mouse;
};

#endif // ENVIORMENT_HPP
