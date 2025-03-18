#ifndef RXFRAME_HEADER
#define RXFRAME_HEADER

#include <SDL.h>
#include <SDL_error.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <cstdlib>
#include <stdio.h>

static void __attribute__((noreturn)) THROW_SDL_ERROR(SDL_Window* DISPLAY,
    SDL_Renderer* RENDERER){
    printf("Program exited with a error %s",
        SDL_GetError());
        SDL_DestroyWindow(DISPLAY);
        SDL_DestroyRenderer(RENDERER);
        SDL_Quit();
        exit(-1);
}

class RxFrame{
private:
    SDL_Window* DISPLAY;
    SDL_Renderer* RENDERER;

public:
    RxFrame(int rw, int rh){
        if(!initFrame(rw,rh)){
            THROW_SDL_ERROR(DISPLAY,RENDERER);
        }
    }

    ~RxFrame(){
        SDL_DestroyRenderer(RENDERER);
        SDL_DestroyWindow(DISPLAY);
        SDL_Quit();
    }

    bool initFrame(int rw, int rh);

};

#endif