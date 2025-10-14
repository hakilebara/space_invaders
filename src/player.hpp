#ifndef PLAYER_H
#define PLAYER_H

#include "bullet.hpp"
#include "ship.hpp"
#include <memory>
#include "audio.hpp"

#if __cplusplus >= 201703L
    // C++17 or later
    #include <optional>
    namespace compat {
      using std::optional;
	    using std::nullopt;
    }
#else
	// Udacity workspace, C++14 or earlier
    #include <experimental/optional>
    namespace compat {
      using std::experimental::optional;
	    using std::experimental::nullopt;
    }
#endif

#define PLAYER_STARTING_X 13
#define PLAYER_WIDTH 13

class Player : public Ship {
  public:
   Player(float x, float y) : Ship(x, y) {
     width = PLAYER_WIDTH;
     Audio sound{};
   }
   void shoot() {
     if (!bullet) {
       sound.PlaySound("shoot.wav");
       bullet.emplace(x+6, y);
     }
   }
   uint8_t const sprite_player_frame1[PLAYER_WIDTH] = { 0xF0, 0xF8, 0xF8, 0xF8, 0xF8, 0xFE, 0xFF, 0xFE, 0xF8, 0xF8, 0xF8, 0xF8, 0xF0 };
   compat::optional<Bullet> bullet;

  private:
   Audio sound;
};

#endif
