#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>

#include"game.h"
#include"graphics.h"
#include"defs.h"
const char *WINDOW_TITLE = "Wordle";

using namespace std;

void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char* argv[])
{
    srand(time(0));
    Graphics graphics;
    SDL_Window* window = graphics.initSDL(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    if(!window) return -1;
    SDL_Renderer* renderer =graphics.createRenderer(window);
    if(!renderer) {
        graphics.quitSDL();
        return -1;
    }
    graphics.drawGrid();
    SDL_RenderPresent(renderer);

    if (TTF_Init() == -1) {
        graphics.logErrorAndExit("TTF_Init", TTF_GetError());
        return -1;
    }
    TTF_Font* font = graphics.loadFont("arial.ttf", 24);
    SDL_Color color = {255, 255, 255, 255};
    SDL_Texture* helloText = graphics.renderText("WELCOME TO WORDLE", font, color);
    graphics.renderTexture(helloText, 300, 500);

    graphics.presentScene();

    waitUntilKeyPressed();
    SDL_DestroyTexture(helloText);
    helloText=NULL;
    TTF_CloseFont(font);
    graphics.quitSDL();
    return 0;
}
