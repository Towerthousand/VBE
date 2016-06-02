#include <VBE/system/android/ClockImpl.hpp>

#include <time.h>
#include <unistd.h>

// static
float ClockImpl::getSeconds() {
    struct timespec monotime;
    clock_gettime(CLOCK_MONOTONIC, &monotime);

    return monotime.tv_sec + monotime.tv_nsec*1e-9f;
}

// static
void ClockImpl::sleepSeconds(float seconds) {
    usleep(seconds*1e6f + 0.5);
}
