#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.hpp"
#include "ship.hpp"
#include <memory>

#define PLAYER_STARTING_X 13
#define PLAYER_WIDTH 13

class Player : public Ship {
  public:
   Player(float x, float y) : Ship(x, y) {
     width = PLAYER_WIDTH;
   }
   void shoot() {
     this->bullet = std::unique_ptr<Bullet>(new Bullet (x+6, y)); // TODO: Magic value
   }
   uint8_t const sprite_player_frame1[PLAYER_WIDTH] = { 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xFE, 0xFF, 0xFE, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0 };
   std::unique_ptr<Bullet> bullet = nullptr;
};

#endif
