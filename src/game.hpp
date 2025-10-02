#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "player.hpp"
#include "invader.hpp"

#define INVADER_NB 55
#define INVADER_ROWS 5
#define SHIP_HEIGHT 8

class Renderer;
class Controller;

enum class GAME_STATE { RUNNING, LOST, WON };
class Game {
  public:
   Game(std::size_t grid_width, std::size_t grid_height);

   void Run(Controller &controller, Renderer &renderer, std::size_t
       target_frame_duration);

   int GetScore() const;

  private:
   const std::size_t grid_width;
   const std::size_t grid_height;
   std::unique_ptr<Player> player;
   std::vector <Invader> invaders;
   int invader_frame_counter = 0;
   int invader_move_counter = 0;
   int invader_frame_delay = 20;
   int score{0};
   GAME_STATE state = GAME_STATE::RUNNING;
   void Update();
};

#endif
