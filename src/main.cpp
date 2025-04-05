#include <cstdio>
#include <SDL_Graph/RxFrame.hpp>
#include <SDL_Graph/DrawAbleSprite.hpp>
#include <SDL_Graph/Components/Label/RxLabel.hpp>

DrawAbleSprite* player = NULL;


int main(int argc, char* argv[]) {
    RxFrame frame(400,600);

    player = new DrawAbleSprite(50,50,20,20);
    player->setBounds(400, 600);
    frame.addComponent(player);
    frame.setKeyListener([&](SDL_Event event){
        printf("%c",(char)event.key.keysym.sym);
    });

    RxLabel* label = new RxLabel("test");
    frame.addComponent(label);

    while (true) {

    }

    return 0;
}

/*
bool running = true;
while (running) {
    if(player == NULL) {
        player = new DrawAbleSprite(50,50,20,20);
        player->setBounds(400, 600);
        frame.access_children()->push_back(player);
    }
    if(player->isOff()){
        player = NULL;
        continue;
    }
    SDL_Event event = frame.renderNextFrame();
    switch (event.type) {
        case SDL_QUIT:
            running = false;
        break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_s:
                    player->set_movement_parameters(0, 10);
                    break;
                case SDLK_d:
                    player->set_movement_parameters(10, 0);
                    break;
                case SDLK_a:
                    player->set_movement_parameters(-10, 0);
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
*/
