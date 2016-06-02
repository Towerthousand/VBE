#include <VBE/system/Clock.hpp>
#include <VBE/system/ClockImpl.hpp>

// static
float Clock::getSeconds() {
    return ClockImpl::getMicroseconds() * 1e-6f;
}

// static
long long Clock::getMicroseconds() {
    return ClockImpl::getMicroseconds();
}

// static
void Clock::sleepSeconds(float seconds) {
    ClockImpl::sleepMicroseconds(seconds * 1e6);
}

// static
void Clock::sleepMicroseconds(long long useconds) {
    ClockImpl::sleepMicroseconds(useconds);
}
