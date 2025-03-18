#include "RxComponent.h"
#include <cstddef>
#include <functional>

void RxComponent::setLocation(int x, int y) {
  this->x = x;
  this->y = y;
}

void RxComponent::setSize(int width, int height) {
  this->width = width;
  this->height = height;
}

std::function<void(RxComponent *,SDL_Renderer*)> *RxComponent::access_render_instructions() {
  return &render_instructions;
}

void RxComponent::getParameters(int *x, int *y, int *w, int *h){
    if(x != NULL){
        *x = this->x;
    }
    if(y != NULL){
        *y = this->y;
    }
    if(w != NULL){
        *w = this->width;
    }
    if(h != NULL){
        *h = this->height;
    }
}