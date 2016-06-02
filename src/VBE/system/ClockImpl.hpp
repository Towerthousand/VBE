#include <VBE/config.hpp>

#if defined(VBE_SYSTEM_SDL2)
#include <VBE/system/sdl2/ClockImpl.hpp>
#elif defined(VBE_SYSTEM_ANDROID)
#include <VBE/system/android/ClockImpl.hpp>
#else
#error No system defined
#endif
