#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include"defs.h"
#include "game.h"

struct Graphics
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture *background;

    void logErrorAndExit(const char* msg, const char* error);
    SDL_Window* initSDL(int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE);
    SDL_Renderer* createRenderer(SDL_Window* window);
    void quitSDL();

    void drawGrid();
    void drawLetter(Cell grid[GRID_ROWS][GRID_COLS], Game game);
    void drawResult(const std::string& message, const std::string &answer);

    SDL_Texture *loadTexture(const char *fileName, SDL_Renderer *renderer);
    TTF_Font* loadFont(const char*path, int size);
    void presentScene();

    void drawReplayMessage();
    void drawVictoryNumber(int winCount);
    void drawTimesPlayed(int times);
};

#endif // GRAPHICS_H_INCLUDED
