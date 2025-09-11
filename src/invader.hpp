#ifndef INVADER_H
#define INVADER_H

#include "ship.hpp"
#include <cstdlib>

#define INVADER_WIDTH 11

class Invader : public Ship {
  public:
    Invader(float x, float y) : Ship(x, y) {
      width = INVADER_WIDTH;
      velocity = -5.0f;
    }

    uint8_t const sprite_crab_frame1[INVADER_WIDTH] = { 0x30, 0x18, 0x7D, 0xB6, 0xBC, 0x3C, 0xBC, 0xB6, 0x7D, 0x18, 0x30 }; // claw down 
    uint8_t const sprite_crab_frame2[INVADER_WIDTH] = { 0x1E, 0xB8, 0x7D, 0x36, 0x3C, 0x3C, 0x3C, 0x36, 0x7D, 0xB8, 0x1E }; // claw up
    uint8_t const sprite_crab_frame3[INVADER_WIDTH] = { 0x92, 0x44, 0x28, 0x81, 0x42, 0x00, 0x42, 0x81, 0x28, 0x44, 0x92 }; // explosion
};

#endif
