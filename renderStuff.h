#include "util.h"
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

    *window = SDL_CreateWindow("Text Editor",
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


void handleUserInput(SDL_Event* event, int* close, char* inputText, int* cursorIndex, SDL_Window* window, int* windowWidth, int* windowHeight, int* cursorPosX, int* cursorPosY, TTF_Font* font) {
    while (SDL_PollEvent(event)) {
        switch (event->type) {
            case SDL_QUIT:
                *close = 1;
                break;

            case SDL_TEXTINPUT:
                if (strlen(inputText) < MAX_TEXT_LENGTH - 1) {
                    memmove(&inputText[*cursorIndex + strlen(event->text.text)], &inputText[*cursorIndex], strlen(&inputText[*cursorIndex]) + 1);
                    strncpy(&inputText[*cursorIndex], event->text.text, strlen(event->text.text));
                    *cursorIndex += strlen(event->text.text);

                    int glyphWidth;
                    TTF_GlyphMetrics(font, event->text.text[0], NULL, NULL, NULL, NULL, &glyphWidth);
                    *cursorPosX += glyphWidth;
                }
                break;

            case SDL_KEYDOWN:
                switch (event->key.keysym.sym) {
                    case SDLK_BACKSPACE:
                        if (*cursorIndex > 0) {
                            int glyphWidth;
                            TTF_GlyphMetrics(font, inputText[*cursorIndex - 1], NULL, NULL, NULL, NULL, &glyphWidth);
                            *cursorPosX -= glyphWidth;

                            memmove(&inputText[*cursorIndex - 1], &inputText[*cursorIndex], strlen(&inputText[*cursorIndex]) + 1);
                            (*cursorIndex)--;
                        }
                        break;

                    case SDLK_RETURN:
                        if (strlen(inputText) < MAX_TEXT_LENGTH - 1) {
                            memmove(&inputText[*cursorIndex + 1], &inputText[*cursorIndex], strlen(&inputText[*cursorIndex]) + 1);
                            inputText[*cursorIndex] = '\n';
                            (*cursorIndex)++;
                            *cursorPosX = 50;
                            *cursorPosY += 30;
                            
                        }
                        break;

                    case SDLK_LEFT:
                        if (*cursorIndex > 0) {
                            (*cursorIndex)--;
                            int glyphWidth;
                            TTF_GlyphMetrics(font, inputText[*cursorIndex], NULL, NULL, NULL, NULL, &glyphWidth);
                            *cursorPosX -= glyphWidth;

                            if (*cursorPosX < 50) {
                                *cursorPosX = *windowWidth - 50;
                                *cursorPosY -= 30;
                            }
                        }
                        break;

                    case SDLK_RIGHT:
                        if (*cursorIndex < strlen(inputText)) {
                            int glyphWidth;
                            TTF_GlyphMetrics(font, inputText[*cursorIndex], NULL, NULL, NULL, NULL, &glyphWidth);
                            *cursorPosX += glyphWidth;
                            (*cursorIndex)++;

                            if (*cursorPosX > *windowWidth - 50) {
                                *cursorPosX = 50;
                                *cursorPosY += 30;
                            }
                        }
                        break;

                    case SDLK_UP:
                        *cursorPosY -= 30;
                        break;

                    case SDLK_DOWN:
                        *cursorPosY += 30;
                        break;

                }
                if ((SDL_GetModState() & KMOD_CTRL) && event->key.keysym.sym == SDLK_s){
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
    int yOffset = 50;
    renderText(renderer, font, inputText, textColor, 50, yOffset, windowWidth - 100);
}

void renderCursor(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect cursorRect = { x, y, 2, 24 };
    SDL_RenderFillRect(renderer, &cursorRect);
}

void cleanup(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}