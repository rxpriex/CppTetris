#ifndef COMPONENT_BLUEPRINT_HEADER
#define COMPONENT_BLUEPRINT_HEADER

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <functional>


class Color {
public:
  int r, g, b, a;
  Color(int r, int g, int b, int a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }
  ~Color() = default;
};

class RxComponent {
protected:
  int x, y;
  int width, height;

  int xspeed,yspeed;

  Color c;

  std::function<void(RxComponent *,SDL_Renderer*)> render_instructions;

public:
  RxComponent(Color c, std::function<void(RxComponent *,SDL_Renderer*)> render_instructions)
      : c(c), render_instructions(render_instructions), xspeed(0), yspeed(0), x(0),y(0) {}

  ~RxComponent() = default;

  std::function<void(RxComponent *,SDL_Renderer*)> *access_render_instructions();

  void setLocation(int, int);

  void setSize(int, int);

  void getParameters(int*,int*,int*,int*);

  void move();

  void set_movement_parameters(int,int);
};

#endif