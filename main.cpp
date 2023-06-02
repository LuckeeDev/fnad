#include <tmxlite/Map.hpp>

#include "src/game/game.hpp"

int main() {
  tmx::Map tiled_map;

  if (tiled_map.load("assets/map/difa_map.tmx")) {
    fnad::Game game{tiled_map};

    game.printStory();

    game.run();

    game.end();
  }
}