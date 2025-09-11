#ifndef SHIP_H
#define SHIP_H

#include "SDL.h"


class Ship {
  public:
   Ship(float x, float y) : x(x), y(y) {}
   float x = 0;
   float y = 0;
   float height = 8;
   float velocity= 0;
   float width = 8;
   void Move(const std::size_t width_limit) {
     x += velocity;
     if (x < 0) { x = 0; }
     if (x > width_limit - width) { x = width_limit - width; }
   }
};

#endif
