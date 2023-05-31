#include <string>

#include "src/entities/enemy/enemy.hpp"
#include "src/game/game.hpp"
#include "src/key/key.hpp"
#include "src/map/map.hpp"

int main() {
  tmx::Map tiled_map;

  if (tiled_map.load("assets/map/map0.tmx")) {
    fnad::Game game{tiled_map};

    game.printStory();

    game.run();

    game.end();
  }
}