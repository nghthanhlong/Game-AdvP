#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "defs.h"
#include "game.h"

struct Graphics
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    void logErrorAndExit(const char* msg, const char* error);
    SDL_Window* initSDL(int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE);
    SDL_Renderer* createRenderer(SDL_Window* window);
    void quitSDL();
    void cleanup();

    void drawGrid();
    //void drawLetter(Cell grid[GRID_ROWS][GRID_COLS]);
    void drawResult(const std::string& message);

    void loadAndRenderBackground(const char *imageFileName);
    std::string toUpperCase(const std::string& input);


    TTF_Font* loadFont(const char*path, int size);
    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void presentScene();
};

#endif // GRAPHICS_H_INCLUDED
