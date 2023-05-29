#include <string>

#include "src/game/game.hpp"
#include "src/map/map.hpp"

int main() {
  tmx::Map tiled_map;

  if (tiled_map.load("assets/map/map0.tmx")) {
    std::vector<sf::Texture> key_textures;

    for (int i{}; i < 3; i++) {
      sf::Texture texture;

      texture.loadFromFile("assets/map/items/key_" + std::to_string(i) +
                           ".png");

      key_textures.push_back(texture);
    }

    fnad::Game game{tiled_map, key_textures};

    game.printStory();

    game.run();

    game.end();
  }
}