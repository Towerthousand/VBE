#include "Environment.hpp"
#include "../scene/Game.hpp"

Screen* Environment::screen = nullptr;
Keyboard* Environment::keyboard = nullptr;
Mouse* Environment::mouse = nullptr;
bool Environment::running = false;

Environment::Environment() {}
Environment::~Environment() {}

void Environment::startUp() {
	VBE_ASSERT(!running, "Trying to start up an already initialized Environment");
	VBE_ASSERT(SDL_WasInit(SDL_INIT_EVERYTHING) == 0, "SDL Has been init from outside of this application");
	running = true;
	int ret = SDL_Init(SDL_INIT_EVERYTHING);
	VBE_ASSERT(ret == 0, "Error when initializating SDL" << SDL_GetError());
	screen = new Screen();
	mouse = new Mouse();
	keyboard = new Keyboard();
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

			// Window events
			case SDL_WINDOWEVENT:
				screen->processEvent(e);
				break;

				// System events
			case SDL_QUIT:
				if(Game::i() != nullptr)
					Game::i()->isRunning = false;
				break;

				// Keyboard events
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				keyboard->processEvent(e);
				break;
			case SDL_TEXTEDITING:
				//TODO KEYBOARD
				break;
			case SDL_TEXTINPUT:
				//TODO KEYBOARD
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
	return 0.001f*SDL_GetTicks();
}

Screen* Environment::getScreen() {
	VBE_ASSERT(running, "Can't get screen, Environment is not initialized");
	return screen;
}
