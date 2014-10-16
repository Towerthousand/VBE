#include <VBE/system/Clock.hpp>
#include <VBE/system/sdl2/ClockImpl.hpp>

// static
float Clock::getSeconds() {
	return ClockImpl::getSeconds();
}

// static
void Clock::sleepSeconds(float seconds) {
	ClockImpl::sleepSeconds(seconds);
}
