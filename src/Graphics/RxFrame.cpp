#include "RxFrame.h"
#include "Component/RxComponent.h"
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <memory>
#include <vector>

bool RxFrame::initFrame(int rw, int rh) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return false;

  DISPLAY = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Test", 50, 50, rw, rh, SDL_WINDOW_SHOWN),[](SDL_Window* window) {
    if (window) {
        SDL_DestroyWindow(window); // Properly clean up SDL_Window
    }
  });
  if (!DISPLAY.get())
    return false;

  RENDERER = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(DISPLAY.get(), -1, SDL_RENDERER_ACCELERATED),[](SDL_Renderer* render) {
    if (render) {
        SDL_DestroyRenderer(render); // Properly clean up SDL_Window
    }
  });
  if (!RENDERER.get())
    return false;

  children = std::shared_ptr<std::vector<RxComponent>>(new std::vector<RxComponent>); 

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

  for (RxComponent rc : *children.get()) {
    (*(rc.access_render_instructions()))(&rc, RENDERER.get());
  }

  SDL_RenderPresent(RENDERER.get());

  return event;
}

std::vector<RxComponent>* RxFrame::access_children() { return children.get(); }