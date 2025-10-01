#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.hpp"
#include "ship.hpp"
#include <memory>
#include <optional>

#define PLAYER_STARTING_X 13
#define PLAYER_WIDTH 13

class Player : public Ship {
  public:
   Player(float x, float y) : Ship(x, y) {
     width = PLAYER_WIDTH;
   }
   void shoot() {
     if (!bullet)
       bullet.emplace(x+6, y);
   }
   uint8_t const sprite_player_frame1[PLAYER_WIDTH] = { 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xFE, 0xFF, 0xFE, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0 };
   std::optional<Bullet> bullet;
};

#endif
