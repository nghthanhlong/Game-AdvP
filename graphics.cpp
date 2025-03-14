#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>
#include"graphics.h"
#include"defs.h"

void Graphics::logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* Graphics::initSDL(int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logErrorAndExit("SDL_Init", SDL_GetError());
    }

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
        logErrorAndExit("SDL_image error:", IMG_GetError());
    }

    window = SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        logErrorAndExit("Create Window", SDL_GetError());
    }

    return window;
}

SDL_Renderer* Graphics::createRenderer(SDL_Window* window) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    return renderer;
}

void Graphics::quitSDL(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit(); SDL_Quit();
}

void Graphics::cleanup(){
    TTF_CloseFont(font);
    quitSDL();
    TTF_Quit();
}

void Graphics::drawGrid(){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int startX=(WINDOW_WIDTH-GRID_COLS*CELL_SIZE)/2;
    int startY=(WINDOW_HEIGHT-GRID_ROWS*CELL_SIZE)/2;

    for(int i=0; i<=GRID_COLS; i++) {
        int x=startX+i*CELL_SIZE;
        SDL_RenderDrawLine(renderer,x,startY,x,startY+GRID_ROWS*CELL_SIZE);
    }

    for(int i=0; i<=GRID_ROWS; i++) {
        int y=startY+i*CELL_SIZE;
        SDL_RenderDrawLine(renderer,startX,y,startX+GRID_COLS*CELL_SIZE, y);
    }
}
