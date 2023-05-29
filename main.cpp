#include <string>

#include "src/game/game.hpp"
#include "src/map/map.hpp"

int main() {
  sf::RenderWindow window(sf::VideoMode::getDesktopMode(),
                          "Five nights at DIFA");
  window.setFramerateLimit(60);

  sf::View view({0.f, 0.f}, {300.f, 200.f});

  tmx::Map tiled_map;

  if (tiled_map.load("assets/map/map0.tmx")) {
    std::vector<sf::Texture> key_textures;

    for (int i{}; i < 3; i++) {
      sf::Texture texture;

      texture.loadFromFile("assets/map/items/key_" + std::to_string(i) +
                           ".png");

      key_textures.push_back(texture);
    }

    fnad::Map map{tiled_map, key_textures};

    const fnad::Background background(tiled_map);

    fnad::Epidemic epidemic(99, 1, map, view);

    fnad::Character character(map, sf::Vector2f{0.f, 0.f});

    fnad::Game game(window, view, character, epidemic, map, background);

    game.printStory();

    game.run();

    game.end();
  }
}