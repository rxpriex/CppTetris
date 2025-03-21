#ifndef RXFRAME_HEADER
#define RXFRAME_HEADER

#include <SDL.h>
#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <cstdlib>
#include <stdio.h>

#include <vector>
#include <memory>

#include "Component/RxComponent.h"

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
  std::shared_ptr<SDL_Window> DISPLAY;
  std::shared_ptr<SDL_Renderer> RENDERER;

  std::shared_ptr<std::vector<RxComponent>> children;

public:
  RxFrame(int rw, int rh) {
    if (!initFrame(rw, rh)) {
      THROW_SDL_ERROR(DISPLAY.get(), RENDERER.get());
    }
  }

  ~RxFrame()=default;

  bool initFrame(int rw, int rh);

  SDL_Event renderNextFrame();

  std::vector<RxComponent>* access_children();
};

#endif