#include <VBE/config.hpp>

#if defined(VBE_SYSTEM_SDL2)
	#include <VBE/system/sdl2/InputImpl.hpp>
#elif defined(SFML_SYSTEM_ANDROID)
	#include <VBE/system/android/InputImpl.hpp>
#endif
