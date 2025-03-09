#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

struct Graphics
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;

    void logErrorAndExit(const char* msg, const char* error);
    SDL_Window* initSDL(int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE);
    SDL_Renderer* createRenderer(SDL_Window* window);
    void quitSDL();

    void drawGrid();
    void drawLetter(Cell grid[GRID_ROWS][GRID_COLS]);
    void drawResult(const std::string& message);

    void loadAndRenderBackground(const char *imageFileName);
    std::string toUpperCase(const std::string& input);

};

#endif // GRAPHICS_H_INCLUDED
