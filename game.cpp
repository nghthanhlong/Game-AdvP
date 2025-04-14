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
#include"defs.h"

using namespace std;

const char *dictionary = "assets/dictionary.txt";

int Game::winCount=0;
int Game::timesCount=0;

Game::Game(){
    currentrow=0;
    currentcol=0;
    answer=getRandomWord();
    showResult=false;
    finish=false;
}

string Game::getRandomWord(){
    ifstream file (dictionary);
    if(!file){
        cerr<<"Could not open dictionary\n";
    }

    vector<string> setOfWord;
    string word;
    while(file>>word) {

        if(word.size()!=GRID_COLS){
            continue;
        }
        else{
            word=toUpperCase(word);
            setOfWord.push_back(word);
        }
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

bool Game::gameOver(){
    return currentrow>=GRID_ROWS;
}

bool Game::gameWin(){
    for(int i=0; i<GRID_COLS; i++){
        if(!(grid[currentrow][i].color.r==0 && grid[currentrow][i].color.g==255)){
            return false;
        }
    }
    return true;
}

void Game::textInput(string &text){
    if(currentcol<GRID_COLS) {
        for(char &c : text){
            c=toupper(c);
        }
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

            if(gameWin()){
                showResult=true;
                result="Congratulations!";
            }
            else{
                currentrow++;
                currentcol=0;
                if(gameOver()){
                    showResult=true;
                    result="You lose. The answer was: ";
                }
            }
        }
    }
}

string Game::toUpperCase(const string&input){
    string result = input;
    for(char &c : result){
        c=toupper(c);
    }
    return result;
}

void Game::resetGame(){
    currentcol=0;
    currentrow=0;
    answer=getRandomWord();
    showResult=false;
    finish=false;
    winCheck=false;
    timeCheck=false;
    for(int i=0; i<GRID_ROWS; i++){
        for(int j=0; j<GRID_COLS; j++){
            grid[i][j].text.clear();
            grid[i][j].color={255,255,255,255};
        }
    }
}

void Game::countGameWon(){
    if(gameWin() && !winCheck){
        winCount++;
        winCheck=true;
        cout<<"Win: "<<winCount<<"\n";
    }
}

void Game::countTimesPlayed(){
    if(finish && !timeCheck){
        timesCount++;
        timeCheck=true;
        cout<<"Times: "<<timesCount<<"\n";
    }
}
