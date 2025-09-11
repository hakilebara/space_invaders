#include "controller.hpp"


void Controller::HandleInput(bool &running, Player &player) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
          case SDLK_LEFT:
            key_left_pressed = true;
            player.velocity = -2;
            break;
          case SDLK_RIGHT:
            key_right_pressed = true;
            player.velocity = 2;
            break;
          default:
            break;
        }
        break;

      case SDL_KEYUP:
        switch (e.key.keysym.sym) {
          case SDLK_LEFT:
            key_left_pressed = false;
            if (!key_right_pressed)
              player.velocity = 0;
            else
              player.velocity = 2;
            break;
          case SDLK_RIGHT:
            key_right_pressed = false;
            if (!key_left_pressed)
              player.velocity = 0;
            else
              player.velocity = -2;
            break;
          default:
            break;
        }
        break;

      case SDL_QUIT:
        running = false;
        break;

      default:
        break;
    }
  }
}
