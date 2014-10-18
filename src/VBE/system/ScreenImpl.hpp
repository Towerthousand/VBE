#include <VBE/config.hpp>

#if defined(VBE_SYSTEM_SDL2)
	#include <VBE/system/sdl2/ScreenImpl.hpp>
#elif defined(SFML_SYSTEM_ANDROID)
	#include <VBE/system/android/ScreenImpl.hpp>
#endif
