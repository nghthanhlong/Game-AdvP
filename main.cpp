#include <iostream>

#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>

#include"game.h"
#include"graphics.h"
#include"run.h"

const char *WINDOW_TITLE = "Hardle";
const char *fontUsed = "assets/PatrickHand-Regular.ttf";
const char *backgroundUsed="assets/background.jpg";

using namespace std;

int main(int argc, char* argv[])
{
    Graphics graphics;
    Game game;
    Run run;

    SDL_Window* window = graphics.initSDL(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SDL_Renderer* renderer =graphics.createRenderer(window);

    TTF_Font* font = graphics.loadFont(fontUsed, 36);
    graphics.font=font;

    SDL_Texture *background=graphics.loadTexture(backgroundUsed, renderer);
    graphics.background=background;

    if(!renderer || !background || !font) {
        graphics.quitSDL();
        return -1;
    }
    run.gameRun(renderer, background, graphics, game);
    graphics.quitSDL();
    return 0;
}
