#include <tmxlite/Map.hpp>

#include "src/game/game.hpp"

int main() {
  tmx::Map tiled_map;

  if (tiled_map.load("assets/map/map0.tmx")) {
    fnad::Game game{tiled_map};

    game.printStory();

    game.run();

    game.end();
  }
}