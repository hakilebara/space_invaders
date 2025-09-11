#include <iostream>
#include "game.hpp"
#include "renderer.hpp"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{672};
  constexpr std::size_t kScreenHeight{768};
  constexpr std::size_t kGridWidth{224};
  constexpr std::size_t kGridHeight{256};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << std::endl;

  return EXIT_SUCCESS;
}

