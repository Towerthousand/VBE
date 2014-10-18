#ifndef SDL_HPP
#define SDL_HPP

#include <SDL2/SDL.h>
#include <VBE/system/Log.hpp>

//SDL_ASSERT
#ifdef __DEBUG
#define SDL_ASSERT( sdl_code ) VBE_ASSERT(sdl_code >= 0, "SDL error: " << SDL_GetError())
#else
#define SDL_ASSERT( sdl_code ) sdl_code
#endif


#endif // SDL_HPP
