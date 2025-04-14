#include<iostream>

#include<SDL.h>
#include<SDL_ttf.h>
#include<SDL_image.h>

#include"graphics.h"
#include"defs.h"
#include"game.h"

using namespace std;

void Graphics::logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* Graphics::initSDL(int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logErrorAndExit("SDL_Init", SDL_GetError());
    }
    if(TTF_Init()==-1){
        logErrorAndExit("TTF_Init", TTF_GetError());
    }
    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)){
        logErrorAndExit("IMG_Init", IMG_GetError());
    }
    window = SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        logErrorAndExit("Create Window", SDL_GetError());
    }

    return window;
}

SDL_Renderer* Graphics::createRenderer(SDL_Window* window) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    return renderer;
}

void Graphics::quitSDL(){
    SDL_DestroyTexture(background);
    background=NULL;

    TTF_CloseFont(font);
    font=NULL;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit(); IMG_Quit(); SDL_Quit();
}

void Graphics::drawGrid(){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int startX=(WINDOW_WIDTH-GRID_COLS*CELL_SIZE)/2;
    int startY=(WINDOW_HEIGHT-GRID_ROWS*CELL_SIZE)/2;

    for(int i=0; i<=GRID_COLS; i++) {
        int x=startX+i*CELL_SIZE;
        SDL_RenderDrawLine(renderer,x,startY,x,startY+GRID_ROWS*CELL_SIZE);
    }

    for(int i=0; i<=GRID_ROWS; i++) {
        int y=startY+i*CELL_SIZE;
        SDL_RenderDrawLine(renderer,startX,y,startX+GRID_COLS*CELL_SIZE, y);
    }
}

void Graphics::drawLetter(Cell grid[GRID_ROWS][GRID_COLS], Game game){
    for(int i=0; i<GRID_ROWS; i++){
        for(int j=0; j<GRID_COLS; j++) {
            if(!grid[i][j].text.empty()){
                string uppertext=grid[i][j].text;

                SDL_Surface* textSurface=TTF_RenderText_Solid(font, uppertext.c_str(), grid[i][j].color);
                SDL_Texture* textTexture=SDL_CreateTextureFromSurface(renderer, textSurface);

                int textwidth=textSurface->w; int textheight=textSurface->h;

                int startX=(WINDOW_WIDTH-GRID_COLS*CELL_SIZE)/2;
                int startY=(WINDOW_HEIGHT-GRID_ROWS*CELL_SIZE)/2;
                int x=startX+j*CELL_SIZE+(CELL_SIZE-textwidth)/2;
                int y=startY+i*CELL_SIZE+(CELL_SIZE-textheight)/2;

                SDL_Rect rect={x, y, textwidth, textheight};
                SDL_RenderCopy(renderer, textTexture, nullptr, &rect);

                SDL_FreeSurface(textSurface);
                SDL_DestroyTexture(textTexture);
            }
        }
    }
}

void Graphics::drawResult(const string& message, const string &answer)
{
    SDL_Color mainColor={255, 255, 255, 255};
    SDL_Color answerColor={255, 0, 0, 0};
    SDL_Surface *mainSurface=TTF_RenderText_Solid(font, message.c_str(), mainColor);
    SDL_Texture *mainTexture=SDL_CreateTextureFromSurface(renderer, mainSurface);

    int mainWidth=mainSurface->w; int mainHeight=mainSurface->h;

    int startY=(WINDOW_HEIGHT-GRID_ROWS*CELL_SIZE)/2;
    int mainX = (WINDOW_WIDTH-mainWidth)/2;
    int y = startY+GRID_ROWS*CELL_SIZE+DISTANCE;

    if(answer.empty()==false){
        SDL_Surface *answerSurface = TTF_RenderText_Solid(font, answer.c_str(), answerColor);
        int answerWidth=answerSurface->w;
        SDL_FreeSurface(answerSurface);
        int totalWidth=mainWidth+answerWidth;
        mainX=(WINDOW_WIDTH-totalWidth)/2;
    }

    SDL_Rect destRect = {mainX, y, mainWidth, mainHeight};
    SDL_RenderCopy(renderer, mainTexture, nullptr, &destRect);
    SDL_FreeSurface(mainSurface);
    SDL_DestroyTexture(mainTexture);

    if(answer.empty()==false){
        SDL_Surface *answerSurface=TTF_RenderText_Solid(font, answer.c_str(), answerColor);
        SDL_Texture *answerTexture=SDL_CreateTextureFromSurface(renderer, answerSurface);

        int answerWidth=answerSurface->w;
        int answerHeight=answerSurface->h;
        int answerX=mainX+mainWidth;

        SDL_Rect answerRect={answerX, y, answerWidth, answerHeight};
        SDL_RenderCopy(renderer, answerTexture, nullptr, &answerRect);
        SDL_FreeSurface(answerSurface);
        SDL_DestroyTexture(answerTexture);
    }
}

TTF_Font* Graphics::loadFont(const char* path, int size)
{
    TTF_Font* gFont = TTF_OpenFont( path, size );
    if (gFont == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
    }
    return gFont;
}

void Graphics::presentScene()
{
    SDL_RenderPresent(renderer);
}

SDL_Texture *Graphics::loadTexture(const char *fileName, SDL_Renderer *renderer){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", fileName);
    SDL_Texture *texture=IMG_LoadTexture(renderer, fileName);
    if(texture==NULL){
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", IMG_GetError());
    }
    return texture;
}

void Graphics::drawReplayMessage(){
    SDL_Color messageColor={0, 255, 0, 0};
    const string message="Press Enter to play again";

    TTF_Font *font=TTF_OpenFont(fontUsed, 24);

    SDL_Surface *messageSurface=TTF_RenderText_Solid(font, message.c_str(), messageColor);
    SDL_Texture *messageTexture=SDL_CreateTextureFromSurface(renderer, messageSurface);

    int messageWidth=messageSurface->w;
    int messageHeight=messageSurface->h;

    int startY=(WINDOW_HEIGHT-GRID_ROWS*CELL_SIZE)/2;
    int mainX=(WINDOW_WIDTH-messageWidth)/2;
    int mainY=startY+GRID_ROWS*CELL_SIZE+3*DISTANCE;

    SDL_Rect destRect={mainX, mainY, messageWidth, messageHeight};
    SDL_RenderCopy(renderer, messageTexture, nullptr, &destRect);
    SDL_FreeSurface(messageSurface);
    SDL_DestroyTexture(messageTexture);
}

void Graphics::drawVictoryNumber(int winCount){
    SDL_Color messageColor={255, 255, 255, 255};
    SDL_Color numberColor={0, 255, 0, 255};

    const string message = "Wins: ";
    string number=to_string(winCount);

    TTF_Font *font=TTF_OpenFont(fontUsed, 24);

    SDL_Surface *messageSurface=TTF_RenderText_Solid(font, message.c_str(), messageColor);
    SDL_Texture *messageTexture=SDL_CreateTextureFromSurface(renderer, messageSurface);

    int messageWidth=messageSurface->w;
    int messageHeight=messageSurface->h;

    SDL_Surface *numberSurface=TTF_RenderText_Solid(font, number.c_str(), numberColor);
    SDL_Texture *numberTexture=SDL_CreateTextureFromSurface(renderer, numberSurface);

    int numberWidth=numberSurface->w;
    int numberHeight=numberSurface->h;

    int messageX=DISTANCE;
    int messageY=DISTANCE_WINDOW_AND_LINE;

    int numberX=messageX+messageWidth;

    SDL_Rect messageRect={messageX, messageY, messageWidth, messageHeight};
    SDL_RenderCopy(renderer, messageTexture, nullptr, &messageRect);
    SDL_FreeSurface(messageSurface);
    SDL_DestroyTexture(messageTexture);

    SDL_Rect numberRect={numberX, messageY, numberWidth, numberHeight};
    SDL_RenderCopy(renderer, numberTexture, nullptr, &numberRect);
    SDL_FreeSurface(numberSurface);
    SDL_DestroyTexture(numberTexture);
}

void Graphics::drawTimesPlayed(int times){
    SDL_Color messageColor={255, 255, 255, 255};
    SDL_Color numberColor={0,255,0,255};

    const string message="Times: ";
    string number=to_string(times);

    TTF_Font *font=TTF_OpenFont(fontUsed, 24);

    SDL_Surface *messageSurface=TTF_RenderText_Solid(font, message.c_str(), messageColor);
    SDL_Texture *messageTexture=SDL_CreateTextureFromSurface(renderer, messageSurface);

    int messageWidth=messageSurface->w;
    int messageHeight=messageSurface->h;

    SDL_Surface *numberSurface=TTF_RenderText_Solid(font, number.c_str(), numberColor);
    SDL_Texture *numberTexture=SDL_CreateTextureFromSurface(renderer, numberSurface);

    int numberWidth=numberSurface->w;
    int numberHeight=numberSurface->h;

    int messageX=DISTANCE;
    int messageY=DISTANCE_WINDOW_AND_LINE+DISTANCE;

    int numberX=messageX+messageWidth;

    SDL_Rect messageRect={messageX, messageY, messageWidth, messageHeight};
    SDL_RenderCopy(renderer, messageTexture, nullptr, &messageRect);
    SDL_FreeSurface(messageSurface);
    SDL_DestroyTexture(messageTexture);

    SDL_Rect numberRect={numberX, messageY, numberWidth, numberHeight};
    SDL_RenderCopy(renderer, numberTexture, nullptr, &numberRect);
    SDL_FreeSurface(numberSurface);
    SDL_DestroyTexture(numberTexture);
}
