#ifndef PLAYER_H
#define PLAYER_H

#include "ship.hpp"

#define PLAYER_STARTING_X 13
#define PLAYER_WIDTH 13

class Player : public Ship {
  public:
   Player(float x, float y) : Ship(x, y) {
     width = PLAYER_WIDTH;
   }
   uint8_t const sprite_player_frame1[PLAYER_WIDTH] = { 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xFE, 0xFF, 0xFE, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0 };
};

#endif
