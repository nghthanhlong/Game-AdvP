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
    static int winCount;
    static int timesCount;
    int currentrow, currentcol;

    bool winCheck=false;
    bool timeCheck=false;
    bool finish=false;

    Cell grid[GRID_ROWS][GRID_COLS];
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

    void resetGame();
    void countGameWon();
    void countTimesPlayed();
};
#endif // GAME_H_INCLUDED
