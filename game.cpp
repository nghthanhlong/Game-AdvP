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


const char *dictionary = "dictionary.txt";
using namespace std;

Game::Game(){
    currentrow=0;
    currentcol=0;
}

string Game::getRandomWord(){
    ifstream file (dictionary);
    if(!file){
        cerr<<"Could not open dictionary"<<"\n";
    }

    vector<string> setOfWord;
    string word;
    while(file>>word) {
        setOfWord.push_back(word);
    }
    srand(time(0));
    return setOfWord[rand()%setOfWord.size()];

}

void Game::textInput(const string &text){
    if(currentcol<GRID_COLS) {
        grid[currentrow][currentcol].text=text;
        currentcol++;
    }
}
