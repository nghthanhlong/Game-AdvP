#ifndef RUN_H_INCLUDED
#define RUN_H_INCLUDED

#include"defs.h"
#include"graphics.h"
#include"game.h"

struct Run
{
    void gameRun(SDL_Renderer *renderer, SDL_Texture *background, Graphics &graphics, Game &game)
    {
        bool quit=false;
        SDL_Event event;
        while(!quit){
            while(SDL_PollEvent(&event)!=0){
                if(event.type==SDL_QUIT){
                    quit=true;
                }
                else if(event.type==SDL_KEYDOWN){
                    game.keyPress(event.key.keysym.sym);
                }
                else if(event.type==SDL_TEXTINPUT){
                    std::string text=event.text.text;
                    if(text.size()==1 && isalpha(text[0])){
                        game.textInput(text);
                    }
                }
            }
            SDL_RenderCopy(renderer, background, NULL, NULL);

            graphics.drawGrid();
            graphics.drawLetter(game.grid, game);

            if(game.showResult){
                if(game.gameOver()){
                    graphics.drawResult(game.result, game.answer);
                    game.finish=true;
                }
                if(game.gameWin()){
                    graphics.drawResult(game.result, "");
                    game.finish=true;
                }
            }
            graphics.presentScene();
            if(game.finish){
                graphics.presentScene();
                graphics.waitUntilKeyPressed();
                break;
            }
        }
    }
};

#endif // RUN_H_INCLUDED
