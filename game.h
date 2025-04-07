#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include<string>
#include<vector>

#include<SDL.h>

#include"defs.h"

//to chuc game thanh cac Cell, moi Cell chua 1 letter
struct Cell
{
    std::string text;
    SDL_Color color = {255, 255, 255, 0};
};

struct Game
{
    Cell grid[GRID_ROWS][GRID_COLS];
    int currentrow, currentcol;
    bool finish=false;
    Game();

    std::string answer;
    std::string result;
    std::string getRandomWord();

    void evaluateGuess(int currentrow);

    bool gameOver();
    bool gameWin();
    bool showResult;

    void textInput(std::string &text);
    void keyPress(SDL_Keycode key);
    std::string toUpperCase(const std::string &input);
};
#endif // GAME_H_INCLUDED
