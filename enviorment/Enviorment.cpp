#include "Enviorment.hpp"
#include "Screen.hpp"
#include "../scene/Game.hpp"

Screen* Enviorment::screen = nullptr;
bool Enviorment::running = false;

Enviorment::Enviorment() {}
Enviorment::~Enviorment() {}

void Enviorment::startUp() {
	VBE_ASSERT(!running, "Trying to start up an already initialized enviorment");
	VBE_ASSERT(SDL_WasInit(SDL_INIT_EVERYTHING) == 0, "SDL Has been init from outside of this application");
	running = true;
	int ret = SDL_Init(SDL_INIT_EVERYTHING);
	VBE_ASSERT(ret == 0, "Error when initializating SDL" << SDL_GetError());
	screen = new Screen();
}

void Enviorment::shutDown() {
	VBE_ASSERT(running, "Trying to shut down an uninitilalized enviorment. Call Enviorment::startUp() to initialize it");
	delete screen;
	SDL_Quit();
	running = false;
}

void Enviorment::processEvents() {
	VBE_ASSERT(running, "Trying to process events in an uninitialized enviorment. Call Enviorment::startUp() to initialize it");
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		switch (e.type) {

			// Window events
			case SDL_WINDOWEVENT:
				switch(e.window.type) {
					case SDL_WINDOWEVENT_CLOSE:
						if(Game::i() != nullptr)
							Game::i()->isRunning = false;
						break;
					case SDL_WINDOWEVENT_RESIZED:
						screen->width = 0;
						screen->height = 0;
						break;
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						screen->width = 0;
						screen->height = 0;
						break;
					case SDL_WINDOWEVENT_ENTER:
						//TODO MOUSE
						break;
					case SDL_WINDOWEVENT_LEAVE:
						//TODO MOUSE
						break;
					case SDL_WINDOWEVENT_EXPOSED: break;
					case SDL_WINDOWEVENT_FOCUS_GAINED:
						//TODO KEYBOARD
						break;
					case SDL_WINDOWEVENT_FOCUS_LOST:
						//TODO KEYBOARD
						break;
					case SDL_WINDOWEVENT_HIDDEN: break;
					case SDL_WINDOWEVENT_MAXIMIZED: break;
					case SDL_WINDOWEVENT_MINIMIZED: break;
					case SDL_WINDOWEVENT_MOVED: break;
					case SDL_WINDOWEVENT_RESTORED: break;
					case SDL_WINDOWEVENT_SHOWN: break;
					default: break;
				}
				break;

				// System events
			case SDL_QUIT:
				if(Game::i() != nullptr)
					Game::i()->isRunning = false;
				break;
			case SDL_SYSWMEVENT: break;

				// Keyboard events
			case SDL_KEYDOWN:
				//TODO KEYBOARD
				break;
			case SDL_KEYUP:
				//TODO KEYBOARD
				break;
			case SDL_TEXTEDITING:
				//TODO KEYBOARD
				break;
			case SDL_TEXTINPUT:
				//TODO KEYBOARD
				break;

				// Mouse events
			case SDL_MOUSEMOTION:
				//TODO MOUSE
				break;
			case SDL_MOUSEBUTTONDOWN:
				//TODO MOUSE
				break;
			case SDL_MOUSEBUTTONUP:
				//TODO MOUSE
				break;
			case SDL_MOUSEWHEEL:
				//TODO MOUSE
				break;
			default: break;
		}
	}
}

Screen* Enviorment::getScreen() {
	VBE_ASSERT(running, "Can't get screen, Enviorment is not initialized");
	return screen;
}
