#include "game.hpp"
#include <iostream>
#include <algorithm>


Game::Game(std::size_t grid_width, std::size_t grid_height) :
  grid_width(grid_width),
  grid_height(grid_height),
  player(PLAYER_STARTING_X, grid_height - 2 * SHIP_HEIGHT) { 

  for (int row = 0; row < INVADER_ROWS; ++row) {
    float y = row * SHIP_HEIGHT * 1.5;
    for (float j = 0; j < INVADER_NB/INVADER_ROWS; ++j) {
      float x = j * INVADER_WIDTH * 1.3;
      Invader i(x, y);
      invaders.push_back(i);
    }
  }
}

void Game::Run(Controller &controller, Renderer &renderer, std::size_t target_frame_duration) { 
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while(running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop
    controller.HandleInput(running, player);
    Update();
    
    // Render
    renderer.Render(player, invaders, invader_move_counter);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cyle
    // takes
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If tthe time for this frame is too small (i.e. frame_duration is samller
    // than the target ms_per_frame), delay the loop to achieve the correct
    // frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

 // flag used to stop invaders from moving left/right when they shift down
bool dont_move = false;

void Game::Update() {
  player.Move(grid_width);

  if (invader_frame_counter % invader_frame_delay == 0) {
    bool out_of_bound = std::any_of(invaders.begin(), invaders.end(),
        [&](Invader i) { return (i.x <= 0 || i.x >= grid_width - i.width); } ); 

    if (out_of_bound) {
      if (!dont_move) {
        for (Invader &i : invaders) {
          i.y += SHIP_HEIGHT;
          i.velocity *= -1; // Change invaders' direction by flipping their velocity sign
         }
         dont_move = true;
      } else dont_move = false;
    }
    if (!dont_move) {
      for (Invader &i : invaders) {
        i.Move(grid_width);
      }
      ++invader_move_counter;
    }
  }
  ++invader_frame_counter;
}
int Game::GetScore() const { return score; }
