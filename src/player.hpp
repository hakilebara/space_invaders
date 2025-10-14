#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.hpp"
#include "ship.hpp"
#include <memory>
#include <optional>
#include "audio.hpp"

#define PLAYER_STARTING_X 13
#define PLAYER_WIDTH 13

class Player : public Ship {
  public:
   Player(float x, float y) : Ship(x, y) {
     width = PLAYER_WIDTH;
     Audio sound = Audio();
   }
   void shoot() {
     if (!bullet) {
       sound.PlaySound("shoot.wav");
       bullet.emplace(x+6, y);
     }
   }
   // Audio sound;
   uint8_t const sprite_player_frame1[PLAYER_WIDTH] = { 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xFE, 0xFF, 0xFE, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0 };
   std::optional<Bullet> bullet;

  private:
   Audio sound;
};

#endif
