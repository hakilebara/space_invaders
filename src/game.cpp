#include "game.hpp"
#include <iostream>
#include <algorithm>
#include "renderer.hpp"
#include "controller.hpp"
#include "audio.hpp"


Game::Game(std::size_t grid_width, std::size_t grid_height) :
  grid_width(grid_width),
  grid_height(grid_height) {
  player = std::make_unique<Player>(PLAYER_STARTING_X, grid_height - 2 * SHIP_HEIGHT);

  for (int row = 1; row <= INVADER_ROWS; ++row) {
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
    if (state != GAME_STATE::LOST) {
      Update();
    }

    // Render
    renderer.Render(player, invaders, invader_move_counter, state);

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


void Game::Update() {
  player->Move(grid_width);

  Game::MoveInvaderFleet();

  bool player_hit = std::any_of(invaders.begin(), invaders.end(),
      [&](const Invader& i) {
        return i.y >= player->y;
      });

  if (player_hit) {
    state = GAME_STATE::LOST;
  }

  if (player->bullet) {
    player->bullet->Move();

    // destroy the bullet when it goes out of the screen top boundary
    if (player->bullet->y < 0) {
      player->bullet = compat::nullopt;
    }

    // collision detection
    for (Invader &i : invaders) {
      bool hit =
        !i.dead &&
        (player->bullet->x >= i.x && player->bullet->x <= i.x + i.width) &&
        (player->bullet->y >= i.y && player->bullet->y <= i.y + i.height);
      if (hit) {
        i.dead = true;
        score+=10;
        player->bullet = compat::nullopt;
        sound.PlaySound("invaderkilled.wav");
        break;
      }
    }

    invaders.erase(
      std::remove_if(invaders.begin(), invaders.end(),
         [](const Invader& i){
           return i.dead;
         }),
         invaders.end()
    );

    if (invaders.empty()) {
      state = GAME_STATE::WON;
    }
  }
}

void Game::MoveInvaderFleet() {
  // Check if any invaders is out of the bounds of the screen
  if (invader_frame_counter % invader_frame_delay == 0) {
    bool out_of_bound = std::any_of(invaders.begin(), invaders.end(),
        [&](const Invader& i) {
          return (i.velocity < 0 && i.x <= 0) || (i.velocity > 0 && i.x + i.width >= grid_width);
        });

    if (out_of_bound) {
      // Move the entire invader fleet in the opposite direction
      for (Invader &i : invaders) {
        i.y += SHIP_HEIGHT;
        i.velocity *= -1;
      }
    }
    else {
      for (Invader &i : invaders) {
        i.Move(grid_width);
      }
      ++invader_move_counter;
    }
  }
  ++invader_frame_counter;
}

int Game::GetScore() const { return score; }
