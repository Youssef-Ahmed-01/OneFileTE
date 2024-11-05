#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define TTF_GetError SDL_GetError


void CheckCode_SDL(int code)
{
    if (code < 0) {
        fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
        exit(1);
    }
}

void *CheckPointer_SDL(void *ptr)
{
    if (ptr == NULL) {
        fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
        exit(1);
    }
    return ptr;
}

void CheckCode_TTF(int code)
{
    if (code < 0) {
        fprintf(stderr, "SDL ERROR: %s\n", TTF_GetError());
        exit(1);
    }
}

void *CheckPointer_TTF(void *ptr)
{
    if (ptr == NULL) {
        fprintf(stderr, "SDL ERROR: %s\n", TTF_GetError());
        exit(1);
    }
    return ptr;
}