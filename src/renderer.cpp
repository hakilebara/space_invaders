#include "renderer.hpp"
#include <iostream>
#include <string>
#include <cmath>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      block_width(screen_width/grid_width),
      block_height(screen_height/grid_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
      std::cerr << "SDL could not initialize.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create window
    sdl_window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
      
    if (nullptr == sdl_window) {
      std::cerr << "Window could not be creatd.\n";
      std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) {
      std::cerr << "Renderer could not be created.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(std::unique_ptr<Player> &player, std::vector <Invader> &invaders, int invader_move_counter, GAME_STATE game_state) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  if (game_state == GAME_STATE::WON) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
    Renderer::RenderGameOver();
  }

  if (game_state == GAME_STATE::LOST) {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    Renderer::RenderGameOver();
  }

  // Render player
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0xFF);
  RenderPixels(player->x, player->y, player->sprite_player_frame1, player->width);

  // Render invaders' fleet
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (Invader const &invader : invaders) {
    uint8_t const *pixels = (invader_move_counter % 2 == 0)
      ? invader.sprite_crab_frame1
      : invader.sprite_crab_frame2;
    RenderPixels(invader.x, invader.y, pixels, invader.width);
  }

  if (player->bullet) {
    SDL_Rect block;
    block.w = block_width;
    block.h = block_height * 4;

    block.x = player->bullet->x * block_width;
    block.y = player->bullet->y * block_height;

    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}
  
void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title("Space Invaders Score: " + std::to_string(score) + " FPS: " + std::to_string(fps));
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderGameOver() {
    uint8_t const g[8] = { 0x00, 0x3C, 0x42, 0x82, 0x92, 0x72, 0x00, 0x00 };
    uint8_t const a[8] = { 0x00, 0xF8, 0x24, 0x22, 0x24, 0xF8, 0x00, 0x00 };
    uint8_t const m[8] = { 0x00, 0xFE, 0x04, 0x18, 0x04, 0xFE, 0x00, 0x00 };
    uint8_t const e[8] = { 0x00, 0xFE, 0x92, 0x92, 0x92, 0x82, 0x00, 0x00 };
    uint8_t const _[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    uint8_t const o[8] = { 0x00, 0x7C, 0x82, 0x82, 0x82, 0x7C, 0x00, 0x00 };
    uint8_t const v[8] = { 0x00, 0x3E, 0x40, 0x80, 0x40, 0x3E, 0x00, 0x00 };
    uint8_t const r[8] = { 0x00, 0xFE, 0x12, 0x32, 0x52, 0x8C, 0x00, 0x00 };
    uint8_t const *game_over[9] = { g, a, m, e, _, o, v, e, r};
    for (int i = 0; i < 9; ++i) {
      RenderPixels(10 + i * 8, grid_height/2, game_over[i], 8);
    }
}

void Renderer::RenderPixels(int x, int y, uint8_t const *pixels, std::size_t size) {
   SDL_Rect block;
   block.w = block_width;
   block.h = block_height;

   block.x = x * block_width;
   block.y = y * block_height;

   for (std::size_t i = 0; i < size; ++i) {
     for (int j = 0; j < 8; ++j) {
       if (pixels[i] & (1 << j))
         SDL_RenderFillRect(sdl_renderer, &block);
       block.y += block_height;
     }
     block.x += block_width;
     block.y = y * block_height;
   }
}
