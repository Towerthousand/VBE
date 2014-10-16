#include "Environment.hpp"
#include "../scene/Game.hpp"

Screen* Environment::screen = nullptr;
Keyboard* Environment::keyboard = nullptr;
Mouse* Environment::mouse = nullptr;
bool Environment::running = false;
StartingConfig Environment::initialConfig = StartingConfig();

Environment::Environment() {}
Environment::~Environment() {}

StartingConfig& Environment::config() {
	VBE_WARN(!running, "Accessing the Environment setup configurations after starting up" << Log::Line <<
			 "Any changes on this configuration won't affect the running Environment" << Log::Line <<
			 "To change settings on the run, please interface with the respective device (screen, mouse..)");
	return initialConfig;
}

void Environment::startUp() {
	VBE_ASSERT(!running, "Trying to start up an already initialized Environment");
	VBE_ASSERT(SDL_WasInit(SDL_INIT_EVERYTHING) == 0, "SDL Has been init from outside of this application");
	running = true;
	int ret = SDL_Init(SDL_INIT_EVERYTHING);
	VBE_ASSERT(ret == 0, "Error when initializating SDL" << SDL_GetError());
	screen = new Screen(initialConfig);
	mouse = new Mouse();
	keyboard = new Keyboard();

	mouse->setGrab(initialConfig.mouseGrab);
	mouse->setRelativeMouseMode(initialConfig.mouseRelativeMode);
}

void Environment::shutDown() {
	VBE_ASSERT(running, "Trying to shut down an uninitilalized Environment. Call Environment::startUp() to initialize it");
	delete screen;
	delete mouse;
	SDL_Quit();
	running = false;
}

void Environment::update() {
	VBE_ASSERT(running, "Trying to process events in an uninitialized Environment. Call Environment::startUp() to initialize it");
	if(mouse != nullptr) mouse->update();
	if(keyboard != nullptr) keyboard->update();
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		switch (e.type) {

			// System events
			case SDL_QUIT:
				if(Game::i() != nullptr)
					Game::i()->isRunning = false;
				break;

				// Window events
			case SDL_WINDOWEVENT:
				screen->processEvent(e);
				break;

				// Keyboard events
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			case SDL_TEXTEDITING:
			case SDL_TEXTINPUT:
				keyboard->processEvent(e);
				break;

				// Mouse events
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEWHEEL:
				mouse->processEvent(e);
				break;
			default:
				break;
		}
	}
}

float Environment::getClock() {
	VBE_ASSERT(running, "Can't get clock, Environment is not initialized");
	return 0.001f*SDL_GetTicks();
}

Screen* Environment::getScreen() {
	VBE_ASSERT(running, "Can't get screen, Environment is not initialized");
	return screen;
}

Mouse*Environment::getMouse() {
	VBE_ASSERT(running, "Can't get mouse, Environment is not initialized");
	return mouse;
}

Keyboard*Environment::getKeyboard() {
	VBE_ASSERT(running, "Can't get keyboard, Environment is not initialized");
	return keyboard;
}
