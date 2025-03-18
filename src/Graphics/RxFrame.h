#ifndef RXFRAME_HEADER
#define RXFRAME_HEADER

#include <SDL.h>
#include <SDL_error.h>
#include <SDL_video.h>
#include <cstdlib>
#include <stdio.h>

class RxFrame{
private:
    SDL_Window* DISPLAY;

    void __attribute__((noreturn)) SDL_ERROR(){
        printf("Program exited with a error %s",
        SDL_GetError());
        exit(-1);
    }

public:
    RxFrame(int rw, int rh){
        if(!initFrame(rw,rh)){
            SDL_ERROR();
        }
    }

    ~RxFrame(){

    }

    bool initFrame(int rw, int rh){
        if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

        DISPLAY = SDL_CreateWindow("Necker",0,0,rw,rh,0x00000004);
        if(!DISPLAY) return false;
        

    }

};

#endif