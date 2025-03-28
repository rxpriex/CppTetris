#ifndef RXFRAME_HEADER
#define RXFRAME_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <SDL_mutex.h>
#include <SDL_thread.h>
#include <cstdlib>
#include <stdio.h>
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
    int rw, rh;
    bool repaint;
    bool running;

    std::shared_ptr<SDL_mutex> mutex;
    std::shared_ptr<SDL_Window> display;
    std::shared_ptr<SDL_Renderer> renderer;
    std::shared_ptr<SDL_Thread> graphicThread;
    std::shared_ptr<std::function<void()>> onUpdate;
    std::shared_ptr<std::function<void(SDL_Event)>> keyListener;

    std::shared_ptr<std::vector<RxComponent*>> children;

    static int __stdcall static_thread_function(void* I){
      RxFrame* frame = (RxFrame*)I;

      if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return -1;

      frame->display = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Test", 50, 50, frame->rw, frame->rh,
         SDL_WINDOW_SHOWN),[](SDL_Window* window) {
          if (window) {
              SDL_DestroyWindow(window);
          }
      });
      if (!frame->display.get())
          return -1;

      frame->renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(frame->display.get(), -1, SDL_RENDERER_ACCELERATED),[](SDL_Renderer* render) {
          if (render) {
              SDL_DestroyRenderer(render);
          }
      });
      if (!frame->renderer.get())
          return -1;

      while(frame->running){
        if(frame->repaint){
          SDL_mutexP(frame->mutex.get());
          if(frame->renderNextFrame() == -1) frame->running = false;
          SDL_mutexV(frame->mutex.get());
        }
        if(frame->onUpdate.get()){
          (*frame->onUpdate.get())();
        }
      }

      return 1;
    }

public:
  RxFrame(int, int);

  ~RxFrame()=default;

  void setFps(int);

  int renderNextFrame();

  bool initFrame(int rw, int rh);

  void addComponent(RxComponent*);

  void setOnUpdate(std::function<void()>);

  void setKeyListener(std::function<void(SDL_Event)>);

};

#endif
