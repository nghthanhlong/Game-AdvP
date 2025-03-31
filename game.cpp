#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

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
    answer=getRandomWord();
    showResult=false;
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

void Game::evaluateGuess(int currentrow){
    string guess;
    for(int i=0; i<GRID_COLS; i++){
        guess+=grid[currentrow][i].text;
    }

    unordered_map<char, int> mp;
    vector<bool> check(GRID_COLS, false);

    for(char &c : answer){
        mp[c]++;
    }
    for(int i=0; i<GRID_COLS; i++){
        if(guess[i]==answer[i]){
            grid[currentrow][i].color={0,255,0,255};
            cout<<guess[i]<<" is in the word\n";
            mp[guess[i]]--;
            check[i]=true;
        }
    }
    for(int i=0; i<GRID_COLS; i++){
        if(!check[i] && answer.find(guess[i])!=string::npos && mp[guess[i]]>0){
            grid[currentrow][i].color={255, 255, 0, 255};
            cout<<guess[i]<<" is in wrong position\n";
            mp[guess[i]]--;
            check[i]=true;
        }
    }
    for(int i=0; i<GRID_COLS; i++){
        if(!check[i]){
            grid[currentrow][i].color={255, 255,255,255};
            cout<<guess[i]<<" is not in the word\n";
        }
    }
}

bool Game::GameOver(){
    return currentrow>=GRID_ROWS;
}

bool Game::Win(){
    for(int i=0; i<GRID_COLS; i++){
        if(!(grid[currentrow][i].color.r==0 && grid[currentrow][i].color.g==255)){
            return false;
        }
    }
    return true;
}

void Game::textInput(const string &text){
    if(currentcol<GRID_COLS) {
        grid[currentrow][currentcol].text=text;
        currentcol++;
    }
}

void Game::keyPress(SDL_Keycode key)
{
    if(key==SDLK_BACKSPACE) {
        if(currentcol>0) {
            currentcol--;
            grid[currentrow][currentcol].text.clear();
        }
    }
    else if(key==SDLK_RETURN){
        if(currentcol==GRID_COLS){
            evaluateGuess(currentrow);

            if(Win()){
                showResult=true;
                result="CONGRATULATIONS!";
            }
            else{
                currentrow++;
                currentcol=0;
                if(GameOver()){
                    showResult=true;
                    result="YOU LOST! THE ANSWER IS " + answer;
                }
            }
        }
    }
}
