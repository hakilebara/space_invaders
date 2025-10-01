#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "player.hpp"
#include "invader.hpp"
#include "game.hpp"

class Renderer {
  public:
   Renderer(const std::size_t screen_width, const std::size_t screen_height,
      const std::size_t grid_width, const std::size_t grid_height); 
   ~Renderer();

   void Render(Player const &player, std::vector <Invader> &invaders, int invader_move_counter, GAME_STATE game_state);
   void UpdateWindowTitle(int scrore, int fps);

  private:
   SDL_Window *sdl_window;
   SDL_Renderer *sdl_renderer;

   const std::size_t screen_width;
   const std::size_t screen_height;
   const std::size_t grid_width;
   const std::size_t grid_height;

   const float block_width;
   const float block_height;

   void RenderPixels(int x, int y, uint8_t const *pixels, std::size_t size);
   void RenderGameOver();
};
#endif
