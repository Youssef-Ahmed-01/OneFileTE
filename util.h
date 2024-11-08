#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define TTF_GetError SDL_GetError
#define MAX_TEXT_LENGTH 2048
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

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