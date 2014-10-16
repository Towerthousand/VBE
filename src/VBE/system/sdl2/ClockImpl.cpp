#include <VBE/system/sdl2/ClockImpl.hpp>
#include <SDL2/SDL.h>

// static
float ClockImpl::getSeconds() {
	return 0.001f*SDL_GetTicks();
}

// static
void ClockImpl::sleepSeconds(float seconds) {
	SDL_Delay(seconds*1000 + 0.5);
}
