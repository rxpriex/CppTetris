#ifndef RXFRAME_HEADER
#define RXFRAME_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <cstdlib>
#include <mutex>
#include <stdio.h>
#include <thread>
#include <vector>
#include <memory>
#include <functional>

#include "Components/Template/RxComponent.h"

static void __attribute__((noreturn)) THROW_SDL_ERROR(SDL_Window *DISPLAY,
                                                      SDL_Renderer *RENDERER) {
  printf("Program exited with a error %s", SDL_GetError());
  SDL_DestroyWindow(DISPLAY);
  SDL_DestroyRenderer(RENDERER);
  SDL_Quit();
  exit(-1);
}

class RxFrame {
private:
    int frames;
    bool render;
    std::shared_ptr<std::mutex> mutex;


    std::shared_ptr<SDL_Window> DISPLAY;
    std::shared_ptr<SDL_Renderer> RENDERER;
    std::shared_ptr<std::thread> graphicTimer;
    std::shared_ptr<std::function<void()>> onUpdate;

    std::shared_ptr<std::vector<RxComponent*>> children;

public:
  RxFrame(int, int);

  ~RxFrame()=default;

  void setFps(int);

  SDL_Event renderNextFrame();

  bool initFrame(int rw, int rh);

  void addComponent(RxComponent*);
};

#endif
