#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.hpp"

class Controller {
  public:
   void HandleInput(bool &running, Player &player);

  private:
   bool key_left_pressed = false;
   bool key_right_pressed = false;
};
#endif
