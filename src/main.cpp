#include "Graphics/RxFrame.h"
#include <iostream>

void start_render(){
    RxFrame* frame= new RxFrame(400,600);

    RxComponent rc(Color(255,255,255,255),
    [&](RxComponent* rcp, SDL_Renderer* rnd){
        int x = 0,y = 0, width = 0, height = 0;
        rcp->getParameters(&x, &y, &width, &height);

        SDL_Rect rect = {x, y, width, height}; // x, y, width, height
        SDL_SetRenderDrawColor(rnd, 0, 255, 0, 255); // Green
        SDL_RenderFillRect(rnd, &rect);
    });

    rc.setLocation(50, 50);
    rc.setSize(50, 50);

    frame->access_children()->push_back(rc);

    bool running = true;
    while (running) {
        if(!frame->renderNextFrame()){
            running = false;
        }
    }
}

int main(int argc, char* argv[]) {
    start_render();

    return 0;
}