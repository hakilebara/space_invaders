#ifndef INVADER_H
#define INVADER_H

#include "ship.hpp"

#define INVADER_WIDTH 11

class Invader : public Ship {
  public:
    Invader(float x, float y) : Ship(x, y) {
      width = INVADER_WIDTH;
      velocity = 5.0f;
    }
    bool dead = false;
};

#endif
