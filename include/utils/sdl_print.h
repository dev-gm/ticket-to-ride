#ifndef UTILS_SDL_PRINT_H

#include <SDL2/SDL.h>

#define UTILS_SDL_PRINT_H

#define SDL_ERROR_IF_NULL(var, ...) if (var == NULL) SDL_ERROR(__VA_ARGS__)

#endif
