#include "filehandler.h"
#include "renderStuff.h"

int main(void)
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    
    initSDL(&window, &renderer, &font);

    int close = 0;
    SDL_Event event;

    char inputText[MAX_TEXT_LENGTH] = {0};
    readFileToString("text", inputText, MAX_TEXT_LENGTH);

    SDL_StartTextInput();

    int windowWidth = WINDOW_WIDTH;
    int windowHeight = WINDOW_HEIGHT;

    while (!close) {
        handleUserInput(&event, &close, inputText, window, &windowWidth, &windowHeight);

        CheckCode_SDL(
                        SDL_SetRenderDrawColor(renderer, 155, 10, 50, 255));
        CheckCode_SDL(
                        SDL_RenderClear(renderer));

        renderTextToWindow(renderer, font, inputText, windowWidth, windowHeight);

        SDL_RenderPresent(renderer);
    }


    SDL_StopTextInput();
    cleanup(window, renderer, font);

    return 0;
}
