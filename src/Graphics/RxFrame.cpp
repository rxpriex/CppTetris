#include "RxFrame.h"
#include "Component/RxComponent.h"
#include <vector>

bool RxFrame::initFrame(int rw, int rh) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    return false;

  DISPLAY = SDL_CreateWindow("Test", 50, 50, rw, rh, SDL_WINDOW_SHOWN);
  if (!DISPLAY)
    return false;

  RENDERER = SDL_CreateRenderer(DISPLAY, -1, SDL_RENDERER_ACCELERATED);
  if (!RENDERER)
    return false;

  children = new std::vector<RxComponent>();

  return true;
}

bool RxFrame::renderNextFrame() {
  SDL_Event event;
  SDL_PollEvent(&event);
  if (event.type == SDL_QUIT) {
    return false;
  }

  for (RxComponent rc : *children) {
    (*rc.access_render_instructions())(&rc, RENDERER);
  }

  return true;
}

std::vector<RxComponent> *RxFrame::access_children() { return children; }