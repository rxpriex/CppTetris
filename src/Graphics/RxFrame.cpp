#include "RxFrame.h"

bool RxFrame::initFrame(int rw, int rh){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

    DISPLAY = SDL_CreateWindow("Necker",0,0,rw,rh,SDL_WINDOW_SHOWN);
    if(!DISPLAY) return false;
    
    RENDERER = SDL_CreateRenderer(DISPLAY,
        -1,
        SDL_RENDERER_ACCELERATED);
    if(RENDERER) return false;

    return true;
}