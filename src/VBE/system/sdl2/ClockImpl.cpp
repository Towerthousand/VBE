#include <VBE/system/sdl2/ClockImpl.hpp>
#include <VBE/system/sdl2/sdl2.hpp>

// static
long long ClockImpl::getMicroseconds() {
    return SDL_GetTicks() * 1000;
}

// static
void ClockImpl::sleepMicroseconds(long long useconds) {
    SDL_Delay((useconds+500)/1000);
}
