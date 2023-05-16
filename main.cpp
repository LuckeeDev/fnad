#include "src/game/game.hpp"
#include "src/map/map.hpp"

int main() {
  fnad::Game const& game = fnad::Game::create();

  game.run();
}