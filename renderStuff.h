#include "util.h"

#define MAX_TEXT_LENGTH 2048
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y, int ww) {
    if (text == NULL || text[0] == '\0') return;

    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text, color, ww);
    CheckPointer_SDL(surface);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    CheckPointer_SDL(texture);

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void initSDL(SDL_Window** window, SDL_Renderer** renderer, TTF_Font** font) {
    CheckCode_SDL(SDL_Init(SDL_INIT_VIDEO));
    CheckCode_SDL(TTF_Init());

    *window = SDL_CreateWindow("Text Rendering",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH, WINDOW_HEIGHT,
                               SDL_WINDOW_RESIZABLE);
    CheckPointer_SDL(*window);

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    CheckPointer_SDL(*renderer);

    *font = TTF_OpenFont("/usr/share/fonts/truetype/noto/NotoSans-Regular.ttf", 24);
    CheckPointer_TTF(*font);
}

void handleUserInput(SDL_Event* event, int* close, char* inputText, SDL_Window* window, int* windowWidth, int* windowHeight) {
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                *close = 1;
                break;

            case SDL_TEXTINPUT:
                if (strlen(inputText) + strlen(event->text.text) < MAX_TEXT_LENGTH - 1) {
                    strcat(inputText, event->text.text);
                }
                break;

            case SDL_KEYDOWN:
                if (event->key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0) {
                    inputText[strlen(inputText) - 1] = '\0';
                } else if (event->key.keysym.sym == SDLK_RETURN) {
                    if (strlen(inputText) < MAX_TEXT_LENGTH - 1) {
                        strcat(inputText, "\n");  
                    }
                }if ((SDL_GetModState() & KMOD_CTRL) && event->key.keysym.sym == SDLK_s){
                        writeFileFromString("text", inputText);

                }
                break;

            case SDL_WINDOWEVENT:
                if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    SDL_GetWindowSize(window, windowWidth, windowHeight);
                }
                break;


            default:
                break;
        }
    }
}

void renderTextToWindow(SDL_Renderer* renderer, TTF_Font* font, const char* inputText, int windowWidth, int windowHeight) {
    SDL_Color textColor = {255, 255, 255, 255};
    int lineHeight = 30;
    int yOffset = 50;

    int currentY = yOffset;
    const char* currentLine = inputText; 
    while (currentLine != NULL && currentY < windowHeight - lineHeight) {
        const char* nextLine = strchr(currentLine, '\n'); 
        if (nextLine != NULL) {
            char* temp = (char*)nextLine; 
            *temp = '\0'; 
        }
        renderText(renderer, font, currentLine, textColor, 50, currentY, windowWidth - 100);
        currentY += lineHeight;
        if (nextLine != NULL) {
            currentLine = nextLine + 1;
        } else {
            break;
        }
    }
}

void cleanup(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}