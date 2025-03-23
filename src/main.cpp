#include "Graphics/Component/RxComponent.h"
#include "Graphics/RxFrame.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <cstddef>
#include <iostream>

class Rect: public RxComponent{
private:
    SDL_Rect hitbox;
    SDL_Rect bounds;

    SDL_Rect getRect(int x,int y,int w,int h){
        SDL_Rect to_render;

        to_render.x = x;
        to_render.y = y;
        to_render.w = w;
        to_render.h = h;

        return to_render;
    }

    void move(){
        hitbox.x += xspeed;
        hitbox.y += yspeed;

        if(SDL_HasIntersection(&bounds, &hitbox) == SDL_FALSE){
            hitbox.x -= xspeed;
            hitbox.y -= yspeed;
        }else{
            x += xspeed;
            y += yspeed;
        }

        xspeed = 0;
        yspeed = 0;
    }

public:
    Rect(int x,int y,int width, int height):RxComponent(Color(255,255,255,255), 
    [&](RxComponent* component,SDL_Renderer*  render){    
        move();
        SDL_SetRenderDrawColor(render, c.r, c.g, c.b, c.a);
        
        SDL_Rect to_render = getRect(this->x, this->y,
            this->width, this->height);
        SDL_RenderFillRect(render, &to_render);
    }){
        hitbox.x = x;
        hitbox.y = y;
        hitbox.w = width;
        hitbox.h = height;

        setLocation(x,y);
        setSize(width, height);
    }

    void setBounds(int maxX, int maxY){
        bounds.h = maxY;
        bounds.w = maxX;
        bounds.x = 0;
        bounds.y = 0;
    }
};

Rect* player;

int main(int argc, char* argv[]) {
    RxFrame frame(400,600);

    Rect player(50,50,10,10);
    player.setBounds(400, 600);

    frame.access_children()->push_back(player);

    bool running = true;
    while (running) {
        SDL_Event event = frame.renderNextFrame();
        switch (event.type) {
            case SDL_QUIT:
                running = false;
            break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_s:
                        player.set_movement_parameters(0, 10);
                        break;
                    case SDLK_d:
                        player.set_movement_parameters(10, 0);
                        break;
                    case SDLK_a:
                        player.set_movement_parameters(-10, 0);
                    break;
                    case SDLK_q:
                        std::cout << "Q pressed, quitting..." << std::endl;
                        running = false;
                        break;
                    default:
                        std::cout << "Keypress not recognised" << std::endl;
                        break;
                }
            break;
        }
    }

    return 0;
}