#include "RxFrame.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL_rect.h>
#include <SDL_stdinc.h>
#include <memory>
#include <mutex>
#include <vector>

RxFrame::RxFrame(int rw, int rh){
    if (!initFrame(rw, rh)) {
      THROW_SDL_ERROR(DISPLAY.get(), RENDERER.get());
    }
}

bool RxFrame::initFrame(int rw, int rh) {

    children = std::shared_ptr<std::vector<RxComponent*>>(new std::vector<RxComponent*>);

    mutex = std::shared_ptr<std::mutex>(new std::mutex());

    /*if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return;

      DISPLAY = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Test", 50, 50, rw, rh, SDL_WINDOW_SHOWN),[](SDL_Window* window) {
          if (window) {
              SDL_DestroyWindow(window); // Properly clean up SDL_Window
          }
      });
      if (!DISPLAY.get())
          return;

      RENDERER = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(DISPLAY.get(), -1, SDL_RENDERER_ACCELERATED),[](SDL_Renderer* render) {
          if (render) {
              SDL_DestroyRenderer(render); // Properly clean up SDL_Window
          }
      });
      if (!RENDERER.get())
          return;*/



  return true;
}

SDL_Event RxFrame::renderNextFrame() {
  SDL_Event event;
  SDL_PollEvent(&event);
  if (event.type == SDL_QUIT) {
    return event;
  }

  SDL_SetRenderDrawColor(RENDERER.get(),
    0, 0, 0, 255);
  SDL_RenderClear(RENDERER.get());

  for (RxComponent* rc : *children.get()) {
    mutex.get()->lock();
    (*(rc->access_render_instructions()))(rc, RENDERER.get());
    mutex.get()->unlock();
  }

  SDL_RenderPresent(RENDERER.get());

  return event;
}

void RxFrame::addComponent(RxComponent* target){
    children.get()->push_back(target);
}
